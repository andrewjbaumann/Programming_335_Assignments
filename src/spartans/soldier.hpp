/******************************************************************************
Title : sim3000.cpp
Author : Andrew Baumann
Created on : 13 October 2014
Description : A battle simulation program, this being the solider class of 
the simulation. Header + implementation. 
Special Thanks : Weiss, Mark Allan. Zheng, Tony.
******************************************************************************/
#ifndef SOLIDER_HPP
#define SOLIDER_HPP
#include <iostream>
#include <string>


class Solider
{
public:
    //default constructor
    Solider()
    {ID=0; time=0; isSpartan=0; deleted=false; wounded=0;}
    //constructor on: am i a spartan? when do i make my first action? what is my id?
    Solider(bool isSpartan, int firstTime, int ID)
    {this->ID = ID;    time = firstTime;    this->isSpartan = isSpartan; deleted=false; wounded=0;}
    //destructor
    ~Solider(){}
    //less than operator overload
    bool operator<(const Solider& other) const
    { return (time < other.time);}
    //greater than operator overload
    bool operator>(const Solider& other) const
    { return(time > other.time);}
    //equals/assignment operator overload
    Solider& operator=(const Solider& other)
    {ID = other.ID; time = other.time; isSpartan = other.isSpartan; deleted = other.deleted; wounded = other.wounded;}
    //not equals operator
    bool operator!=(const Solider& other) const
    {return (ID!=other.ID);}
    void operator+=(const int other)
    {time+=other;}

    //sets for all variables
    void setID(int ID)
    {this->ID = ID;}
    void setTime(int time)
    {this->time = time;}
    void setSpartan(bool isSpartan)
    {this->isSpartan = isSpartan;}
    void setWounded() //increments instead of change
    {wounded = wounded+1;}
    void kill()
    {deleted=true;}
    //gets for all variables
    int getID() const
    {return ID;}
    int getTime() const
    {return time;}
    bool getSpartan() const
    {return isSpartan;}
    int getWounded() const
    {return wounded;}
    bool isDeleted() const
    {return deleted;}


private:
    int ID; //identification variable
    int time; //time until next action
    bool isSpartan; // false = persian
    int wounded; //how many wounds a spartan(only) has
    bool deleted;
};

#endif


