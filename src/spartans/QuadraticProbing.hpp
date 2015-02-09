/******************************************************************************
Title : quadraticprobing.hpp
Author : Mark Weiss
Created on : 13 October 2014
Description : A quadratic probing hashtable used in the battle simulator. 
Several changes made by Andrew Baumann. 
Special Thanks : Weiss, Mark Allan. Zheng, Tony.
******************************************************************************/
#ifndef _QUADRATIC_PROBING_HPP_
#define _QUADRATIC_PROBING_HPP_

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

int nextPrime(int n);

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename KeyType, typename valueType>
class HashTable
{
public:

    explicit HashTable(int size = 1) : array(nextPrime(size))
    {
        makeEmpty();
    }

	bool contains(const KeyType & x) const
    {
        return isActive(findPos(x));
    }

	void makeEmpty()
    {
		currentSize = 0;
	
        for (auto & entry : array)
        {
            entry.info = EMPTY;
        }
    }

	bool insert(const KeyType & x, const valueType & value)
    {
		int currentPos = findPos(x);
		
        if (isActive(currentPos))
        {
            return false;
        }
		
        array[currentPos].element = value;
        array[currentPos].key = x;
        array[currentPos].info = ACTIVE;

		if (++currentSize > array.size() / 2)
        {
            rehash();
        }
        
		return true;
	}

	bool insert(const KeyType & x, valueType && value)
    {
		int currentPos = findPos(x);
	
        if (isActive(currentPos))
        {
            return false;
        }
		
        array[currentPos] = std::move(value);
        array[currentPos].key = x;
        array[currentPos].info = ACTIVE;

		if (++currentSize > array.size() / 2)
        {
            rehash();
        }
		
        return true;
	}

	bool remove(const KeyType & x)
    {
		int currentPos = findPos(x);
	
        if (!isActive(currentPos))
        {
            return false;
        }
		
        array[currentPos].info = DELETED;
        return true;
	}

	valueType& operator[](const KeyType& aKey)
    {
		int pos = findPos(aKey);
        
		return array[pos].element;
	}

	enum EntryType
    {
        ACTIVE, EMPTY, DELETED
    };

private:
	struct HashEntry
    {
		KeyType key;
        valueType element; // value
        EntryType info;

		HashEntry(const valueType & e = valueType{}, EntryType i = EMPTY, const KeyType & k = KeyType{}) : element{e}, info{i}, key{k}
        {
        }
        
		HashEntry(valueType && e, KeyType && k, EntryType i = EMPTY) : element{std::move(e)}, info{i}, key{std::move(k)}
        {
        }
	};

	vector<HashEntry> array;
	
    unsigned int currentSize;

	bool isActive(int currentPos) const
    {
		return array[currentPos].info == ACTIVE;
	}

	int findPos(const KeyType & x) const
    {
		int offset = 1;
        unsigned int currentPos = x.ID;
		while (array[currentPos].info != EMPTY && array[currentPos].key != x)
        {
			currentPos += offset;
            offset += 2;
			
            if (currentPos >= array.size())
            {
                currentPos -= array.size();
            }
        }
		return currentPos;
	}

	void rehash()
    {
		vector<HashEntry> oldArray = array;
		array.resize(nextPrime(2 * oldArray.size()));
		
        for (auto & entry : array)
        {
			entry.info = EMPTY;
        }

        currentSize = 0;
		
        for (auto & entry : oldArray)
        {
            if (entry.info == ACTIVE)
            {
                insert(entry.key, std::move(entry.element));
            }
        }
    }

	size_t myhash(const KeyType & x) const
    {
		static hash<KeyType> hf;
        return hf(x) % array.size();
	}
};

#endif //_QUADRATIC_PROBING_HPP_