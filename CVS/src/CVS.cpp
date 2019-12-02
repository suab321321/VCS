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

	unordered_set<string>files;
	unordered_set<string>blobs;
}
