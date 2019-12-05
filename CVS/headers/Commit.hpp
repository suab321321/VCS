/*
 * Commit.hpp
 *
 *  Created on: Dec 2, 2019
 *      Author: abhinav
 */

#ifndef COMMIT_HPP_
#define COMMIT_HPP_

#include<iostream>
#include<boost/archive/binary_oarchive.hpp>
#include<boost/archive/binary_iarchive.hpp>
#include<boost/filesystem.hpp>

class Commit{
public:
	const std::string& getTree() const {
		return tree;
	}

	void setTree(const std::string &tree) {
		this->tree = tree;
	}

private:
	std::string tree;
	friend class::boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar,const unsigned){
		ar & tree;
	}
};
std::ostream & operator <<(std::ostream& os,const Commit&);
void push(const std::string&);
bool move(const std::string&,const std::string&);
void createCommit(const std::string&);

#endif /* COMMIT_HPP_ */
