This is local VERSION CONTROL SYSTEM made in c++.
Not full like git.This just tracks you have made anychanges in projects which is under /files dir and if changes are found they you can add-->commit-->push.This will make a /files in VERSIONS with time as folder name stores how your current project is in /files dir.

Only Compatible with Unix type filesystem.

Codebase is very messy due to my inexperience :) if you want to contact regarding anything with project reach me on singhabhinav0796@gmail.com

To generate the binary:
1.clone it
2.go inside the cloned local repo,and go inside /src folder
3.open terminal in that directory and enter the command below

 g++ -std=c++1z CVS.cpp ../source/Commit.cpp ../source/Blob.cpp ../source/Tree.cpp ../source/commitShow.cpp -lboost_serialization -lboost_filesystem -lboost_system


0-git init(compulsory to initialize .git dir only first time require)
1-git add(changes are stagged to for commit in future)
2-git commit(changes are ready to be pushed)
3-git push(you successfully made a new version of your project in /VERSION dir)

Please report any issues if found.

