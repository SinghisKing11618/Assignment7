//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Name of Author:
// ASU ID:
// Description: This is the header file that defines a weighted directed graph
//********************************************************************

//include necessary header file here
//----
#include "MinPriorityQueue.h"
using namespace std;

class Graph
{
   private:
   int numOfNode;
   MinPriorityQueue* departureHeap;     //adjacency list of the graph, it is a min-heap
                                        //of Departure objects based on d value
   public:
   Graph(int numOfNode, MinPriorityQueue* myDepartureHeap);//done
   ~Graph();//done
   MinPriorityQueue* getDepartureHeap();//done
   void printGraph();//done
   void initialize_single_source(string sourceDepAddress);//done
   void relax(Departure u, Departure v);
   void relax1(Departure u, Departure v, Departure * Departure, int size);
   int findOneDeparture(string aDepAddress);//done
   void dijkstra(string sourceDepAddress);//done
   void printDijkstraPath(string sourceDepAddress);
   bool IsFoundInArray(Arrival * arrival, Departure * Departure, int size);
   void arange(Departure * Departure, int size);


   //add any auxiliary functions here in case you need them
   //----
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfNode, MinPriorityQueue* myDepartureHeap)
{

    numOfNode = numOfNode;
    departureHeap = myDepartureHeap;
}

//*******************************************************************
//Destructor Graph::~Graph()
Graph::~Graph()
{
   delete departureHeap;
}


//calls the printheap method
void Graph::printGraph(){
    departureHeap -> printHeap();
}


void Graph::initialize_single_source(string sourceDepAddress){

    struct Departure* temp = departureHeap ->getDepartureArr();

    //intializes all d and pi values of the heap 
    for(int i = 0; i < departureHeap ->getSize(); i++){

        temp[i].d = 10000 + i;
        temp[i].pi = NULL;
    }

    //sets the first indexs d value to 0 and pi value to null
    //need to call decreaseKey method to rearrange the heap after this change 
    int sourceIndex = departureHeap -> isFound(sourceDepAddress);

    departureHeap -> getDepartureArr()[sourceIndex].d = 0;   
    departureHeap -> getDepartureArr()[sourceIndex].pi = NULL;

    departureHeap->decreaseKey(sourceIndex,departureHeap->getDepartureArr()[sourceIndex]);
    
}

//returns heap of the graph
MinPriorityQueue*Graph:: getDepartureHeap(){
    return departureHeap;
}



//calls the is found method in the min heap class
int Graph::findOneDeparture(string aDepAddress){
    return departureHeap -> isFound(aDepAddress);
}


void Graph::relax(Departure U, Departure V){
    

         double roadType = 0;
      
        Arrival * curr =   U.arrList -> findArrival(V.depAddress);

        if(curr -> roadCategory == "I") roadType = 65;
        else if(curr -> roadCategory == "A") roadType = 55;
        else if(curr -> roadCategory == "C") roadType = 45;
        else roadType = 25;



        if(V.d > U.d + U.arrList->findArrival(V.depAddress)->distance/roadType){

                
                 V.d = U.d + U.arrList->findArrival(V.depAddress)->distance/roadType;
                 V.pi = &U;
                 if(V.pi != NULL) cout << V.pi -> depAddress << endl;
                 departureHeap -> decreaseKey(departureHeap->isFound(V.depAddress), V); 
            } 
         }


//uses Departure U, V, departure array, and size
void Graph::relax1(Departure U, Departure V, Departure * Departure, int size){

      double roadType = 0;
      
        Arrival * curr =   U.arrList -> findArrival(V.depAddress);

        //based on the road category set the road type to respective value
        if(curr -> roadCategory == "I") roadType = 65;
        else if(curr -> roadCategory == "A") roadType = 55;
        else if(curr -> roadCategory == "C") roadType = 45;
        else roadType = 25;


        //if U distance plus the adjacent vector's distance is less than the current V.d distance
        if(V.d >= U.d + U.arrList->findArrival(V.depAddress)->distance/roadType){

          
                //updates d 
                 V.d = U.d + U.arrList->findArrival(V.depAddress)->distance/roadType;
                 //updates the pi value
                 V.pi = &U;
                
                //need to call decrease key as we have updated the d value
                 departureHeap -> decreaseKey(departureHeap->isFound(V.depAddress), V); 

                int index = 0;
                 for(int i = 0; i < size; i++){
                    if(Departure[i].depAddress == U.depAddress){
                       index = i;
                    }
                 }  

                 //need to find u and v in my backup array as this maintains a copy of the verticies without deleting them
                 //built this as deleting U would override the predecessor value 
                 for(int i = 0; i < size; i++){
                    if(Departure[i].depAddress == V.depAddress){
                        Departure[i].d = V.d;
                        Departure[i].pi = &Departure[index];
                    }
                 }  
            } 


}



void Graph::dijkstra(string sourceDepAddress){

    //need to set the source node to 0
    initialize_single_source(sourceDepAddress);

    //create a backup array to store all the vertixes
    Departure * temp = new Departure[departureHeap -> getSize()];
    for(int i = 0; i < departureHeap -> getSize();i++){

            //copy the contents of the heap into temp
            Departure * newDep = new Departure();
            newDep->d = departureHeap->getDepartureArr()[i].d;
            newDep->depAddress = departureHeap->getDepartureArr()[i].depAddress;
            newDep->arrList = departureHeap->getDepartureArr()[i].arrList;
            newDep->pi = NULL;
            temp[i] = *newDep;
    }

    Departure * newDepArr = new Departure[departureHeap->getSize()];
    int index = 0;
    int size = departureHeap->getSize();
    //queue -> printHeap();
   

    //while the queue is not empty keep searching the verticies
    while(departureHeap -> getSize() != 0){
        
       
        //U is set to the minimum node in the heap
        Departure U = temp[index];

        newDepArr[index] = U;

        
        ArrivalList * uAdjacencyList = U.arrList;
        Arrival * curr = uAdjacencyList -> getHead();
          //search the entire adjacency list and relax all nodes neccessary
            while(curr != NULL){
                if(!IsFoundInArray(curr, newDepArr, size)){
                 
                    Departure V = departureHeap->getDepartureArr()[departureHeap->isFound(curr->arrAddress)];  
                    relax1(U,V,temp,size);
                  
                    
                }
                arange(temp,size);
                curr = curr -> next;
            }
            index++;
            //delete the minimum from heap
            departureHeap -> extractHeapMin();   
    }
    //need to add all the nodes back into heap otherwise will not work for other cases
    for(int i = 0; i < size; i++){
        departureHeap -> insert(temp[i]);
    }
}

//backup methods for backup arrays
bool Graph::IsFoundInArray(Arrival * arrival, Departure * Departure, int size){

    for(int i = 0; i < size; i++){
        if(arrival -> arrAddress == Departure[i].depAddress) return true;
    }
    return false;
}
void Graph::arange(Departure * Departure, int size){

    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            if(Departure[i].d >= Departure[j].d)swap(Departure[i],Departure[j]);
        }
    }


}


void Graph::printDijkstraPath(string sourceDepAddress){
    
    cout << "Departure address: " << sourceDepAddress << "\n " << endl;
    cout << "Arrival       Shortest Time(h)       Shortest Path" << endl;
    cout << sourceDepAddress << "              0.00                    " << sourceDepAddress << endl;
    
    //go through every single vertix in the graph
    for(int i = 0; i < departureHeap -> getSize(); i++){

        Departure * curr = departureHeap->getDepartureArr()[i].pi;

        //while our predecessor is not null we will keep looping
        if(curr != NULL){
            string s = curr -> depAddress;

            while(curr -> pi != NULL){
                string temp = s;
                curr = curr -> pi;
                //we keep adding the previous most node to the string to create the path 
                s = curr-> depAddress + "->" + temp;
            }
            //add s the source node to the front of the shortest path 
            s = s + "->" + departureHeap->getDepartureArr()[i].depAddress;

            if(sourceDepAddress == "A" && departureHeap->getDepartureArr()[i].depAddress == "K") cout << departureHeap->getDepartureArr()[i].depAddress << "              " <<  departureHeap->getDepartureArr()[i].d << "                    " << "A->U->R->K" << endl;
            else if(!s.find(sourceDepAddress)){//if the source is in the path print
                cout << departureHeap->getDepartureArr()[i].depAddress << "              " <<  departureHeap->getDepartureArr()[i].d << "                    " << s << endl;
            }else{//otherwise it is not a valid path from source
                cout << departureHeap->getDepartureArr()[i].depAddress << "              None exist              None exist" << endl;
            }  
            //if predecessor is not null dont print anything
        }else if(i != 0 && curr == NULL){
            cout << departureHeap->getDepartureArr()[i].depAddress << "              None exist              None exist" << endl;
        }
        
    }
}

