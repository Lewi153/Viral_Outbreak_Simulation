#include "person.h"
#include "mixGroup.h"
#include <iostream>
#include <list>
#include <random>
#include <ctime>
#include <cmath>
#include <fstream>



using namespace std;


int main()
{

    // We will consider each time step 1 day in order to implement health status changes according to the Research Paper
    int dayTracker=0;
    ofstream outputFile;


    //Main Lists, iterators, and pointers:
    person * newPerson;
    mixGroup* newGroup;
    list<mixGroup*>group_list;
    list<mixGroup*>::iterator gitr;
    list<person*>person_list;
    list<person*>::iterator pitr;


    // Initial Random Generators:
    default_random_engine * gptr;
    gptr = new default_random_engine(time(NULL));
    uniform_int_distribution<int> famDist(1,7);         /// Family Size Distribution
    normal_distribution<double> ageDist(38,26);         /// Population Age Distribution
    uniform_int_distribution<int> fiftyDist(1,2);       /// Simple 50-50 Distribution (University OR Work) & (Daycare OR No-Daycare)
    uniform_int_distribution<int> elementaryDist(2,9);  /// Pick Random Elementary School
    uniform_int_distribution<int> middleDist(10,13);    /// Pick Random Middle School
    uniform_int_distribution<int> highDist(14,15);      /// Pick Random High school


    // Initialize Hospital 0
    newGroup=new mixGroup(0);
    group_list.push_back(newGroup);
    newGroup=NULL;
    // Initialize Daycare 1
    newGroup=new mixGroup(1);
    newGroup->SetProb(0.02000);
    group_list.push_back(newGroup);
    newGroup=NULL;
    // Initialize Elementary Schools 2-9
    for (int i=2;i<10;i++){
        newGroup=new mixGroup(i);
        newGroup->SetProb(0.01000);
        group_list.push_back(newGroup);
        newGroup=NULL;
    }
    // Initialize Middle Schools 10-13
    for (int i=10;i<14;i++){
        newGroup=new mixGroup(i);
        newGroup->SetProb(0.00800);
        group_list.push_back(newGroup);
        newGroup=NULL;
    }
    // Initialize High Schools 14-15
    for (int i=14;i<16;i++){
        newGroup=new mixGroup(i);
        newGroup->SetProb(0.00800);
        group_list.push_back(newGroup);
        newGroup=NULL;
    }
    // Initialize University 16
    newGroup=new mixGroup(16);
    newGroup->SetProb(0.00800);
    group_list.push_back(newGroup);
    newGroup=NULL;






//////////////////////////////////////// Initialize Entire Population & Families (Place Persons in Schools)//////////////////////////////////////////////////////////////////////////////
    int popSize;
    int famSize;
    int pID=1;
    int fID=17;
    int randGroup;
    int age;

    cout<<endl<<"                  ------Simulation of Hemorrhagic Smallpox Outbreak Within a Small Community------"<<endl<<endl;

    cout<<"                             [Community Structure with Probabilities of Virus Spreading]"<<endl;
    cout<<"                              ________________________________________________________"<<endl;
    cout<<"                             |  Structure Type:   |    Amount:   | Transmission Rate: |"<<endl;
    cout<<"                             |--------------------------------------------------------|"<<endl;
    cout<<"                             | Daycare            |  [1]         |  0.02000           |"<<endl;
    cout<<"                             | Elementary School  |  [8]         |  0.01000           |"<<endl;
    cout<<"                             | Middle School      |  [4]         |  0.00800           |"<<endl;
    cout<<"                             | High School        |  [2]         |  0.00800           |"<<endl;
    cout<<"                             | University         |  [1]         |  0.00800           |"<<endl;
    cout<<"                             | Family(Adult/Child)|  [As Needed] |  0.01000 / 0.03000 |"<<endl;
    cout<<"                             | Workplace          |  [1 Per 25]  |  0.01000           |"<<endl;
    cout<<"                             | Miscellaneous      |  [80]        |  0.00003           |"<<endl;
    cout<<"                             |____________________|______________|____________________|"<<endl;
    cout<<"                         *Reference: [International Journal of Infectious Diseases (2007) 11, 98-108]"<<endl;

    cout<<endl<<endl<<endl<<"                                *(Time-delay to output file if Population > 10,000)";
    cout<<endl<<"                                         ENTER DESIRED POPULATION SIZE: ";
    cin>>popSize;
    cout<<endl;

    while(person_list.size() < popSize){

        // New Family and Size
        newGroup=new mixGroup(fID);
        newGroup->SetProb(0.01000);
        for(int r=0;r<10;r++){
            famSize=famDist(*gptr);
        }

        /// First Person: Age = 18+ (job=1)
        newPerson=new person(pID);
        pID++;
        newPerson->AddGroup(fID);
        age=ageDist(*gptr);
        while(age<18){age=ageDist(*gptr);}
        newPerson->SetAge(age);
        newPerson->SetJob(1);

        /// Add First Person Master List and Family's Member List
        person_list.push_back(newPerson);
        newGroup->AddMember(newPerson);
        newPerson=NULL;

        // Generate Rest of Family Members (based on size)
        for(int i=0;i<famSize-1;i++){

            /// Generate New Person: Age = 1+
            newPerson=new person(pID);
            pID++;
            newPerson->AddGroup(fID);
            for(int r=0;r<5;r++){
                age=ageDist(*gptr);
            }
            while(age<1){age=ageDist(*gptr);}
            newPerson->SetAge(age);

            /// Add Next Person Master List and Family's Member List
            person_list.push_back(newPerson);                              // MOVE DOWN TO BOTTOM
            newGroup->AddMember(newPerson);

            /// Add to School (Ages 5-18) or Daycare (Age<5)
            if(age<5){
                for(int r=0;r<5;r++){
                    randGroup=fiftyDist(*gptr);}
                if(randGroup==1){
                newPerson->AddGroup(1);
                gitr=group_list.begin();
                while((*gitr)->GetID()!=1){gitr++;} ///Daycare
                (*gitr)->AddMember(newPerson);
                }
            }
            else if(age<11){
                for(int r=0;r<5;r++){
                randGroup=elementaryDist(*gptr);}
                newPerson->AddGroup(randGroup);
                gitr=group_list.begin();
                while((*gitr)->GetID()!=randGroup){gitr++;} ///Elementary
                (*gitr)->AddMember(newPerson);
            }
            else if(age<14){
                for(int r=0;r<5;r++){
                randGroup=middleDist(*gptr);}
                newPerson->AddGroup(randGroup);
                gitr=group_list.begin();
                while((*gitr)->GetID()!=randGroup){gitr++;} ///Middle
                (*gitr)->AddMember(newPerson);
            }
            else if(age<19){
                for(int r=0;r<5;r++){
                randGroup=highDist(*gptr);}
                newPerson->AddGroup(randGroup);
                gitr=group_list.begin();
                while((*gitr)->GetID()!=randGroup){gitr++;} ///High
                (*gitr)->AddMember(newPerson);
            }
            else if(age>18 && age<26){  /// University OR job=1
                for(int r=0;r<5;r++){
                randGroup=fiftyDist(*gptr);}
                if(randGroup==1){
                    newPerson->AddGroup(16);
                    gitr=group_list.begin();
                    while((*gitr)->GetID()!=16){gitr++;}
                    (*gitr)->AddMember(newPerson);}
                else{
                newPerson->SetJob(1);}
            }
            newPerson=NULL;
        }///End One Single Family Generation

    ///Add Family to Master List
    group_list.push_back(newGroup);
    newGroup=NULL;
    fID++;
    }///End Entire Persons Generation




    // Work Groups:
    int needJobs=0;
    int wID=fID;
    int numWork;
    ///Count Number Persons that need jobs
    pitr=person_list.begin();
    while(pitr!=person_list.end()){
        if((*pitr)->GetJob()==1){needJobs++;}
        pitr++;
    }
    ///Average 25 Persons per Work Group
    numWork=needJobs/25;

    ///Generate All Needed Work Groups
    for (int i=0;i<numWork;i++){
        newGroup=new mixGroup(wID);
        newGroup->SetProb(0.01000);
        group_list.push_back(newGroup);
        newGroup=NULL;
        wID++;
    }

    /// Random Work Group Generator
    uniform_int_distribution<int> workDist(fID,wID-1); ///Random Work


    /// Loop through Person Master List, Add to Random Work Group if job==1
    pitr=person_list.begin();
    while(pitr!=person_list.end()){
        if((*pitr)->GetJob()==1){
            for(int r=0;r<5;r++){
            randGroup=workDist(*gptr);}
            (*pitr)->AddGroup(randGroup);
            gitr=group_list.begin();
            while((*gitr)->GetID()!=randGroup){gitr++;}
            (*gitr)->AddMember((*pitr));
        }
    pitr++;
    }




    // Miscellaneous Groups:
    int mID=wID;
    ///Generate All Needed Misc Groups
    for (int i=0;i<80;i++){
        newGroup=new mixGroup(mID);
        newGroup->SetProb(0.00003);
        group_list.push_back(newGroup);
        newGroup=NULL;
        mID++;
    }

    /// Random Misc Group Generator
    uniform_int_distribution<int> miscDist(wID,mID-1);  ///Random Misc


    /// Loop through Person Master List, Add all to a Random Misc Group
    pitr=person_list.begin();
    while(pitr!=person_list.end()){
            for(int r=0;r<5;r++){
            randGroup=miscDist(*gptr);}
            (*pitr)->AddGroup(randGroup);
            gitr=group_list.begin();
            while((*gitr)->GetID()!=randGroup){gitr++;}
            (*gitr)->AddMember((*pitr));
    pitr++;
    }







//////////////////////////////////////////////////////////// END INITIALIZATION OF ALL PERSONS AND ALL MIXING GROUPS ///////////////////////////////////////////////////////////












////////////////////////////////////////////////////////////////// Initial Target: All Members = Exposed //////////////////////////////////////////////////////////////////////////

    uniform_int_distribution<int> randomDist(1,8); /// random Group
    uniform_int_distribution<int> fDist(17,fID-1); /// Random Family
    int type;
    int select;
    int target;
    int initialID;
    cout<<endl<<endl<<"                                          SELECT INITIAL EXPOSURE TARGET: "<<endl;
    cout<<"                                          [0] Random"<<endl;
    cout<<"                                          [1] Daycare"<<endl;
    cout<<"                                          [2] Elementary School"<<endl;
    cout<<"                                          [3] Middle School"<<endl;
    cout<<"                                          [4] High School"<<endl;
    cout<<"                                          [5] University"<<endl;
    cout<<"                                          [6] Family"<<endl;
    cout<<"                                          [7] Workplace"<<endl;
    cout<<"                                          [8] Misc"<<endl;
    cout<<"                                          Selection: ";
    cin>>select;
    while (select>8){
        cout<<"                                      Invalid: Select Again [0-7] ";
        cin>>select;
    }
    switch(select){

    ///Random: (Recycles Non-Random Cases with it's own random switch)
    case 0:{
        for (int r=0;r<5;r++){type=randomDist(*gptr);}
        switch(type){
        case 1:{gitr=group_list.begin();
        while((*gitr)->GetID()!=1){gitr++;}
        (*gitr)->ExposeAll();
        cout<<"                                          INITIAL EXPOSURE: Daycare  |  ID: 1"<<endl;
        }break;
        case 2:{target=elementaryDist(*gptr);
            gitr=group_list.begin();
            while((*gitr)->GetID()!=target){gitr++;}
            initialID=(*gitr)->GetID();
            (*gitr)->ExposeAll();
            cout<<"                                          INITIAL EXPOSURE: Elementary School  |  ID: "<<initialID<<endl;}break;
        case 3:{target=middleDist(*gptr);
            gitr=group_list.begin();
            while((*gitr)->GetID()!=target){gitr++;}
            initialID=(*gitr)->GetID();
            (*gitr)->ExposeAll();
            cout<<"                                          INITIAL EXPOSURE: Middle School  |  ID: "<<initialID<<endl;}break;
        case 4:{target=highDist(*gptr);
            gitr=group_list.begin();
            while((*gitr)->GetID()!=target){gitr++;}
            initialID=(*gitr)->GetID();
            (*gitr)->ExposeAll();
            cout<<"                                          INITIAL EXPOSURE: High School  |  ID: "<<initialID<<endl;}break;
        case 5:{target=16;
            gitr=group_list.begin();
            while((*gitr)->GetID()!=target){gitr++;}
            (*gitr)->ExposeAll();
            cout<<"                                          INITIAL EXPOSURE: University  |  ID: 16"<<endl;}break;
        case 6:{target=fDist(*gptr);
            gitr=group_list.begin();
            while((*gitr)->GetID()!=target){gitr++;}
            initialID=(*gitr)->GetID();
            (*gitr)->ExposeAll();
            cout<<"                                          INITIAL EXPOSURE: Family  |  ID: "<<initialID<<endl;}break;
        case 7:{target=workDist(*gptr);
            gitr=group_list.begin();
            while((*gitr)->GetID()!=target){gitr++;}
            initialID=(*gitr)->GetID();
            (*gitr)->ExposeAll();
            cout<<"                                          INITIAL EXPOSURE: Work  |  ID: "<<initialID<<endl;}break;
        case 8:{target=miscDist(*gptr);
            gitr=group_list.begin();
            while((*gitr)->GetID()!=target){gitr++;}
            initialID=(*gitr)->GetID();
            (*gitr)->ExposeAll();
            cout<<"                                          INITIAL EXPOSURE: Miscellaneous  |  ID: "<<initialID<<endl;}break;
        default: cout<<"! Error with initial exposure !"<<endl;
        }
    }break;

    ///Non-Random
    case 1:{
        gitr=group_list.begin();
        while((*gitr)->GetID()!=1){gitr++;}
        (*gitr)->ExposeAll();
        cout<<"                                          INITIAL EXPOSURE: Daycare  |  ID: 1"<<endl;
    }break;
    case 2:{
        target=elementaryDist(*gptr);
        gitr=group_list.begin();
        while((*gitr)->GetID()!=target){gitr++;}
        initialID=(*gitr)->GetID();
        (*gitr)->ExposeAll();
        cout<<"                                          INITIAL EXPOSURE: Elementary School  |  ID: "<<initialID<<endl;}break;
    case 3:{
        target=middleDist(*gptr);
        gitr=group_list.begin();
        while((*gitr)->GetID()!=target){gitr++;}
        initialID=(*gitr)->GetID();
        (*gitr)->ExposeAll();
        cout<<"                                          INITIAL EXPOSURE: Middle School  |  ID: "<<initialID<<endl;}break;
    case 4:{
        target=highDist(*gptr);
        gitr=group_list.begin();
        while((*gitr)->GetID()!=target){gitr++;}
        initialID=(*gitr)->GetID();
        (*gitr)->ExposeAll();
        cout<<"                                          INITIAL EXPOSURE: High School  |  ID: "<<initialID<<endl;}break;
    case 5:{
        target=16;
        gitr=group_list.begin();
        while((*gitr)->GetID()!=target){gitr++;}
        (*gitr)->ExposeAll();
        cout<<"                                          INITIAL EXPOSURE: University  |  ID: 16"<<endl;}break;
    case 6:{
        target=fDist(*gptr);
        gitr=group_list.begin();
        while((*gitr)->GetID()!=target){gitr++;}
        initialID=(*gitr)->GetID();
        (*gitr)->ExposeAll();
        cout<<"                                          INITIAL EXPOSURE: Family  |  ID: "<<initialID<<endl;}break;
    case 7:{
        target=workDist(*gptr);
        gitr=group_list.begin();
        while((*gitr)->GetID()!=target){gitr++;}
        initialID=(*gitr)->GetID();
        (*gitr)->ExposeAll();
        cout<<"                                          INITIAL EXPOSURE: Work  |  ID: "<<initialID<<endl;}break;
    case 8:{
        target=miscDist(*gptr);
        gitr=group_list.begin();
        while((*gitr)->GetID()!=target){gitr++;}
        initialID=(*gitr)->GetID();
        (*gitr)->ExposeAll();
        cout<<"                                          INITIAL EXPOSURE: Miscellaneous  |  ID: "<<initialID<<endl;}break;


    default: cout<<"! Error with initial exposure !"<<endl;
    }
    cout<<endl<<endl;
/////////////////////////////////////////////////////////////// END INITIAL Exposure //////////////////////////////////////////////////////////////////////////////////////







/////////////////////////////////////////////////////////////////////// Spreading Infection SIMULATION ////////////////////////////////////////////////////////////////////////

    int numDays;
    int status;
    int ids[3];
    double P1,P2,P3;
    double result;
    double randResult;
    uniform_real_distribution<double> healthDist(0.0,1.0);
    int numUnexposed;
    int numExposed;
    int numInfected;
    int numSymptomatic;
    int numDead;
    double popRemain, dead, pop;
    pop=(double)popSize;


    cout<<"                                    ENTER DESIRED NUMBER OF DAYS TO RUN SIMULATION: ";
    cin>>numDays;
    cout<<endl;
    outputFile.open("Output.txt", ofstream::out | ofstream::trunc);
    outputFile<<"Total Population: "<<popSize<<"\n"<<"\n";
    for(int i=0;i<numDays;i++){

        //Recalculate Family Probs (Weighted Average Adult/Child)
        gitr=group_list.begin();
        while((*gitr)->GetID()!=17){gitr++;}
        for(int i=0;i<fID-1;i++){
            (*gitr)->CheckFamProb();
            gitr++;}


        //Begin Loop Through Master Person List
        pitr=person_list.begin();
        while(pitr!=person_list.end()){
            (*pitr)->UpdateStatus(gptr);
            status=(*pitr)->GetStatus();

            switch(status){
            case 0:{ //Unexposed - Check for Exposure (Update Status to 1 if so)

                (*pitr)->GetGroups(ids);
                //Get Probs from Groups
                gitr=group_list.begin();
                while((*gitr)->GetID()!=ids[0]){gitr++;}
                P1=(*gitr)->CalcProb();
                gitr=group_list.begin();
                while((*gitr)->GetID()!=ids[1]){gitr++;}
                P2=(*gitr)->CalcProb();
                gitr=group_list.begin();
                while((*gitr)->GetID()!=ids[2]){gitr++;}
                P3=(*gitr)->CalcProb();
                //Calculate Final Prob
                result=1-(P1*P2*P3);
                //Get Random Prob to Compare
                for(int r=0;r<5;r++){
                randResult=healthDist(*gptr);}
                //Compare for Health Status change or not
                if(result>randResult){ ///Exposed = True
                    (*pitr)->NewStatus();}
            }break;


            case 1:{ //Exposed - Check for Infection (Update Status to 2 if so)

                (*pitr)->GetGroups(ids);
                //Get Probs from Groups
                gitr=group_list.begin();
                while((*gitr)->GetID()!=ids[0]){gitr++;}
                P1=(*gitr)->CalcProb();
                gitr=group_list.begin();
                while((*gitr)->GetID()!=ids[1]){gitr++;}
                P2=(*gitr)->CalcProb();
                gitr=group_list.begin();
                while((*gitr)->GetID()!=ids[2]){gitr++;}
                P3=(*gitr)->CalcProb();
                //Calculate Final Prob
                result=1-(P1*P2*P3);
                ///cout<<"Person "<<n<<" Prob: "<<result<<endl;
                //Get Random Prob to Compare
                for(int r=0;r<5;r++){
                randResult=healthDist(*gptr);}
                //Compare for Health Status change or not
                if(result>randResult){ ///Infected = True
                    (*pitr)->NewStatus();}
            }break;


            case 2:break;//Infected - Nothing


            case 3:{ //Symptomatic >4 days (Bleeding) - Move to Hospital
                if((*pitr)->GetStatusTime()>4){
                    gitr=group_list.begin();
                    (*gitr)->AddMember((*pitr));
                }
            }break;


            case 4:break;//Dead - Nothing


            default:cout<<"Issue With Infection Spread Loop"<<endl;
            }/// end switch


            //Update Person's Status Time and move Iterator
            (*pitr)->UpdateStatusTime();
            pitr++;

        }//End 1 Master Person Loop (1 Day Complete)
        dayTracker++;

        //Remove Symptomatic >4 days (Bleeding) from Prior Groups (end of each day)
        gitr=group_list.begin();
        gitr++;
        while(gitr!=group_list.end()){
            (*gitr)->RemoveSymptomatic();
            gitr++;
        }


        //Write Results to File (end of each day)
        numUnexposed=0;
        numExposed=0;
        numInfected=0;
        numSymptomatic=0;
        numDead=0;
        pitr=person_list.begin();
        while(pitr!=person_list.end()){
            status=(*pitr)->GetStatus();
            switch(status){
            case 0:{numUnexposed++;}break;
            case 1:{numExposed++;}break;
            case 2:{numInfected++;}break;
            case 3:{numSymptomatic++;}break;
            case 4:{numDead++;}break;
            default:cout<<"Issue Counting Health Status Totals"<<endl;
            }
            pitr++;
        }
        dead=(double)numDead;
        popRemain=(1-dead/pop)*100;

        outputFile<<"Day ["<<dayTracker<<"] Population Health Status:\n";
        outputFile<<"Unexposed: "<<numUnexposed<<"\n";
        outputFile<<"Exposed: "<<numExposed<<"\n";
        outputFile<<"Infected: "<<numInfected<<"\n";
        outputFile<<"Symptomatic: "<<numSymptomatic<<"\n";
        outputFile<<"Dead: "<<numDead<<"\n";
        outputFile<<"POPULATION REMAINING: "<<popRemain<<"%"<<"\n"<<"\n";


    }//end simulation for-loop (All Days Complete)
    outputFile.close();

    cout<<"                                     Data stored in file 'Output.txt' successfully."<<endl<<endl<<endl;

////////////////////////////////////////////////////////////  END SIMULATION  //////////////////////////////////////////////////////////////////////////////////////////








    //Terminal Display of Results (If Desired)
    int choice;
    cout<<"DISPLAY FINAL RESULTS OF ALL GROUPS? [Yes=1 | No=0]: ";
    cin>>choice;
    while(choice>1){
        cout<<"Invalid, Select Again [1/0]: ";
        cin>>choice;}
    cout<<endl<<endl;
    if(choice==1){
        gitr=group_list.begin();
    while (gitr!=group_list.end()){
        (*gitr)->Display(fID-1, wID-1);
        gitr++;}
    }
    cout<<"DISPLAY FINAL RESULTS OF ALL PERSONS? [Yes=1 | No=0]: ";
    cin>>choice;
    while(choice>1){
        cout<<"Invalid, Select Again [1/0]: ";
        cin>>choice;}
    cout<<endl<<endl;
    if(choice==1){
        pitr=person_list.begin();
    while (pitr!=person_list.end()){
        (*pitr)->Display();
        pitr++;}
    }


    return 0;
}




