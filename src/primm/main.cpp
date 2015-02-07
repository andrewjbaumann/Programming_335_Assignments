/******************************************************************************
Title :
Author : Tong Zheng & Andrew Baumann
Created on :
Description :
Build With :
Special Thanks :
******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Vertex.hpp"
#include "Adjacency_List.hpp"
#include "Prim.hpp"
using namespace std;

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        cout << "Error 1: command line arguments incomplete. Rerun." << endl;
        return 0;
    }

    string file=argv[1];
    Prim<string> * DRAGON;
    DRAGON = new Prim<string>(file);
    delete DRAGON;
    return 0;
}