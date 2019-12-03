/*
 * Blob.hpp
 *
 *  Created on: Dec 2, 2019
 *      Author: abhinav
 */

#ifndef BLOB_HPP_
#define BLOB_HPP_

#include<iostream>
#include<map>
#include<unordered_set>
#include<boost/serialization/map.hpp>
#include<boost/archive/binary_oarchive.hpp>
#include<boost/archive/binary_iarchive.hpp>
#include<boost/filesystem.hpp>
#include<set>
namespace fs=boost::filesystem;
class Blob{
public:
	Blob(){}

	const std::map<int, std::string>& getContent() const {
		return content;
	}

	void setContent(const std::map<int, std::string> &content) {
		this->content = content;
	}

	const std::string& getFilePath() const {
		return filePath;
	}

	void setFilePath(const std::string &filePath) {
		this->filePath = filePath;
	}

private:
	std::string filePath;
	std::map<int,std::string>content;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar,const unsigned){
		ar & filePath;
		ar & content;
	}
};

std::ostream & operator <<(std::ostream&,const Blob&);
void getFiles(std::unordered_set<std::string>&,const char*);
bool compare(const char*,const char*);
void add(const std::string&);
void getBlobs(std::unordered_set<std::string>&,const char*);
void stagADD(const std::string&,const std::string&);
void stagDELETE(const std::string&,const std::string&);

#endif /* BLOB_HPP_ */
