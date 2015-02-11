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
#include "AvlTree.h"
#include "BinarySearchTree.h" 

#ifndef SEQMAP_HPP
#define SEQMAP_HPP

using namespace std;
class SeqMap
{
public:
  SeqMap(string recog, string enz);
  ~SeqMap();
  bool operator==(const SeqMap & two) const;
  string returnRecog() const;
  vector<string> returnNames() const;
  bool operator<(SeqMap y) const;
  void addNames(string name);
  void merge(SeqMap y);
  void printNames() const;
private:
  string recog; 
  vector<string> enzNames;
};

#endif
