/******************************************************************************
Title :
Author : Tong Zheng & Andrew Baumann
Created on :
Description :
Build With :
Special Thanks :
******************************************************************************/
#ifndef EDGE_HPP
#define EDGE_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
using namespace std;

template <typename Object>
struct Edge
{
public:
    Edge()
    {
        weight, neighbor = 0;
    }
    bool operator<(const Edge<Object> & other) const
    {
        if(weight < other.weight)
            return true;
        else
            return false;
    }
    int weight;
    int neighbor;
    Object neighbor_data;
};

#endif