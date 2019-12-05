
#include "../headers/Commit.hpp"

using namespace std;

ostream & operator <<(ostream& os,const Commit& commit){
	os<<' '<<commit.getParentCommit()<<commit.getTree();
	return os;
}

//committing the unstagged file
