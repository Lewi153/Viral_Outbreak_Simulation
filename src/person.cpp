#include "person.h"
#include <list>
#include <random>
#include <ctime>
using namespace std;

person::person(int n)
{
    id=n;
    age=0;
    status=0;
    statusTime=0;
    job=0;
}

person::~person()
{
    //dtor
}


void person::Display(){
cout<<"Person: ID "<<id<<" | Age "<<age<<" | ";
switch(status){
    case 0:{cout<<"Unexposed";}break;
    case 1:{cout<<"Exposed";}break;
    case 2:{cout<<"Infected";}break;
    case 3:{cout<<"Symptomatic";}break;
    case 4:{cout<<"Dead";}break;
    default: cout<<"Issue Determining Person's Status.";
}
cout<<" For ["<<statusTime<<"] Full Days"<<endl;
}



void person::GetGroups(int arr[3]){
    PGitr=PersonGroup_list.begin();
    for(int i=0;i<3;i++){
        arr[i]=(*PGitr);
        PGitr++;
    }
}


void person::UpdateStatus(default_random_engine * gptr){
    uniform_int_distribution<int> sdist(7,15);
    int rand;
    switch(status){
    case 0:break;

    case 1:{    //Exposed -> Unexposed (if over 1 Day)
            if(statusTime>1){
            status=0;
            statusTime=0;}
    }break;

    case 2:{    //Infected -> Symptomatic (based on distribution of Days Spent Infected)
            for(int r=0;r<5;r++){
                rand=sdist(*gptr);}
            if(statusTime>=rand){
            status=3;
            statusTime=0;}
    }break;

    case 3:{    //Symptomatic -> Dead (After 10 days of being Symptomatic
            if(statusTime>10){
            status=4;
            statusTime=0;}
    }break;

    case 4:break;
    default:cout<<"Issue with UpdateStatus function"<<endl;
    }
}
