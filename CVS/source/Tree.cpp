
#include "../headers/Tree.hpp"
#include<boost/filesystem.hpp>
#include<functional>
#include<sstream>
#include<fstream>
#include<chrono>
#include<ctime>

using namespace std;
namespace fs=boost::filesystem;

ostream & operator << (ostream& os,const Tree& tree){
	os<<' '<<tree.getIsFirst();
	for(auto i:tree.getParentTree())
		os<<i;
	for(auto i:tree.getBlobs())
		os<<i;
	return os;
}

//commit files by taking files from blob/unstagged to stagged dir
void commit(const string& CWD){
	createTree(CWD);
}

//creating the Tree Object
void createTree(const string& CWD){
	Tree tree;
	fs::path intermidiateBlobPath=CWD+"/.git/blob/intermidiate";
	vector<string>blobs;
	fs::path dest=CWD+"/.git/blob/stagged";
	fs::permissions(dest,fs::all_all);

	//moving files from intermidiate to stagged directory
	for(fs::directory_entry& ent:fs::recursive_directory_iterator(intermidiateBlobPath)){
		if(fs::is_regular_file(ent.path())){
			string staggedFilePath=CWD+"/.git/blob/stagged/"+ent.path().filename().string();
			if(!fs::exists(staggedFilePath)){
				cout<<"Committed "<<staggedFilePath<<endl;
				fs::copy_file(ent.path(),staggedFilePath);
				blobs.push_back(staggedFilePath);
			}
		}
	}//ends//
	if(blobs.size()==0){
		cout<<"Nothing to commit"<<endl;
		return;
	}
	tree.setBlobs(blobs);
	string parentTree="";
	fs::path unpushedTreePath=CWD+"/.git/tree/unpushed";
	if(fs::is_empty(unpushedTreePath)){
		stringstream ss;
		auto time=chrono::system_clock::to_time_t(chrono::system_clock::now());
		auto t=ctime(&time);
		ss<<hash<string>{}(t);
		string hashed=ss.str();
		string Filename=CWD+"/.git/tree/unpushed/"+hashed;
		ofstream file(Filename.c_str());
		boost::archive::binary_oarchive oos(file);
		tree.setBlobs(blobs);
		tree.setIsFirst(1);
		tree.setParentTree({});
		oos<<tree;
		return;
	}
	else{
		fs::path p=CWD+"/.git/tree/unpushed";
		for(fs::directory_entry& ent:fs::recursive_directory_iterator(p)){
			string path=ent.path().string();
			ifstream file1(path.c_str());
			boost::archive::binary_iarchive ois(file1);
			Tree t;
			ois>>t;
			file1.close();
			if(t.getIsFirst()==1){
				stringstream ss;
				auto time=chrono::system_clock::to_time_t(chrono::system_clock::now());
				auto ti=ctime(&time);
				ss<<hash<string>{}(ti);
				string hashed=ss.str();
				string Filename=CWD+"/.git/tree/unpushed/"+hashed;
				ofstream file(Filename.c_str());
				boost::archive::binary_oarchive oos(file);
				tree.setBlobs(blobs);
				tree.setIsFirst(0);
				tree.setParentTree({});
				oos<<tree;
				vector<string>vec=t.getParentTree();
				vec.push_back(Filename);
				t.setParentTree(vec);
				ofstream file2(ent.path().string().c_str());
				boost::archive::binary_oarchive oos2(file2);
				oos2<<t;
				file2.close();
			}
		}
	}
	return;
}
