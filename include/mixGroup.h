#ifndef MIXGROUP_H
#define MIXGROUP_H
#include "person.h"
#include <iostream>
#include <list>
#include <random>
#include <ctime>
using namespace std;

class mixGroup
{
    public:
        mixGroup(int n);
        virtual ~mixGroup();

        int GetID() {return id;}
        void AddMember(person * ptr){members_list.push_back(ptr);}
        void Display(int numFam, int numWork);
        void ExposeAll();
        void SetProb(double n){prob=n;}
        double CalcProb();
        void RemoveSymptomatic();
        void CheckFamProb();



    private:
        int id;
        list<person*>members_list;
        list<person*>::iterator mitr;
        double prob;
};

#endif // MIXGROUP_H
