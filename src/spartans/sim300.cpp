/******************************************************************************
Title : sim3000.cpp
Author : Andrew Baumann
Created on : 13 October 2014
Description : A battle simulator. This is the main.
Special Thanks : Weiss, Mark Allan. Zheng, Tony.
******************************************************************************/
#include <iostream>
#include <string>
#include <cmath>
#include <time.h>
#include "BinaryHeap.hpp"
#include "QuadraticProbing.hpp"
#include "soldier.hpp"
#include "simulation.hpp"

using namespace std;

int main(int argc, char * argv[])
{
    int totalPWins = 0;
    int totalSWins = 0;
    double tTime, cTime = 0; //total time, current runtime
    clock_t bTime, eTime; //begin time, end time
    /*
    Below section is argument handling for main, setting up sim,
    spart, and pers numbers for running in the simulation.
     */
    if(argc != 4)
    {
        cout << "Error 1: command lines arguments incorrect. Rerun." << endl;
        return 0;
    }
    string numOfSims = argv[1];
    string numofSpartans = argv[2];
    string numOfPersians = argv[3];

    for (int i = 0; i < numOfSims.size(); i++)
    {
        if (!isdigit(numOfSims[i])) {
            cout << "Error 2: Number of sims is not a number. Rerun." << endl;
            return 0;
        }
    }

    int sims = 0;
    sims = atoi(numOfSims.c_str());

    for (int i = 0; i < numofSpartans.size(); i++)
    {
        if (!isdigit(numofSpartans[i]))
        {
            if(numofSpartans[i] = 'S' && i != 0)
                break;
            else {
                cout << "Error 3: Number of Spartans is not a number. Rerun." << endl;
                return 0;
            }
        }
    }

    int spartans = 0;
    spartans = atoi(numofSpartans.c_str());

    for (int i = 0; i < numOfPersians.size(); i++)
    {
        if (!isdigit(numOfPersians[i]))
        {
            if(numOfPersians[i] = 'P' && i != 0)
                break;
            else {
                cout << "Error 4: Number of Persians is not a number. Rerun." << endl;
                return 0;
            }
        }
    }

    int persians = 0;
    persians = atoi(numOfPersians.c_str());
    /*
     End of argument handling portion.
     /////
     Begin simulation handling.
     */
    for(int i=0; i<sims; i++) {
        bTime = clock();
        Simulation sim300(spartans,persians);
        if(sim300.WhoWon()) {
            totalSWins++;
            cout << "This is Sparta!" << endl;
            cout << sim300.getSpartans() << " Spartans Standing." << endl;
        }
        else {
            totalPWins++;
            cout << "Athens will burn." << endl;
            cout << sim300.getPersians() << " Persians Strong." << endl;
        }
        eTime = clock();
        cTime = (eTime - bTime)/CLOCKS_PER_SEC;
        tTime += cTime;
        cout << "This took: " << cTime << " seconds." << endl;
    }

    cout << "Out of " << sims << " simulations, the glorious Spartans won: ";
    cout << totalSWins << " times. The terrible Persians won: " << totalPWins << endl;
    cout << "This took an average of: " << tTime/sims << " seconds per simulation." << endl;
    return 0;
}



