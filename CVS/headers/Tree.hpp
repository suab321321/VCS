/*
 * Tree.hpp
 *
 *  Created on: Dec 2, 2019
 *      Author: abhinav
 */

#ifndef TREE_HPP_
#define TREE_HPP_

#include<iostream>
#include<vector>
#include<boost/archive/binary_oarchive.hpp>
#include<boost/archive/binary_iarchive.hpp>
#include<boost/serialization/vector.hpp>

class Tree{
public:
	const std::vector<std::string>& getBlobs() const {
		return blobs;
	}

	void setBlobs(const std::vector<std::string> &blobs) {
		this->blobs = blobs;
	}

	int getIsFirst() const {
		return isFirst;
	}

	void setIsFirst(int isFirst) {
		this->isFirst = isFirst;
	}

	const std::vector<std::string>& getParentTree() const {
		return parentTree;
	}

	void setParentTree(const std::vector<std::string> &parentTree) {
		this->parentTree = parentTree;
	}

private:
	std::vector<std::string>blobs;
	std::vector<std::string> parentTree;
	int isFirst;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar,const unsigned){
		ar & blobs;
		ar & parentTree;
		ar & isFirst;
	}
};

std::ostream & operator <<(std::ostream&,const Tree&);
void commit(const std::string&);
void moveFromDir(const std::string&,const std::string&,int&);
void createTree(const std::string&);


#endif /* TREE_HPP_ */
