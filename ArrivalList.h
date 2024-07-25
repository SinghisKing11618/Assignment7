//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Name of Author: Yashraj Singh
// ASU ID: 1224341092
// Description: //---- is where you should add your own code
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Arrival represents an arrival address with distance and road
//category info. from a specific departure address
struct Arrival
{
    string arrAddress;
    double distance;        //miles from the departure address to this arrival address
    string roadCategory;    //Interstates, Arterials, Collectors or Local streets
    struct Arrival* next;
};

//class ArrivalList contains a linked list of Arrival objects
class ArrivalList
{
    private:
        struct Arrival* head;

    public:
        ArrivalList();//done
        ~ArrivalList();//done
        Arrival* getHead();//done
        Arrival* findArrival(string oneAddress);//done
        bool addArrival(string oneAddress, double distance, string roadCategory);//done
        void printArrivalList();//done
};

//we set head to null
ArrivalList::ArrivalList(){
    head = NULL;
}

//destructor goes through each node and deletes it 
ArrivalList::~ArrivalList(){

    struct Arrival * curr = head;
    int addressCount = 0;

    while(curr != NULL){
        struct Arrival * temp = curr;
        curr = curr -> next;
        delete temp ;
        addressCount++;
    }

    cout<< "The number of deleted arrival addresses are: " << addressCount <<"\n";
}

//returns head
Arrival* ArrivalList::getHead(){
    return head;
}


//loop through entire list until oneAddress matches the address of the current node and then return it
Arrival* ArrivalList::findArrival(string oneAddress){

    if(head == NULL) return NULL;

    Arrival * curr = head;
    while(curr != NULL){
        if(curr -> arrAddress == oneAddress) return curr;
        curr = curr -> next;
    }
    return NULL;
}

bool ArrivalList::addArrival(string oneAddress, double distance, string roadCategory){

    //Arrival objects must be inserted in alphabetical order of their addresses.

    if(findArrival(oneAddress) != NULL) return false;

    Arrival * newArrival = new Arrival();
    newArrival -> arrAddress = oneAddress;
    newArrival -> distance = distance;
    newArrival -> roadCategory = roadCategory;

    if(head == NULL){
        head = newArrival;
        return true;
    } 

    //insertion in the beginning
    if(newArrival -> arrAddress < head -> arrAddress){
        Arrival * temp = head;
        head = newArrival;
        newArrival -> next = temp;
        return true;
    }

    Arrival * prev = NULL;
    Arrival * curr = head;

    while(curr != NULL && curr -> arrAddress < oneAddress){
        prev = curr;
        curr = curr -> next;
    }


    if(curr != NULL){//we need to insert somewhere in the middle of the list
        prev -> next = newArrival;
        newArrival -> next = curr;
    }else{//we need to insert at tail of list
        prev -> next = newArrival;
    }
    return true;
}



//Prints all the arrival address in the linked list starting from the head.
void ArrivalList::printArrivalList()
{
    Arrival * temp = head;

    if(head == NULL){
        cout << "Arrival list is empty" << endl;
    }else{
         while(temp != NULL){
            cout << temp->arrAddress << fixed << setprecision(2) << "(" << temp->distance << "/" << temp->roadCategory << "),";
		    temp = temp->next;
        }	
	    cout <<"\n";
    }
    
}