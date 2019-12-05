/*
 * commitShow.hpp
 *
 *  Created on: Dec 5, 2019
 *      Author: abhinav
 */

#ifndef COMMITSHOW_HPP_
#define COMMITSHOW_HPP_
#include "../headers/Commit.hpp"
#include "../headers/Blob.hpp"

#include<iostream>
#include<boost/filesystem.hpp>
#include<boost/serialization/vector.hpp>
#include<boost/archive/binary_iarchive.hpp>
#include<fstream>

void saveToVersion(const std::string&);
void makeDirectories(const std::string&,const std::string&);



#endif /* COMMITSHOW_HPP_ */
