#include "../headers/Blob.hpp"
#include<boost/filesystem.hpp>
#include<fstream>
#include<unordered_map>
#include<functional>
#include<sstream>

namespace fs=boost::filesystem;
using namespace std;

//serializing << operator overload
ostream & operator << (ostream& os,const Blob& blob){
	os<<' '<<blob.getFilePath();
	for(auto i:blob.getContent())
		os<<i.first<<i.second;
	return os;
}
//ends

//initiating git add process
void add(const string& CWD){
	unordered_set<string>Files;
	unordered_set<string>Blobs;
	getFiles(Files,(CWD+"/files").c_str());
	getBlobs(Blobs,(CWD+"/git/blob/unstagged").c_str());
	cout<<Blobs.size()<<" "<<Files.size()<<endl;
	for(auto i:Files){
		if(Blobs.find(i)==Blobs.end()){
			stag(i,CWD);
		}
		else{
			if(!compare(i.c_str(),(CWD+"/git/blob/unstagged").c_str()))
				stag(i,CWD);
		}
	}
}
//ends

//getting files from projects
void getFiles(unordered_set<string>& Files,const char* dir){
	try{
		for(fs::directory_entry& ent:fs::recursive_directory_iterator(dir)){
			if(fs::is_regular_file(ent.path()))
				Files.insert(ent.path().string());
		}
	}catch(fs::filesystem_error& ex){
		cout<<ex.what()<<endl;
	}
}
//ends

//getting path of Blobs from git/blob/unstagged dir
void getBlobs(unordered_set<string>& Blobs,const char* dir){
	try{
		for(fs::directory_entry& ent:fs::recursive_directory_iterator(dir)){
			if(fs::is_regular_file(ent.path())){
				ifstream file(ent.path().string().c_str());
				boost::archive::binary_iarchive ios(file);
				Blob b;
				ios>>b;
				Blobs.insert(b.getFilePath());
				file.close();
			}
		}
	}catch(fs::filesystem_error& ex){
		cout<<ex.what();
	}
}
//ends//

bool compare(const char* filePath,const char* blobDir){
	map<int,string>content;
	for(fs::directory_entry& ent:fs::recursive_directory_iterator(blobDir)){
		if(fs::is_regular_file(ent.path())){
			ifstream file(ent.path().string().c_str());
			boost::archive::binary_iarchive ios(file);
			Blob b;
			ios>>b;
			file.close();
			if(!b.getFilePath().compare(filePath)){
				content=b.getContent();
				break;
			}
		}
	}
	unordered_map<int,string>fileContent;
	ifstream file;
	file.open(filePath,ios::in);
	if(file.is_open()){
		string line;
		int count=0;
		while(getline(file,line)){
			++count;
			fileContent[count]=line;
		}
	}
	else
		return 0;
	file.close();
	for(auto i:content){
		if(fileContent[i.first]!=i.second){
			return 0;
		}
	}
	return 1;
}

void stag(const string& filePath,const string& CWD){
	cout<<filePath<<endl;
	ifstream file;
	map<int,string>content;
	file.open(filePath.c_str(),ios::in);
	if(file.is_open()){
		int count=0;
		string line;
		while(getline(file,line)){
			++count;
			content[count]=line;
		}
	}
	else
		return;
	file.close();
	Blob b;
	b.setContent(content);
	b.setFilePath(filePath);
	stringstream ss;
	size_t h=hash<string>{}(filePath);
	ss<<h;
	string hashPath=ss.str();
//	cout<<hashPath<<endl;
	ofstream file2((CWD+"/git/blob/unstagged/"+hashPath).c_str());
	boost::archive::binary_oarchive oos(file2);
	oos<<b;
	file2.close();
}









