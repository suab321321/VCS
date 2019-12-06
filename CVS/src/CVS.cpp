//#include<boost/archive/binary_iarchive.hpp>
//#include<boost/archive/binary_oarchive.hpp>

#include<fstream>
#include <iostream>
#include "../headers/Blob.hpp"
#include "../headers/Tree.hpp"
#include "../headers/Commit.hpp"
#include "../headers/commitShow.hpp"
#include <boost/filesystem.hpp>
#include<fstream>
#include<unordered_set>
#include<unistd.h>

namespace fs=boost::filesystem;
using namespace std;

void init(const string& CWD){
	fs::path gitDir=CWD+"/.git";
	if(!fs::exists(gitDir)){
		fs::path p1=gitDir;
		fs::create_directories(p1.append("blob/unstagged"));
		p1=gitDir;
		fs::create_directories(p1.append("blob/intermidiate"));
		p1=gitDir;
		fs::create_directories(p1.append("blob/stagged"));
		p1=gitDir;
		fs::create_directories(p1.append("tree/pushed"));
		p1=gitDir;
		fs::create_directories(p1.append("tree/unpushed"));
		p1=gitDir;
		fs::create_directories(p1.append("commit/pushed"));
	}
	fs::path p2=CWD+"/files";
	if(!fs::exists(p2))
		fs::create_directory(p2);
	p2=CWD+"/VERSIONS";
	if(!fs::exists(p2))
		fs::create_directory(p2);
}

int main() {
	boost::filesystem::path full_path(boost::filesystem::current_path());
	fs::path p=full_path.string()+"/"+"files";
	cout<<"git init------->git add------->git commit------->git push"<<endl;
	int choice;
	cin>>choice;
	switch(choice){
		case 0:init(full_path.string());
			break;
		case 1:add(full_path.string());
			break;
		case 2:commit(full_path.string());
			break;
		case 3:if(push(full_path.string())){
				saveToVersion(full_path.string());
				cout<<"Successfully pushed"<<endl;
			}
			break;
		default:
			cout<<"wrong choice"<<endl;
	}
}
