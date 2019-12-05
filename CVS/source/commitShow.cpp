
#include "../headers/commitShow.hpp"


using namespace std;
namespace fs=boost::filesystem;

void saveToVersion(const string& CWD){
	fs::path commitPushedPath;
	fs::path p=CWD+"/git/commit/pushed";
	for(fs::directory_entry& ent:fs::recursive_directory_iterator(p)){
		commitPushedPath=ent.path();
//		fs::remove(ent.path());
	}
	string VersionFileName=commitPushedPath.filename().string();
	fs::path dest=CWD+"/VERSIONS/"+VersionFileName;
	fs::path source=CWD+"/files";
	fs::create_directory(dest);
	fs::create_directories(dest.append(source.string()));
	for(fs::directory_entry& ent:fs::recursive_directory_iterator(source)){
		if(fs::is_regular_file(ent.path())){
			try{
				string val="";
				int l=ent.path().string().size()-1;
				while(l>=0){
					if(ent.path().string()[l]=='/'){
						val=ent.path().string().substr(0,l);
					}
					--l;
				}
				fs::copy_file(ent.path(),dest.append(ent.path().string()));
			}catch(fs::filesystem_error& ex){
				cout<<ex.what()<<endl;
			}
		}
		else
			fs::create_directory(dest.append(ent.path().string()));
	}
}

//void makeDirectories(const string& filePath,const string& root){
//	ifstream file(filePath);
//	boost::archive::binary_iarchive ois(file);
//	Tree tree;
//	ois>>tree;
//	vector<string>blobs=tree.getBlobs();
//	for(auto i:blobs){
//		ofstream file1((root+i).c_str());
//		boost::
//	}
//}
