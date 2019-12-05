//#include<boost/archive/binary_iarchive.hpp>
//#include<boost/archive/binary_oarchive.hpp>

#include<fstream>
#include <iostream>
#include "../headers/Blob.hpp"
#include "../headers/Tree.hpp"
#include "../headers/Commit.hpp"
#include <boost/filesystem.hpp>
#include<fstream>
#include<unordered_set>
#include<unistd.h>

namespace fs=boost::filesystem;
using namespace std;

int main() {
//	const string path="/home/abhinav/cpp-2019-09/prgrames/CVS";
	boost::filesystem::path full_path(boost::filesystem::current_path());
//	cout<<full_path<<endl;
//	for(fs::directory_entry& e:fs::recursive_directory_iterator(full_path))
//		cout<<e.path().filename()<<endl;
	fs::path p=full_path.string()+"/"+"files";
//	for(fs::directory_entry& ent:fs::directory_iterator(p))
//		cout<<ent.path().filename().string()<<endl;
	cout<<"git add------->git commit------->git push"<<endl;
	int choice;
	cin>>choice;
	switch(choice){
		case 1:add(full_path.string());
			break;
		case 2:commit(full_path.string());
			break;
//		case 3:push();
//			break;
		default:
			cout<<"wrong choice"<<endl;
	}
}
