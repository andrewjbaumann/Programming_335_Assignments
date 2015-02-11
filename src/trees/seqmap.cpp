/******************************************************************************
Title : seqmap.cpp
Author : Andrew Baumann
Created on : 13 October 2014
Description : A SeqMap class for use with ttmain or qtmain
Build With : 	g++ -std=c++0x qtmain.cpp seqmap.cpp -o qt.exe OR
				g++ -std=c++0x ttmain.cpp seqmap.cpp -o tt.ex
Special Thanks : Weiss, Mark Allan. Zheng, Tony. Vora, Aarsh. 
******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include "seqmap.hpp"
#include "AvlTree.h"
#include "BinarySearchTree.h" 
using namespace std;

SeqMap::SeqMap(string recog, string enz)
{
  this->recog = recog;
  enzNames.push_back(enz);
}

SeqMap::~SeqMap()
{

}

bool SeqMap::operator==(const SeqMap & two) const
{
	if(this->recog == two.returnRecog())
		return true;

	return false;
}


string SeqMap::returnRecog() const
{
  return recog;
}

vector<string> SeqMap::returnNames() const
{
  return enzNames;
}

void SeqMap::addNames(string name)
{
  enzNames.push_back(name);
}

bool SeqMap::operator<(SeqMap y) const
{//is THIS SeqMap's recog < SeqMap y's recog? if yes, than return 1.
	if(recog < y.returnRecog())
		return true;
	else
		return false;
}

void SeqMap::merge(SeqMap y)
{
	vector<string> yNames = y.returnNames();
	for(int i=0; i<yNames.size(); i++)
	{
		enzNames.push_back(yNames[i]);
	}
}

void SeqMap::printNames() const
{
	for(int i=0; i<enzNames.size(); i++)
	{
		cout << enzNames[i] << " and "; 
	}
	cout << endl;
}





















