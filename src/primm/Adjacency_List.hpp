/******************************************************************************
Title :
Author : Tong Zheng & Andrew Baumann
Created on :
Description :
Build With :
Special Thanks :
******************************************************************************/
#ifndef ADJACENCY_LIST_HPP
#define ADJACENCY_LIST_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include "Vertex.hpp"
using namespace std;

template <typename Object>
class AList
{
private:
    vector<Vertex<string>> list_of_names; //the graph of Nodes

public:
    //default constructor
    AList()
    {}

    //constructor with doc_name
    AList(string file_name)
    {}

    //destructor
    ~AList()
    {}

    //equals operator
    void operator=(const AList other)
    {
        for (unsigned long i = 0; i < list_of_names.size(); i++)
        {
            Vertex<string> new_node = other.list_of_names.at(i);
            list_of_names.push_back(new_node);
        }
    }

    //adds a node to the graph by the values (creates a new node from scratch)
    void add_node(int v_name, Object d_data)
    {
        Vertex<string> new_node;
        new_node.vertex_name = v_name;
        new_node.data = d_data;
        for(unsigned long i=0; i< list_of_names.size(); i++)
        {
            Object temp1 = list_of_names[i].data;
            Object temp2 = d_data;
            int distance = levenshtein(temp1, temp2);
            /*
            if the levenshtein distance between new_node
            and graph[i]node is <= 4, then they are neighbors
            with a weight of the levenshtein distance
            we add that
             */
            if(distance <= 4)
            {
                new_node.neighbors.push_back(list_of_names[i].vertex_name);
                new_node.weights.push_back(distance);
                list_of_names[i].neighbors.push_back(v_name);
                list_of_names[i].weights.push_back(distance);
            }
        }

        list_of_names.push_back(new_node);
        return;
    }

    //adds a node to the tree using an already made node pointer
    void add_node(Vertex<string> new_node)
    {
        list_of_names.push_back(new_node);
        return;
    }

    //finds a node and prints its neighbors (edges)
    bool testing_find_node(Object data)
    {
        for(int i=0; i< list_of_names.size(); i++)
        {
            if(list_of_names[i].data == data)
            {
                for(int j=0; j< list_of_names[i].neighbors.size(); j++)
                {
                    int neighbor = list_of_names[i].neighbors[j];
                    int weight = list_of_names[i].weights[j];
                    for(int a=0; a< list_of_names.size(); a++)
                    {
                        if(list_of_names[a].vertex_name == neighbor)
                        {
                            cout << list_of_names[a].data << "(" << weight << ")" << endl;
                        }
                    }
                }
                return true;
            }
        }
        return false;
    }

    //finds a node and returns its name. returns -1 if not found.
    int find_node(Object data)
    {
        for(int i=0; i< list_of_names.size(); i++)
            if(list_of_names[i].data == data)
                return list_of_names[i].vertex_name;

        return -1;
    }

    //finds a node and returns its data.
    Object return_node_data(int node)
    {
        for(int i=0; i<list_of_names.size(); i++)
            if(list_of_names[i].vertex_name == node)
                return list_of_names[i].data;
    }

    //
    void return_pointer(unsigned long name, Vertex<string> *& pointer)
    {
        for(int i=0; i<list_of_names.size(); i++)
        {
            if(list_of_names[i].vertex_name == name)
            {
                pointer = & list_of_names[i];
                return;
            }
        }
        return;
    }

    //
    void return_pointer(int name, Vertex<string> *& pointer)
    {
        for(int i=0; i<list_of_names.size(); i++)
        {
            if(list_of_names[i].vertex_name == name)
            {
                pointer = & list_of_names[i];
                return;
            }
        }
        return;
    }

    //Vertex * find_node(int name);
    //prints the graph all nice and shit
    void print_graph()
   {
       for(unsigned long i=0; i< list_of_names.size(); i++)
       {
           cout << "Vertex: " << list_of_names.at(i).vertex_name;
           cout << "   Data: " << list_of_names.at(i).data;
           cout << "   Neighbors:  ";
           for(int j=0; j< list_of_names.at(i).neighbors.size(); j++)
           {
               int temp;
               temp = list_of_names.at(i).neighbors.at(j);
               cout << temp << ",";
           }
           cout << "    Weights:   ";
           for(int j=0; j< list_of_names.at(i).weights.size(); j++)
           {
               int temp;
               temp = list_of_names.at(i).weights.at(j);
               cout << temp << ",";
           }
           cout << endl;
       }
       return;
   }

    //used http://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C.2B.2B
    unsigned int levenshtein(const Object &s1, const Object &s2)
    {
        const size_t len1 = s1.size(), len2 = s2.size();
        vector<unsigned int> col(len2+1), prevCol(len2+1);

        for (unsigned int i = 0; i < prevCol.size(); i++)
            prevCol[i] = i;
        for (unsigned int i = 0; i < len1; i++) {
            col[0] = i+1;
            for (unsigned int j = 0; j < len2; j++)
                col[j+1] = std::min( std::min(prevCol[1 + j] + 1, col[j] + 1),
                        prevCol[j] + (s1[i]==s2[j] ? 0 : 1) );
            col.swap(prevCol);
        }
        return prevCol[len2];
    }

    //returns size of vector
    unsigned long return_size()
    {
        return list_of_names.size();
    }
};
#endif