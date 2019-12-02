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

class Blob{
public:
	const std::map<int, std::string>& getContent() const {
		return content;
	}

	void setContent(const std::map<int, std::string> &content) {
		this->content = content;
	}

	const std::string& getFileName() const {
		return fileName;
	}

	void setFileName(const std::string &fileName) {
		this->fileName = fileName;
	}

	virtual std::unordered_set<std::string> getFiles(std::unordered_set<std::string>&,const char*);

//	std::ostream & operator << (std::ostream&,const Blob&);

private:
	std::string fileName;
	std::map<int,std::string>content;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar,const unsigned){
		ar & fileName;
		ar & content;
	}
};
std::ostream & operator <<(std::ostream& os,const Blob& blob){
	os<<' '<<blob.getFileName();
	for(auto i:blob.getContent())
		os<<i.first<<i.second;
	return os;
}


#endif /* BLOB_HPP_ */
