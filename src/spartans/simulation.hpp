/******************************************************************************
Title : simulation.hpp
Author : Andrew Baumann
Created on : 13 October 2014
Description : A battle simulator. This is the "simulation" class, which runs
the simulation based on n times simed, s soliders (spartans), and p soliders
(persians). Header + implementation.
Special Thanks : Weiss, Mark Allan. Zheng, Tony.
******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "BinaryHeap.hpp"
#include "soldier.hpp"
#include "QuadraticProbing.hpp"

struct Node{
    Node(){ID=-1; actTime=0;}
    Node(int id, int time)
    {ID = id; actTime = time;}
    ~Node(){}
    void operator=(Node other)
    {ID = other.ID; actTime = other.actTime;}
    void operator=(int Time)
    {actTime = Time;}
    bool operator<(Node other) const
    {
        if(actTime < other.actTime)
            return true;
        else
            return false;
    }
    bool operator!=(Node other) const
    {return (actTime != other.actTime);}
    void operator+=(int Time)
    {actTime += Time;}
    void operator-=(int Time)
    {actTime -= Time;}
    int ID;
    int actTime;
};

class Simulation
{
private:
    vector<Solider> spartans; //vect of spartans (ID: 0 -> n-1)
    vector<Solider> persians; //vect of persians (ID: n -> m+n)
    int snum, pnum, sDeath, pDeath;
    bool winner;
    binaryHeap<Node> map; //the priority queue of events

public:
    Simulation()
    {}
    ~Simulation()
    {}

    Simulation(int numSpartans, int numPersians)
    {
        snum = numSpartans;
        pnum = numPersians;
        sDeath = numSpartans;
        pDeath = numPersians;
        winner = true;
        srand(time(NULL));
        int firstAct=0;
        /*
        Generates spartans from ID: 0-N.
        Generates first act from 1-50.
         */
        for(int i=0; i<numSpartans; i++)
        {
            firstAct = rand() % 50+1;
            Solider solider(true, firstAct, i);
            spartans.push_back(solider);
            Node node(i, firstAct);
            map.insert(node);
        }
        /*
        Generates persians from ID: N-(N+M).
        Generates first act from 51-1000
         */
        for(int i=numSpartans; i<(numPersians+numSpartans); i++)
        {
            firstAct = rand() % 1000+52;
            Solider solider(false, firstAct, i);
            persians.push_back(solider);
            Node node(i, firstAct);
            map.insert(node);
        }


        battleon();
        while(!map.isEmpty())
            map.deleteMin();

    }

    /*
    The fighting simulator. Ends when one army is defeated.
    Will return true if Spartans are victorious.
    snum = spartan #s, pnum = persian #s
     */
    void battleon()
    {
        int ID=0;
        int pID=-1;
        do{
            Node node = map.findMin();
            //if ID < number of spartans, actor is spartan
            ID = node.ID;
/*            for(inti=0; i<15; i++)
            {
                Node node =
            }*/

            if(ID < snum)
            {
                if(spartans[ID].isDeleted())
                    {map.deleteMin();}
                else
                {
                    sAttack();
                    int increase = rand() % 10;
                    map.increaseKey(ID, increase);
                }
            }
            else
            {
                ID = ID-snum;
                if(persians[ID].isDeleted())
                    {map.deleteMin();}
                else
                {
                    pAttack();
                    int increase = rand() % 60 + 10;
                    map.increaseKey(ID, increase);
                }
            }
            pID = ID;
        }while(sDeath != 0 && pDeath != 0);

        return;
    }

    void sAttack()
    {
        bool acceptable=false;
        int target = 0;
        do{
            if(pDeath==0)
                return;
            else if(persians[target].isDeleted())
                target++;
            else
            {
               acceptable=true;
               persians[target].kill();
               pDeath--;
            }
        }while(!acceptable);

        return;
    }

    void pAttack()
    {
        bool acceptable=false;
        int chance = rand()% 100+1;

        if(chance < 95)
        {
            return;
        }

        int target2 = rand() % snum +1;
        int target = 0;
        do{
            if(sDeath == 0 || pDeath == 0)
                {return;}
            if(spartans[target].isDeleted())
                target++;
            else
            {
                spartans[target].setWounded();
                int deathcheck = spartans[target].getWounded();
                bool dead = false;
                if(deathcheck <= 3)
                    dead = false;
                else
                    dead= true;
                if(dead)
                {
                    spartans[target].kill();
                    sDeath--;
                    inspire();
                }
                acceptable=true;
            }
        }while(!acceptable);

        return;
    }

    void inspire()
    {
        int time;
        for(int i=0; i<snum; i++)
        {
            if(spartans[i].isDeleted())
            {}
            else {
                time = rand()% 2 + 1;
                map.increaseKey(i, time);
            }
        }
        return;
    }

    bool WhoWon()
    {
        if(pDeath == 0)
            return true;
        else
            return false;
    }

    int getPersians()
    {return pDeath;}

    int getSpartans()
    {return sDeath;}

};