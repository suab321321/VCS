
#include "../headers/Commit.hpp"
#include<vector>
#include<chrono>
#include<ctime>
#include<sstream>

namespace fs=boost::filesystem;
using namespace std;

ostream & operator <<(ostream& os,const Commit& commit){
	os<<' '<<commit.getTree();
	return os;
}

string& getFilename(string& name){
	int l=name.size();
	while(l>=0){
		if(name[l]=='/'){
			name=name.substr(l+1);
			return name;
		}
		l--;
	}
}

//pushing the committed file
void push(const string& CWD){
	const string treePushedPath=CWD+"/git/tree/pushed";
	const string treeUnpushedPath=CWD+"/git/tree/unpushed";

	if(!move(treeUnpushedPath,treePushedPath)){
		cout<<"Nothing to push!"<<endl;
		return;
	}
	createCommit(CWD);
}

//moving files from unpushed to pushed tree
bool move(const string& fromPath,const string& toPath){
	int isChanged=0;
	fs::path To=toPath;
	fs::path From=fromPath;
	fs::permissions(To,fs::all_all);
	for(fs::directory_entry& ent:fs::directory_iterator(From)){
		if(fs::is_regular_file(ent.path())){
			fs::path intermediatePath=toPath+"/"+ent.path().filename().string();
			string to=toPath+"/"+ent.path().filename().string();
			fs::path To1=to;
			if(!fs::exists(To1)){
				isChanged=1;
				try{
					fs::copy_file(ent.path(),To1);
				}catch(fs::filesystem_error& ex){
						cout<<ex.what()<<endl;
				}
			}
		}
	}

	for(fs::directory_entry& ent:fs::recursive_directory_iterator(toPath)){
		ifstream file(ent.path().string());
		boost::archive::binary_iarchive ois(file);
		Tree tree;
		ois>>tree;
		if(tree.getIsFirst()){
			vector<string>name=tree.getParentTree();
			for(auto& i:name)
				i=toPath+"/"+getFilename(i);
			tree.setParentTree(name);
			ofstream file2(ent.path().string());
			boost::archive::binary_oarchive oos(file2);
			oos<<tree;
		}
		file.close();
	}
	return isChanged;
}

//creating commit object
void createCommit(const string& CWD){
	fs::path treePushedPath=CWD+"/git/tree/pushed";
	string parentTree="";
	for(fs::directory_entry& ent:fs::recursive_directory_iterator(treePushedPath)){
		ifstream file(ent.path().string());
		boost::archive::binary_iarchive ois(file);
		Tree tree;
		ois>>tree;
		if(tree.getIsFirst()==1){
			parentTree=ent.path().string();
			break;
		}
	}
	fs::path p=CWD+"/git/commit/pushed";
	Commit commit;
	commit.setTree(parentTree);
	stringstream ss;
	auto time=chrono::system_clock::to_time_t(chrono::system_clock::now());
	ss<<ctime(&time);
	string hashedPath=ss.str();
	ofstream file(CWD+"/git/commit/pushed/"+hashedPath);
	boost::archive::binary_oarchive oos(file);
	oos<<commit;
	file.close();
	//now removing all the unpushed and intermidiate and nstagged dir's files
//	fs::path p1=CWD+"/git/blob/intermidiate";
//	fs::remove_all(p1);
//	fs::create_directory(p1);
//	p1=CWD+"/git/blob/unstagged";
//	fs::remove_all(p1);
//	fs::create_directory(p1);
//	p1=CWD+"/git/tree/unpushed";
//	fs::remove_all(p1);
//	fs::create_directory(p1);
}
//ends
