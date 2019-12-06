#include "../headers/Blob.hpp"
#include<boost/filesystem.hpp>
#include<fstream>
#include<unordered_map>
#include<functional>
#include<sstream>
#include<chrono>
#include<ctime>


namespace fs=boost::filesystem;
using namespace std;

//serializing << operator overload
ostream & operator << (ostream& os,const Blob& blob){
	os<<' '<<blob.getFilePath()<<blob.getIsDelete();
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
	getBlobs(Blobs,(CWD+"/.git/blob/unstagged").c_str());
	cout<<Blobs.size()<<" "<<Files.size()<<endl;
	int isChanged=0;
	//files that were added or changed whose saved binary should also be altered is done here
	for(auto i:Files){
		if(Blobs.find(i)==Blobs.end()){
			isChanged=1;
			stagADD(i,CWD);
		}
		else{
			if(!compare(i.c_str(),(CWD+"/.git/blob/unstagged").c_str())){
				isChanged=1;
				stagADD(i,CWD);
			}
		}
	}
	//removing saved binary file when that particular file was removed from the main directory
	for(auto i:Blobs){
		if(Files.find(i)==Files.end()){
			isChanged=1;
			stagDELETE(i,CWD);
		}
	}
	if(!isChanged){
		cout<<"No changes were made"<<endl;
		return;
	}
	const string blobIntermidiate=CWD+"/.git/blob/intermidiate";
	const string blobUnstagged=CWD+"/.git/blob/unstagged";
	//moving the files from unstagged dir to stagged dir
	moveFromDir(blobIntermidiate,blobUnstagged);
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
				if(!b.getIsDelete()){
					Blobs.insert(b.getFilePath());
					file.close();
				}
			}
		}
	}catch(fs::filesystem_error& ex){
		cout<<ex.what();
	}
}
//ends//

bool compare(const char* filePath,const char* blobDir){
	map<int,string>content;
	fs::path toBeRemoved;
	for(fs::directory_entry& ent:fs::recursive_directory_iterator(blobDir)){
		if(fs::is_regular_file(ent.path())){
			ifstream file(ent.path().string().c_str());
			boost::archive::binary_iarchive ios(file);
			Blob b;
			ios>>b;
			file.close();
			if(!b.getFilePath().compare(filePath)){
				toBeRemoved=ent.path();
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
	else{
		fs::remove(toBeRemoved);
		return 0;
	}
	file.close();
	if(fileContent.size()!=content.size()){
		fs::remove(toBeRemoved);
		return 0;
	}
	for(auto i:content){
		if(fileContent[i.first]!=i.second){
			fs::remove(toBeRemoved);
			return 0;
		}
	}
	return 1;
}

//adding new files or changed file
void stagADD(const string& filePath,const string& CWD){
	cout<<"Added or changed "<<filePath<<endl;
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
	b.setIsDelete(0);
	stringstream ss;
	auto t=chrono::system_clock::to_time_t(chrono::system_clock::now());
	auto time=ctime(&t);
	size_t h=hash<string>{}(filePath+time);
	ss<<h;
	string hashPath=ss.str();
	ss.clear();
	fs::path p=CWD+"/.git/blob/unstagged/"+hashPath;
	ofstream file2((CWD+"/.git/blob/unstagged/"+hashPath).c_str());
	boost::archive::binary_oarchive oos(file2);
	oos<<b;
	file2.close();
}

//deleting files whose path as given as paramter from unstagged dir
void stagDELETE(const string& filePath,const string& CWD){
	cout<<"deleted "<<filePath<<endl;
	fs::path p=CWD+"/.git/blob/unstagged";
	for(fs::directory_entry& ent:fs::recursive_directory_iterator(p)){
		ifstream file(ent.path().string());
		boost::archive::binary_iarchive ois(file);
		Blob b;
		ois>>b;
		if(b.getFilePath()==filePath){
			fs::remove(ent.path());
			break;
		}
	}
	fs::path dirPath=CWD+"/.git/blob/unstagged";
	Blob blob;
	blob.setFilePath(filePath);
	blob.setIsDelete(1);
	blob.setContent({{}});
	auto t=chrono::system_clock::to_time_t(chrono::system_clock::now());
	auto time=ctime(&t);
	stringstream ss;
	ss<<hash<string>{}(dirPath.string()+time);
	string hashPath=ss.str();
	ofstream file(dirPath.string()+"/"+hashPath);
	boost::archive::binary_oarchive ois(file);
	ois<<blob;
	file.close();
}

//moving files from one directory to another with paths given as paramter
void moveFromDir(const string& toPath,const string& fromPath){
	fs::path To=toPath;
	fs::path From=fromPath;
	fs::permissions(To,fs::all_all);
	fs::remove_all(toPath);
	bool create=fs::create_directory(To);
	if(!create)
		return;
	for(fs::directory_entry& ent:fs::directory_iterator(From)){
		if(fs::is_regular_file(ent.path())){
			fs::path intermediatePath=toPath+"/"+ent.path().filename().string();
				try{
					string to=toPath+"/"+ent.path().filename().string();
					fs::path To1=to;
					try{
						fs::copy_file(ent.path(),To1);
					}catch(fs::filesystem_error& ex){
						cout<<ex.what()<<endl;
					}
				}catch(fs::filesystem_error& ex){
					cout<<ex.what()<<endl;
			}
		}
	}
}
