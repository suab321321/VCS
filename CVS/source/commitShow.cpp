
#include "../headers/commitShow.hpp"

using namespace std;
namespace fs=boost::filesystem;

string relativePath(string path,const string& CWD){
	int i=0;
	while(i<path.size()){
		if(CWD[i]==path[i])
			i++;
		else{
			path=path.substr(i);
			return path;
		}
	}
}

void saveToVersion(const string& CWD){
	fs::path commitPushedPath;
	fs::path p=CWD+"/.git/commit/pushed";
	for(fs::directory_entry& ent:fs::recursive_directory_iterator(p)){
		commitPushedPath=ent.path();
	}
	string VersionFileName=commitPushedPath.filename().string();
	fs::path dest=CWD+"/VERSIONS/"+VersionFileName;
	fs::path source=CWD+"/files";
	fs::create_directory(dest);
	fs::create_directories(dest.append(relativePath(source.string(),CWD)));
	for(fs::directory_entry& ent:fs::recursive_directory_iterator(source)){
		if(fs::is_regular_file(ent.path())){
			try{
				fs::path des=CWD+"/VERSIONS/"+VersionFileName+relativePath(ent.path().string(),CWD);
//				cout<<"yes"<<relativePath(ent.path().string(),CWD)<<endl;
				fs::copy_file(ent.path(),des);
			}catch(fs::filesystem_error& ex){
				cout<<ex.code()<<" "<<ex.what()<<endl;
			}
		}
		else{
			fs::path des=CWD+"/VERSIONS/"+VersionFileName+relativePath(ent.path().string(),CWD);
			fs::create_directory(des);
		}
	}
	fs::path p1=CWD+"/.git/commit/pushed";
	fs::remove_all(p1);
	fs::create_directory(p1);
}
