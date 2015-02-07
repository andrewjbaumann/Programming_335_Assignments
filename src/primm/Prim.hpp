/******************************************************************************
Title :
Author : Tong Zheng & Andrew Baumann
Created on :
Description :
Build With :
Special Thanks :
******************************************************************************/
#ifndef PRIM_HPP
#define PRIM_HPP
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>
#include "Vertex.hpp"
#include "Adjacency_List.hpp"
#include "BinaryHeap.hpp"
using namespace std;

template <typename Object>
class Prim
{
private:
    AList<string> undirected_graph;
    BinaryHeap<Edge<string>> heap_of_edges;
    string doc_name;
    fstream document;

public:
    //the Prim constructor
    Prim()
    {}

    /*
    the used constructor. builds the adjacency list(using Vertex) from the text file and then
    builds a binary heap from the adjacency list (using edges). obtains the searching name
    and the requested tree depth from the user. is the running portion of the code
     */
    Prim(string document_name)
    {
        Vertex<string> *  vertex;
        doc_name = document_name;
        if(!process_document())
            cout << "Error 2: Could not open file. Rerun." << endl;
        else
        {
            string searching_name;
            string depth_string;
            int depth = 0;
            cout << "Enter a name?" << endl;
            bool acceptable = false;
            //uses a STRING to find VERTEX
            while(!acceptable)
            {
                cin >> searching_name;
                int temp = undirected_graph.find_node(searching_name);
                if (-1 == temp)
                    cout << "Error 3: Name not in .txt file. Try again: " << endl;
                else
                {
                    undirected_graph.return_pointer(temp, vertex);
                    acceptable=true;
                }
            }
            acceptable=false;
            cout << "What is the depth?: " << endl;
            //error catching for finding the depth
            while(!acceptable)
            {
                cin >> depth_string;
                for (int i = 0; i < depth_string.size(); i++)
                    if (!isdigit(depth_string[i]))
                        cout << "Error: incorrect input. Try again: " << endl;
                depth = atoi(depth_string.c_str());
                if (depth < 0)
                    cout << "Error: depth cannot be a negative number. Try again: " << endl;
                else
                    acceptable=true;
            }
            build_tree(vertex, depth);
            cout << vertex->data << "(0)" << endl;
            print_tree();
            vertex = 0;
        }
        delete vertex;
        cout << "Thank you for playing." << endl;
    }
    //the Prim destructor
    ~Prim()
    {

    }

    //builds an MST based on depth
    void build_tree(Vertex<string> *& vertex, int depth)
    {
        if(depth == 0)
            return;
        int name = vertex->vertex_name;
        for(int i = 0; i<vertex->neighbors.size(); i++)
        {
            if(vertex->weights[i] <= depth)
            {
                Edge<string> edge;
                edge.neighbor = vertex->neighbors[i];
                edge.neighbor_data = undirected_graph.return_node_data(edge.neighbor);
                edge.weight = vertex->weights[i];
                Edge<string> const temp = edge;
                heap_of_edges.insert(temp);
            }
        }
    }

    //prints and empties the tree
    void print_tree()
    {
        while(!heap_of_edges.isEmpty())
        {
            Edge<string> edge;
            heap_of_edges.deleteMin(edge);
            Object temp_data = edge.neighbor_data;
            int temp_weight = edge.weight;
            int temp_name = edge.neighbor;
            cout << temp_data << "(" << temp_weight << ")" << endl;
        }
    }


    //processes the database.txt file
    bool process_document()
    {
        fstream file;
        string line; //reader
        file.open(doc_name);
        if(!file.is_open())
            return false;
        int count = 0;
        while(file.good())
        {
            file >> line;
            undirected_graph.add_node(count,line);
            count++;
        }
        file.close();
        return true;
    }




};

#endif