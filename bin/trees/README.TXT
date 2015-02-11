PLEASE COMPILE BOTH FILES USING C++
This project is two seperate mains: 
ttmain(test trees) and qtmain(query trees). 
The makefile is optional, and 
it compiles both files. 


all:
	
g++ -std=c++0x qtmain.cpp seqmap.cpp -o qt.exe
	
g++ -std=c++0x ttmain.cpp seqmap.cpp -o tt.exe



The files AvlTree.h, dsexecptions.h, and BinarySearchTree.h were taken directly from Mark Weiss' 
source code: 
http://users.cis.fiu.edu/~weiss/. Files lazyAvlTree.h and lazyBinarySearchTree.h 
are 
just modified from their parent file. They contain minor edits by the author, and places
where edits were made 
are noted in the comments.



Created by Andrew Baumann (using Mark Weiss' trees code). 



