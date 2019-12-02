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

class Commit{
public:
	const std::string& getParentCommit() const {
		return parentCommit;
	}

	void setParentCommit(const std::string &parentCommit) {
		this->parentCommit = parentCommit;
	}

	const std::string& getTree() const {
		return tree;
	}

	void setTree(const std::string &tree) {
		this->tree = tree;
	}

private:
	std::string tree;
	std::string parentCommit;
	friend class::boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar,const unsigned){
		ar & tree;
		ar & parentCommit;
	}
};



#endif /* COMMIT_HPP_ */
