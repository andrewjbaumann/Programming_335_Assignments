/******************************************************************************
Title :
Author : Tong Zheng & Andrew Baumann
Created on :
Description :
Build With :
Special Thanks :
******************************************************************************/
#ifndef VERTEX_HPP
#define VERTEX_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
using namespace std;

template <typename Object>
class Vertex
{
public:
    Vertex()
    {
        vertex_name = 0;
    }
    int vertex_name; //A vertex's name
    Object data; //the data they hold
    vector<int> neighbors; //its connected nodes in the graph
    vector<int> weights;
    /* between a node and its neighbor[i], it will have a connected
       weight of weight[i]*/

    //equals operator
    void operator=(Vertex other)
    {
        vertex_name = other.vertex_name;
        data = other.data;
        for(int i=0; i<neighbors.size(); i++)
        {
            int new_neighbor = neighbors.at(i);
            other.neighbors.push_back(new_neighbor);
        }
        for(int i=0; i<weights.size(); i++)
        {
            int new_weight = weights.at(i);
            other.weights.push_back(new_weight);
        }
    }
    vector<bool> weight_in_tree;
};

#endif