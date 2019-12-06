This is local VERSION CONTROL SYSTEM made by me in c++.

Only Compatible with Unix type filesystem.

Codebase is very messy due to my inexperience :)

To generate the binary:
1.clone it
2.go inside the cloned local repo,and go inside /src folder
3.open terminal in that directory and enter the command below

 g++ -std=c++1z CVS.cpp ../source/Commit.cpp ../source/Blob.cpp ../source/Tree.cpp ../source/commitShow.cpp -lboost_serialization -lboost_filesystem -lboost_system


Any issues is welcomed.

