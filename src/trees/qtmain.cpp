/******************************************************************************
Title : qtmain.cpp
Author : Andrew Baumann
Created on : 15 October 2014
Description : A program that parses a database and creates either an AVL tree or 
BST, with lazy deletion or without. It searches the tree with the user's query.
The tree code was written by Mark Allan Weiss,but this file was written by the author alone. 
This is part one of two main files.
Build With : 	g++ -std=c++0x qtmain.cpp seqmap.cpp -o qt.exe
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
  if(argc != 3)
    {
      cout << "Error 1: command line arguments incomplete. Rerun." << endl;
      return 0;
    }
  string database = argv[1];
  string flag = argv[2];
  
  if(!readDatabase(database))
    {
      cout << "Error 2: could not read database. Rerun." << endl;
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
     	cout << "Error 3: flag is entered incorrectly. Please retry." << endl;
     	return 0;
      }
    
    return 0;
}

//////////reads database beased on user input
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

/////////prints database
////////
void printTemp()
{
  for(int i=0; i<771; i++)
    cout << "Name:" << tempStore[i][0] << " Condo:" << tempStore[i][1] << " Condo2:" << tempStore[i][2] << endl;
}

/////////runs program using an avl tree
/////////
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

	string query = ""; 

	cout << "Enter recognition sequence for searching: " << endl;
	cin >> query;
	SeqMap seq(query,"");
	vector<string> ans;
	if(avl->contains(seq))
	{
		cout << "Here are the names of the matching sequences:" << endl;
		ans = avl->returnSearch();
		for(int i=0; i<ans.size(); i++)
			cout << ans[i] << ", "; 
		cout << "end of sequences." << endl;
	}
	else
	{
		cout << "Not found." << endl;
	}
	delete avl;
	
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

	string query = ""; 

	cout << "Enter recognition sequence for searching: " << endl;
	cin >> query;
	SeqMap seq(query,"");
	vector<string> ans;
	if(avl->contains(seq))
	{
		cout << "Here are the names of the matching sequences:" << endl;
		ans = avl->returnSearch();
		for(int i=0; i<ans.size(); i++)
			cout << ans[i] << ", "; 
		cout << "end of sequences." << endl;
	}
	else
	{
		cout << "Not found." << endl;
	}
	delete avl;
	
}

//////////runs program using a bst
//////////
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

	string query = ""; 

	cout << "Enter recognition sequence for searching: " << endl;
	cin >> query;
	SeqMap seq(query,"");
	vector<string> ans;
	if(bst->contains(seq))
	{
		cout << "Here are the names of the matching sequences:" << endl;
		ans = bst->returnSearch();
		for(int i=0; i<ans.size(); i++)
			cout << ans[i] << ", "; 
		cout << "end of sequences." << endl;
	}
	else
	{
		cout << "Not found." << endl;
	}
	delete bst;
	
}

/////////runs program using a bst with lazy deletion
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

	string query = ""; 

	cout << "Enter recognition sequence for searching: " << endl;
	cin >> query;
	SeqMap seq(query,"");
	vector<string> ans;
	if(bst->contains(seq))
	{
		cout << "Here are the names of the matching sequences:" << endl;
		ans = bst->returnSearch();
		for(int i=0; i<ans.size(); i++)
			cout << ans[i] << ", "; 
		cout << "end of sequences." << endl;
	}
	else
	{
		cout << "Not found." << endl;
	}
	delete bst;
	
}














