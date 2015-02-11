/******************************************************************************
Title : ttmain.cpp
Author : Andrew Baumann
Created on : 13 October 2014
Description : A program that parses a database and creates either an AVL tree or 
BST, with lazy deletion or without. The tree code was written by Mark Allan Weiss,
but this file was written by the author alone. This is part one of two main files.
Build With : 	g++ -std=c++0x ttmain.cpp seqmap.cpp -o tt.exe
Special Thanks : Weiss, Mark Allan. Zheng, Tony. Vora, Aarsh. 
******************************************************************************/
#include <iostream>
#include <string>
#include <cmath>
#include "seqmap.hpp"
#include "AvlTree.h"
#include "lazyAvlTree.h"
#include "BinarySearchTree.h"
#include "lazyBinarySearchTree.h"

using namespace std;
string tempStore[780][3]; //array for storing
string tempSearch[420];
bool readDatabase(string database);
void printTemp();
bool readSearch(string searchbase);
void printSearch();
void avlRun(); 
void bstRun();
void avlLazyRun();
void bstLazyRun();
void searchTree();


int main(int argc, char * argv[])
{
  if(argc != 4)
    {
      cout << "Error 1: command line arguments incomplete. Rerun." << endl;
      return 0;
    }
  string database = argv[1];
  string searchbase = argv[2];
  string flag = argv[3];
  
  if(!readDatabase(database))
    {
      cout << "Error 2: could not read database. Rerun." << endl;
      return 0;
    }
    if(!readSearch(searchbase))
    {
      cout << "Error 3: could not read search file. Rerun." << endl;
      return 0;
    }

      if(flag == "AVL")
      	avlRun();
      else if(flag == "LazyAVL")
      	avlLazyRun();
      else if(flag == "BST")
      	bstRun();
      else if(flag == "LazyBST")
      	bstLazyRun();
      else 
      {
     	cout << "Error 4: flag is entered incorrectly. Please retry." << endl;
     	return 0;
      }
    
    return 0;
}

////////reads database from user entry
////////
bool readDatabase(string database)
{
  //opens file
  fstream file;
  file.open(database);
  string line; //reader
  string pusher; //inserts into array 
  size_t find1,find2,find3; //for finding loc of backslashes
  int length1,length2;
  const string backslash =  "/"; //for finding
  
  if(!file.is_open())
    {
      cout << "Could not open file." << endl;
      return false;
    }
  else
    {
      for (int i=0; i<27; i++) //first ten lines of rebase210.txt are garbage
		file >> line;
      for(int i=0; i<771;  i++)
	{
	      file >> line; //reads line from file
	      //then finds location of backslashes for writing
	      find1 = line.find(backslash);
	      find2 = line.find(backslash,find1+1);
	      find3 = line.find(backslash,find2+1);
	      //the length of the first and second rec sequence
	      length1 = find2 - find1+1;
	      length2 = find3 - find2+1;
	      //begins inserting enzyme names and recognition sequences
	      pusher = line.substr(0,find1);
	      tempStore[i][0] = pusher;
	      pusher = line.substr(find1+1,length1);
	      pusher.erase(pusher.end()-2,pusher.end());
	      tempStore[i][1] = pusher;
	      /*if there is a second recgnition sequence (never more than 2) t hen 
		find2 and find 3 should be more than 1 character apart*/ 
	      if (find2+1 != find3)
		{
		  pusher = line.substr(find2+1,length2-2);
		  tempStore[i][2] = pusher;
		}
	      else
		tempStore[i][2] = backslash;
	}
	  //closes file
	  file.close();
    }
  return true;
}

////////prints database from user entry
////////
void printTemp()
{
  for(int i=0; i<771; i++)
    cout << "Name:" << tempStore[i][0] << " Condo:" << tempStore[i][1] << " Condo2:" << tempStore[i][2] << endl;
}

////////reads the database for searching
////////
bool readSearch(string searchbase)
{
  //opens file
  fstream file;
  file.open(searchbase);
  string line; //reader
  string pusher; //inserts into array 
  const string backslash =  "/"; //for finding
  
  if(!file.is_open())
    {
      cout << "Could not open file." << endl;
      return false;
    }
  else
    {
      for(int i=0; i<420;  i++)
      {
	      file >> line; //reads line from file
		  tempSearch[i] = line; 
	  }
	  //closes file
	  file.close();
    }
  return true;
}

////////prints database for searching
////////
void printSearch()
{
	for(int i=0; i<420; i++)
		cout << tempSearch[i] << endl;
}

////////runs program using an avl tree
////////

void avlRun()
{
	AvlTree<SeqMap> * avl = new AvlTree<SeqMap>();
	for(int i=0; i<770; i++)
	{
		string rec = tempStore[i][1];
		string name = tempStore[i][0];
		SeqMap SEQ(rec,name);
		avl->insert(SEQ);
		if(tempStore[i][2] != "/")
		{
			string rec = tempStore[i][2];
			SeqMap SEQ(rec,name);
			avl->insert(SEQ);
		}
	}
	double inserts = avl->returnIC();
	cout << "Number of inserts after creation: " << inserts << "." << endl;
	double nodes = avl->getNum();
	cout << "There are " << nodes << " nodes in the tree." << endl;
	double height = avl->height();
	cout << "The height is: " << height << "." << endl;
	double internalPath = avl->path();
	cout << "The length of the internal path is: " << internalPath << "." << endl;
	double avgDepth = internalPath/nodes; 
	cout << "The average depth is: " << avgDepth << "." << endl;
	double log2n = log(nodes) / log(2);
	double ratio = avgDepth/log2n;
	cout << "The ratio of avg depth to log base 2 of n is: " << ratio << "." << endl;
	int finds = 0;
	//time for search 
	for(int i=0; i<420; i++)
	{
		string name = "default";
		const SeqMap SEQ(tempSearch[i],name);
		if(avl->contains(SEQ))
			finds++;
	}
	cout << "The number of successful searches in the tree was " << finds << "." << endl;
	cout << "The number of calls to contains is " << avl->returnCC() << "." << endl;

	for(int i=0; i<420; i++)
	{
		string name = "default";
		const SeqMap SEQ(tempSearch[i],name);
		avl->remove(SEQ);
		i++;		
	}

	cout << "The number of successful removes in the tree was: " << avl->returnRemove() << endl;
	cout << "The number of calls to the remove function was: " << avl->returnRC() << endl;
	cout << endl;
	//
	avl->reset();
	finds=0;
	//
	nodes = avl->getNum();
	cout << "There are " << nodes << " nodes in the tree." << endl;
	height = avl->height();
	cout << "The height is: " << height << "." << endl;
	internalPath = avl->path();
	cout << "The length of the internal path is: " << internalPath << "." << endl;
	avgDepth = internalPath/nodes; 
	cout << "The average depth is: " << avgDepth << "." << endl;
	log2n = log(nodes) / log(2);
	ratio = avgDepth/log2n;
	cout << "The ratio of avg depth to log base 2 of n is: " << ratio << "." << endl;

	//time for search 
	for(int i=0; i<420; i++)
	{
		string name = "default";
		const SeqMap SEQ(tempSearch[i],name);
		if(avl->contains(SEQ))
			finds++;
	}
	cout << "The number of searches in the tree was " << finds << "." << endl;
	cout << "The number of calls to contains is " << avl->returnCC() << "." << endl;

}

/////////runs program using an avl tree with lazy deletion
/////////
void avlLazyRun()
{
	lazyAvlTree<SeqMap> * avl = new lazyAvlTree<SeqMap>();
	for(int i=0; i<770; i++)
	{
		string rec = tempStore[i][1];
		string name = tempStore[i][0];
		SeqMap SEQ(rec,name);
		avl->insert(SEQ);
		if(tempStore[i][2] != "/")
		{
			string rec = tempStore[i][2];
			SeqMap SEQ(rec,name);
			avl->insert(SEQ);
		}
	}
	double inserts = avl->returnIC();
	cout << "Number of inserts after creation: " << inserts << "." << endl;
	double nodes = avl->getNum();
	cout << "There are " << nodes << " nodes in the tree." << endl;
	double height = avl->height();
	cout << "The height is: " << height << "." << endl;
	double internalPath = avl->path();
	cout << "The length of the internal path is: " << internalPath << "." << endl;
	double avgDepth = internalPath/nodes; 
	cout << "The average depth is: " << avgDepth << "." << endl;
	double log2n = log(nodes) / log(2);
	double ratio = avgDepth/log2n;
	cout << "The ratio of avg depth to log base 2 of n is: " << ratio << "." << endl;
	int finds = 0;
	//time for search 
	for(int i=0; i<420; i++)
	{
		string name = "default";
		const SeqMap SEQ(tempSearch[i],name);
		if(avl->contains(SEQ))
			finds++;
		
	}
	cout << "The number of successful searches in the tree was " << finds << "." << endl;
	cout << "The number of calls to contains is " << avl->returnCC() << "." << endl;
	//remove every other from sequence.txt
	for(int i=0; i<420; i++)
	{
		string name = "default";
		const SeqMap SEQ(tempSearch[i],name);
		avl->remove(SEQ);	
		i++;		
	}

	cout << "The number of successful removes in the tree was: " << avl->returnRemove() << endl;
	cout << "The number of calls to the remove function was: " << avl->returnRC() << endl;

	//
	avl->reset();
	finds=0;
	//
	nodes = avl->getNum();
	cout << "There are " << nodes << " nodes in the tree." << endl;
	height = avl->height();
	cout << "The height is: " << height << "." << endl;
	internalPath = avl->path();
	cout << "The length of the internal path is: " << internalPath << "." << endl;
	avgDepth = internalPath/nodes; 
	cout << "The average depth is: " << avgDepth << "." << endl;
	log2n = log(nodes) / log(2);
	ratio = avgDepth/log2n;
	cout << "The ratio of avg depth to log base 2 of n is: " << ratio << "." << endl;

	//time for search 
	for(int i=0; i<420; i++)
	{
		string name = "default";
		const SeqMap SEQ(tempSearch[i],name);
		if(avl->contains(SEQ))
			finds++;
	}
	cout << "The number of successful searches in the tree was " << finds << "." << endl;
	cout << "The number of calls to contains is " << avl->returnCC() << "." << endl;
}

/////////runs program using an bst
/////////
void bstRun()
{
	BinarySearchTree<SeqMap> * bst = new BinarySearchTree<SeqMap>();
	for(int i=0; i<770; i++)
	{
		string rec = tempStore[i][1];
		string name = tempStore[i][0];
		SeqMap SEQ(rec,name);
		bst->insert(SEQ);
		if(tempStore[i][2] != "/")
		{
			string rec = tempStore[i][2];
			SeqMap SEQ(rec,name);
			bst->insert(SEQ);
		}
	}
	double inserts = bst->returnIC();
	cout << "Number of inserts after creation: " << inserts << "." << endl;
	double nodes = bst->getNum();
	cout << "There are " << nodes << " nodes in the tree." << endl;
	double height = bst->height();
	cout << "The height is: " << height << "." << endl;
	double internalPath = bst->path();
	cout << "The length of the internal path is: " << internalPath << "." << endl;
	double avgDepth = internalPath/nodes; 
	cout << "The average depth is: " << avgDepth << "." << endl;
	double log2n = log(nodes) / log(2);
	double ratio = avgDepth/log2n;
	cout << "The ratio of avg depth to log base 2 of n is: " << ratio << "." << endl;
	int finds = 0;
	//time for search 
	for(int i=0; i<420; i++)
	{
		string name = "default";
		const SeqMap SEQ(tempSearch[i],name);
		if(bst->contains(SEQ))
			finds++;
	}
	cout << "The number of successful searches in the tree was " << finds << "." << endl;
	cout << "The number of calls to contains is " << bst->returnCC() << "." << endl;
	//remove every other from sequence.txt
	for(int i=0; i<420; i++)
	{
		string name = "default";
		const SeqMap SEQ(tempSearch[i],name);
		bst->remove(SEQ);	
		i++;		
	}

	cout << "The number of successful removes in the tree was: " << bst->returnRemove() << endl;
	cout << "The number of calls to the remove function was: " << bst->returnRC() << endl;

	//
	bst->reset();
	finds=0;
	//
	nodes = bst->getNum();
	cout << "There are " << nodes << " nodes in the tree." << endl;
	height = bst->height();
	cout << "The height is: " << height << "." << endl;
	internalPath = bst->path();
	cout << "The length of the internal path is: " << internalPath << "." << endl;
	avgDepth = internalPath/nodes; 
	cout << "The average depth is: " << avgDepth << "." << endl;
	log2n = log(nodes) / log(2);
	ratio = avgDepth/log2n;
	cout << "The ratio of avg depth to log base 2 of n is: " << ratio << "." << endl;

	//time for search 
	for(int i=0; i<420; i++)
	{
		string name = "default";
		const SeqMap SEQ(tempSearch[i],name);
		if(bst->contains(SEQ))
			finds++;
	}
	cout << "The number of successful searches in the tree was " << finds << "." << endl;
	cout << "The number of calls to contains is " << bst->returnCC() << "." << endl;
}

/////////runs program using an bst with lazy deletion
/////////
void bstLazyRun()
{
	lazyBinarySearchTree<SeqMap> * bst = new lazyBinarySearchTree<SeqMap>();
	for(int i=0; i<770; i++)
	{
		string rec = tempStore[i][1];
		string name = tempStore[i][0];
		SeqMap SEQ(rec,name);
		bst->insert(SEQ);
		if(tempStore[i][2] != "/")
		{
			string rec = tempStore[i][2];
			SeqMap SEQ(rec,name);
			bst->insert(SEQ);
		}
	}
	double inserts = bst->returnIC();
	cout << "Number of inserts after creation: " << inserts << "." << endl;
	double nodes = bst->getNum();
	cout << "There are " << nodes << " nodes in the tree." << endl;
	double height = bst->height();
	cout << "The height is: " << height << "." << endl;
	double internalPath = bst->path();
	cout << "The length of the internal path is: " << internalPath << "." << endl;
	double avgDepth = internalPath/nodes; 
	cout << "The average depth is: " << avgDepth << "." << endl;
	double log2n = log(nodes) / log(2);
	double ratio = avgDepth/log2n;
	cout << "The ratio of avg depth to log base 2 of n is: " << ratio << "." << endl;
	int finds = 0;
	//time for search 
	for(int i=0; i<420; i++)
	{
		string name = "default";
		const SeqMap SEQ(tempSearch[i],name);
		if(bst->contains(SEQ))
			finds++;
	}
	cout << "The number of successful searches in the tree was " << finds << "." << endl;
	cout << "The number of calls to contains is " << bst->returnCC() << "." << endl;
	//remove every other from sequence.txt
	for(int i=0; i<420; i++)
	{
		string name = "default";
		const SeqMap SEQ(tempSearch[i],name);
		bst->remove(SEQ);	
		i++;		
	}

	cout << "The number of successful removes in the tree was: " << bst->returnRemove() << endl;
	cout << "The number of calls to the remove function was: " << bst->returnRC() << endl;

	//
	bst->reset();
	finds=0;
	//
	nodes = bst->getNum();
	cout << "There are " << nodes << " nodes in the tree." << endl;
	height = bst->height();
	cout << "The height is: " << height << "." << endl;
	internalPath = bst->path();
	cout << "The length of the internal path is: " << internalPath << "." << endl;
	avgDepth = internalPath/nodes; 
	cout << "The average depth is: " << avgDepth << "." << endl;
	log2n = log(nodes) / log(2);
	ratio = avgDepth/log2n;
	cout << "The ratio of avg depth to log base 2 of n is: " << ratio << "." << endl;

	//time for search 
	for(int i=0; i<420; i++)
	{
		string name = "default";
		const SeqMap SEQ(tempSearch[i],name);
		if(bst->contains(SEQ))
			finds++;
	}
	cout << "The number of successful searches in the tree was " << finds << "." << endl;
	cout << "The number of calls to contains is " << bst->returnCC() << "." << endl;
}














