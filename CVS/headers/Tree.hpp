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

class Tree{
public:

	const std::vector<std::string>& getBlobs() const {
		return blobs;
	}

	void setBlobs(const std::vector<std::string> &blobs) {
		this->blobs = blobs;
	}

	const std::string& getParentTree() const {
		return parentTree;
	}

	void setParentTree(const std::string &parentTree) {
		this->parentTree = parentTree;
	}

private:
	std::vector<std::string>blobs;
	std::string parentTree;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar,const unsigned){
		ar & blobs;
		ar & parentTree;
	}
};

std::ostream & operator <<(std::ostream& os,const Tree& tree){
	os<<' '<<tree.getParentTree();
	for(auto i:tree.getBlobs())
		os<<i;
	return os;
}



#endif /* TREE_HPP_ */
