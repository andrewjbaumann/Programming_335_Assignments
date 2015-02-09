/******************************************************************************
Title : quadraticprobing.cpp
Author : Mark Weiss
Created on : 13 October 2014
Description : A quadratic probing hashtable, this is the prime functions.
No changes made by Andrew Baumann.
Special Thanks : Weiss, Mark Allan. Zheng, Tony.
******************************************************************************/
#include <stdlib.h>
#include <time.h>


using namespace std;

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime(int n)
{
    if((n == 2) || (n == 3))
    {
        return true;
    }
    if((n == 1) || (n % 2 == 0))
    {
        return false;
    }
    for(int i = 3; i * i <= n; i += 2)
    {
        if(n % i == 0)
        {
            return false;
        }
    }
    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
int nextPrime(int n)
{
    if(n % 2 == 0)
    {
        ++n;
    }
    for(; !isPrime(n); n += 2)
    {
        ;
    }
    return n;
}
