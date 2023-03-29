#include "mixGroup.h"
#include <list>
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
using namespace std;

mixGroup::mixGroup(int n)
{
    id=n;
    prob=1.0;

}

mixGroup::~mixGroup()
{
    //dtor
}


void mixGroup::Display(int fams, int works){
    if(id>works){cout<<"Group: *Miscellaneous*";}
    else if(id>fams){cout<<"Group: *Work*";}
    else if(id>16){cout<<"Group: *Family*";}
    else if(id==16){cout<<"Group: *University*";}
    else if(id>13){cout<<"Group: *High School*";}
    else if(id>9){cout<<"Group: *Middle School*";}
    else if(id>1){cout<<"Group: *Elementary School*";}
    else if(id==1){cout<<"Group: *Daycare*";}
    else if(id==0){cout<<"Group: *Hospital*";}
    else {cout<<"Issue Determining Group Type";}
    cout<<"  ID: "<<id<<endl;

    cout<<"----Members---------------------"<<endl;
    mitr=members_list.begin();
    while(mitr!=members_list.end()){
        (*mitr)->Display();
        mitr++;
    }

cout<<endl<<endl;
}


void mixGroup::ExposeAll(){ //Sets Initial Target member's to Exposed status
    mitr=members_list.begin();
    while(mitr!=members_list.end()){
        (*mitr)->SetStatus(1);
        mitr++;
    }
}





double mixGroup::CalcProb(){    //Includes Transmission Rate multiplier for Infected/Symptomatic
    double prob1, prob2, prob3, probTotal;
    double p1, p2, p3;
    double x=0.0;
    double y=0.0;
    double z=0.0;
    mitr=members_list.begin();
    while(mitr!=members_list.end()){
        if((*mitr)->GetStatus()==1){        //Normal Group Prob (Exposed)
            x=x+1.0;
        }
        else if((*mitr)->GetStatus()==2){   //Group Prob *5 (Infected)
            y=y+1.0;
        }
        else if((*mitr)->GetStatus()==3){   //Group Prob *10 (Symptomatic)
            z=z+1.0;
        }
        mitr++;
    }
    prob1=1-prob;
    prob2=1-(prob*5);
    prob3=1-(prob*10);

    p1=pow(prob1,x);
    p2=pow(prob2,y);
    p3=pow(prob2,z);

    probTotal=p1*p2*p3;
    return probTotal;

}





void mixGroup::RemoveSymptomatic(){ //If days spent Symptomatic > 4 (then they are Bleeding) ->Moved to Hospital
    int status;
    mitr=members_list.begin();
    while(mitr!=members_list.end()){
        status=(*mitr)->GetStatus();
        switch(status){
        case 0:break;
        case 1:break;
        case 2:break;
        case 3:{
                if((*mitr)->GetStatusTime()>4){
                members_list.erase(mitr);}
        }break;
        case 4:{members_list.erase(mitr);}break;
        default:cout<<"Issue with RemoveSymptomatic Function"<<endl;
        }
    mitr++;
    }
}



void mixGroup::CheckFamProb(){  //Weighted Average of Child and Adult Transmission Rates
    double prob1=0.03000;
    double prob2=0.01000;
    int x=0;
    int y=0;
    mitr=members_list.begin();
    while (mitr!=members_list.end()){
        if((*mitr)->GetAge()<18){
            if((*mitr)->GetStatus()==1){x++;}
            else if((*mitr)->GetStatus()==2){x++;}
            else if((*mitr)->GetStatus()==3){x++;}
        }
        else{
            if((*mitr)->GetStatus()==1){y++;}
            else if((*mitr)->GetStatus()==2){y++;}
            else if((*mitr)->GetStatus()==3){y++;}}
    mitr++;
    }

    prob=((x*prob1)+(y*prob2))/(x+y);
}
