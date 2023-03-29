#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <list>
#include <random>
#include <ctime>
using namespace std;

class person
{
    public:
        person(int n);
        virtual ~person();

        int GetID() {return id;}
        void SetID(int val) {id = val;}
        int GetAge() {return age;}
        void SetAge(int val) {age = val;}
        void SetStatus(int n) {status=n;}
        int GetStatus() {return status;}
        void NewStatus() {status++; statusTime=-1;}
        int GetStatusTime() {return statusTime;}
        void SetStatusTime(int n) {statusTime=n;}
        void UpdateStatusTime() {statusTime++;}
        void ResetStatusTime() {statusTime=0;}
        void Display();
        void SetJob(int n){job=n;}
        int GetJob(){return job;}
        void AddGroup(int id){PersonGroup_list.push_back(id);}
        void GetGroups(int arr[3]);
        void UpdateStatus(default_random_engine * gptr);


    private:
        int id;
        int age;
        int status; //    0=Unexposed     1=Exposed     2=Infected    3=Symptomatic      4=Dead
        int statusTime;
        int job;
        list<int>PersonGroup_list;  // Always = 3 total
        list<int>::iterator PGitr;
};

#endif // PERSON_H
