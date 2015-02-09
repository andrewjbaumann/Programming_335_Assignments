/******************************************************************************
Title : BinaryHeap.hpp
Author : Mark Weiss
Created on : 13 October 2014
Description : A binary heap class used in the battle simulator.
Changes made by Andrew Baumann.
Special Thanks : Weiss, Mark Allan. Zheng, Tony.
******************************************************************************/
#ifndef _BINARY_HEAP_HPP_
#define _BINARY_HEAP_HPP_

#include "dsexceptions.hpp"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "QuadraticProbing.hpp"
using namespace std;

// binaryHeap class
//
// CONSTRUCTION: with an optional capacity (that defaults to 100)
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item]q
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <class Comparable>
class binaryHeap
{
public:
	// Constructors
    explicit binaryHeap(int capacity = 100) : array(capacity + 1), currentSize{0}
    {
    }
	
    explicit binaryHeap(const vector<Comparable> & items) : array(items.size() + 10), currentSize{static_cast <int>(items.size())},
                                                            hashTable{static_cast <int>(items.size())}
    {
        for(int i = 0; i < items.size(); ++i)
        {   array[i + 1] = items[i];    }
        buildHeap();
    }

    bool isEmpty() const
    {   return currentSize == 0;    }

    /**
     * Find the smallest item in the priority queue.
     * Return the smallest item, or throw Underflow if empty.
     */
    const Comparable & findMin() const
    {
        if(isEmpty())
        {   throw UnderflowException{}; }
        return array[1];
    }
    
    /**
     * Insert item x, allowing duplicates.
     */
    void insert(const Comparable & x)
    {
        if(currentSize == array.size() - 1)
        {   array.resize(array.size() * 2); }
		
        array[++currentSize] = x;
		hashTable.insert(x, currentSize);
        percolateUp(currentSize);
    }
    
    /**
     * Insert item x, allowing duplicates.
     */
    void insert(Comparable && x)
    {
        if(currentSize == array.size() - 1)
        {   array.resize( array.size() * 2);    }

        int hole = ++currentSize;
        
        for(; (hole > 1) && (x < array[hole / 2]); hole /= 2)
        {   array[hole] = std::move(array[hole / 2]);   }
        
        array[hole] = std::move(x);
		hashTable.insert(x, hole);
    }
    
    /**
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     */
    void deleteMin()
    {
        if(isEmpty())
        {   throw UnderflowException{}; }
		
        hashTable.remove(array[1]);
        array[1] = std::move( array[currentSize--]);
        hashTable[array[1]] = 1;
        percolateDown(1);
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws Underflow if empty.
     */
    void deleteMin(Comparable & minItem)
    {
        if(isEmpty())
        {   throw UnderflowException{}; }
		
        hashTable.remove(array[1]);
        minItem = std::move(array[1]);
        array[1] = std::move(array[currentSize--]);
        hashTable[array[1]] = 1;
        percolateDown(1);
    }

    void makeEmpty()
    {hashTable.makeEmpty(); currentSize = 0;}

	void increaseKey(int key, int time)
    {array[key] += time;    percolateDown(key);}
    
	void decreaseKey(int key, int time)
    {array[key] -= time;    percolateUp(key);}

	void increaseKey(Comparable obj, int time)
    {int pos = hashTable[obj];  increaseKey(pos, time);}

	void decreaseKey(Comparable obj, int time)
    {int pos = hashTable[obj];decreaseKey(pos, time);}
    
	void remove(int key)
    {
		array[key] = array[1] - 1;
        percolateUp(key);
        deleteMin();
	}
    
	int getPos(Comparable obj)
    {
        return hashTable[obj];
    }

private:
    int currentSize; // Number of elements in heap
    vector<Comparable> array; // The heap array
    HashTable<Comparable, int> hashTable;

    /**
     * Establish heap order property from an arbitrary
     * arrangement of items. Runs in linear time.
     */
    void buildHeap()
    {
        for(int i = currentSize / 2; i > 0; i--)
        {   percolateDown(i);   }
    }

	int percolateUp(int hole)
    {
		Comparable tmp = array[hole];
        array[0] = std::move(tmp);

		for (; tmp < array[hole / 2]; hole /= 2)
        {
			array[hole] = std::move(array[hole / 2]);
            hashTable[array[hole]] = hole;
		}

		array[hole] = std::move(array[0]);
        hashTable[array[hole]] = hole;
        return hole;
	}
	
	/**
     * Internal method to percolate down in the heap.
     * hole is the index at which the percolate begins.
     */
    int percolateDown(int hole)
    {
        int child;
        Comparable tmp = std::move(array[hole]);

        for(; hole * 2 <= currentSize; hole = child)
        {
            child = hole * 2;
        
            if(child != currentSize && array[child + 1] < array[child])
            {
                child++;
            }
            
            if (array[child] < tmp)
            {
				array[hole] = std::move(array[child]);
                hashTable[array[hole]] = hole;
			}
			
            else
            {
                break;
            }
        }
        
        array[hole] = std::move(tmp);
        hashTable[array[hole]] = hole;
        return hole;
    }
};

#endif //_BINARY_HEAP_HPP_