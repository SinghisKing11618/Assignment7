//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Name of Author: Yashraj Singh
// ASU ID: 1224341092
// Description: //---- is where you should add your own code
//********************************************************************

#include "ArrivalList.h"

using namespace std;

//represent each node of the graph which is a departure location
//with all the relevant info.
struct Departure
{
    string depAddress;
    double d;
    struct Departure* pi;
    ArrivalList* arrList;
};

//class MinPriorityQueue represents a Min-heap that contains Departure objects.
class MinPriorityQueue
{
    private:
        struct Departure* departureArr;	//a Departure array
        int capacity, size;

	public:
        MinPriorityQueue(int myCapacity);//done
        ~MinPriorityQueue();//done

        Departure* getDepartureArr();//done
        int getSize();//done
        int getCapacity();//done
        int isFound(string oneDepAddress);///done
        bool decreaseKey(int index, Departure oneDepartureWithNewDValue);//done
        bool insert(Departure oneDeparture);
        void heapify(int index, int length);//done
        void resize();//done
        Departure getHeapMin();//done
        void extractHeapMin();//done
        int leftChild(int parentIndex);//done
        int rightChild(int parentIndex);//done
        int parent(int childIndex);//done
        void printHeap();//done
        void build_min_heap(); 

        //add other function definitions here if 100% necessary
        //----
};
//constructor
MinPriorityQueue::MinPriorityQueue(int myCapacity){
    size = 0;
    capacity = myCapacity;
    departureArr = new Departure[capacity];
}
//destructor
MinPriorityQueue::~MinPriorityQueue(){
        delete [] departureArr;
}

//return the array of the heap
Departure * MinPriorityQueue::getDepartureArr(){
    return departureArr;
}

//returns size
int MinPriorityQueue::getSize(){
    return size;
}

//returns capacity
int MinPriorityQueue::getCapacity(){
    return capacity;
}

//returns left child
int MinPriorityQueue::leftChild(int parentIndex){
    return parentIndex * 2  + 1;
}

//returns right child
int MinPriorityQueue::rightChild(int parentIndex){
    return parentIndex * 2 + 2;
}

//returns parent 
int MinPriorityQueue::parent(int childIndex){
    return (childIndex - 1)/2;
}


int MinPriorityQueue::isFound(string oneDepAddress){

    if(size == 0) return -1;
    
    //loop  through the entire array and if it matches one dep address return the index we found it at
    for(int i = 0; i < size; i++){
        if(departureArr[i].depAddress == oneDepAddress) return i;
    }
    return -1;
}



//created another heapify method that has paramter length as well

void MinPriorityQueue::heapify(int index, int length){

      //we find the left index and the right index of the index parameter
    int parent = index;
    int left = leftChild(index);
    int right = rightChild(index);
 //if left the index is less than the size we still have space and if the lefts vin is less we set the root to left
    if(left < length && departureArr[left].d < departureArr[parent].d) parent = left;
      //otherwise if the right is less than the index and is less then the root we set the root to right
    if(right < length && departureArr[right].d < departureArr[parent].d) parent = right;

    //if the root was equal to the index that means neither child was greater so we dont swap
    //otherwise we swap and then heapify from the swaped index downwards
    if(index != parent){
        swap(departureArr[index],departureArr[parent]);
        heapify(parent, length);
    }
}


bool MinPriorityQueue::decreaseKey(int index, Departure oneDepartureWithNewDValue){

    if(index > size) return false;

    //we replace the old d value with the new d value
    departureArr[index].d = oneDepartureWithNewDValue.d; 

    //swap while the child is smaller than the parent
    while(index > 0 && departureArr[index].d < departureArr[parent(index)].d){
        swap(departureArr[index],departureArr[parent(index)]);
        index = parent(index);
    }
    return true;

}



bool MinPriorityQueue::insert(Departure oneDeparture){

    if(isFound(oneDeparture.depAddress) != -1) return false; // already exist

    //set the left most index with the new departure
    departureArr[size] = oneDeparture;

    //use decrease key
    decreaseKey(size, oneDeparture);
    size++;
    return true;
}

Departure MinPriorityQueue::getHeapMin(){
    return departureArr[0];
}

//decrement size and swap the last most index with the first index
//heapify
void MinPriorityQueue::extractHeapMin(){
    if(size != 0){
        swap(departureArr[0],departureArr[size-1]);
        size -=1;
        heapify(0,size);
    }

}



//*********************************************************
void MinPriorityQueue::printHeap()
{
		cout << "\nHeap size = " << getSize() << "\n" << endl;

         Departure temp = departureArr[0];
        
            cout << left;
		    cout << setw(15) << "Departure"
             << setw(12) << "d Value"
             << setw(15) << "PI"
             << "Arrival List" << endl;

        //goes through the heap and prints out the contents of the heap including departure, d value, PI, and arrival list
        for(int i = 0; i < size; i++){

            

            Departure temp = departureArr[i];
            Arrival * arrival = departureArr[i].arrList -> getHead();
            string s = "";

            if(temp.pi == NULL){
                s = "No Parent";
            }else{
                s = temp.pi -> depAddress;
            }
           
    

            cout << left;
		    cout << setw(15) << temp.depAddress
             << setw(12) << fixed << setprecision(2) << temp.d
             << setw(15) << s
             << "";
            departureArr[i].arrList -> printArrivalList();
             
        }
}

//did not use this method 
void MinPriorityQueue::build_min_heap()
{
    int parent = size/2 - 1;

        for(int i = parent; i >= 0; i--){
            heapify(i,size);
        }
}

//************************************************************
//when you create the dummy node, initialize its d value to be
//50000 which represents infinite large


//****************************************************************************
//Given the original departureArr, the function build a min-heap by using d value


//According to above class definition, define all other functions accordingly
//----
//----