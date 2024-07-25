//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Name: Yashraj Singh
// ASU ID: 1224341092
// Description: //---- is where you should add your own code
//********************************************************************

//include necessary header file here
//----
#include "Graph1.h"

using namespace std;

void getDepartureInfo(string oneLine, string& depAddress, ArrivalList* arrList);
void getArrivalInfo(string oneArrivalInfo, string& arrAddress, double& distance, string& roadCategory); //**optional
string oneLine;

int main()
{
   int count;       //a variable for number of nodes
   string oneLine, sourceDepAddress;
   string answer = "yes";       //a variable to decide whether to run Dijkstra multiple times or not

   //cout << "Enter number of departure address: ";
   cin >> count;
   cin.ignore(20, '\n');

   //Create an array called 'departureArr' that holds 'count' number of Departure objects
   //----

   Departure * departureArr = new Departure[count];
   MinPriorityQueue * heap = new MinPriorityQueue(count);

   //Initialize departureArr. Note: you will need to initialize each of the instance variable
   //including arrival list

   for(int i = 0; i < count; i++)
   {

      departureArr[i].d = 10000.00 + i;  //***this is to make sure each node has different d value
      departureArr[i].pi = NULL;
      departureArr[i].arrList = new ArrivalList();
      departureArr[i].depAddress = sourceDepAddress;
      //----
       getline(cin, oneLine);
       getDepartureInfo(oneLine,departureArr[i].depAddress,departureArr[i].arrList);
       //departureArr[i].arrList ->printArrivalList();
       heap -> insert(departureArr[i]);
   }


    
    Graph* graph = new Graph(count,heap);

   //print the graph adjacency list before running Dijkstra algorithm
   cout << "\nPrint the graph adjacency list before running Dijkstra algorithm" << endl;

   heap -> printHeap();

   /*
   Enter departure address: 
   Print the Dijkstra algorithm running result
   */

  cout << "\nEnter departure address:\n" << endl;
  getline(cin, oneLine);
  cout << "\nPrint the Dijkstra algorithm running result\n" <<endl;

   graph -> dijkstra(oneLine);

   graph -> printDijkstraPath(oneLine);

   //do while loop to keep asking if the user wants to print djikstra path on the verticies 
   //type no to stop
   do{

      cout << "\nFind shortest path for another departure address(yes or no):\n" << endl;
      getline(cin, oneLine);
      if(oneLine == "no") break;

      cout << "Enter departure address:\n" << endl;
      getline(cin, oneLine);

      if(graph->getDepartureHeap()->isFound(oneLine)== -1){
         cout << oneLine << " does NOT exist" << endl;
      }else{

         cout << "\nPrint the Dijkstra algorithm running result\n" << endl;

         graph -> dijkstra(oneLine);

         graph -> printDijkstraPath(oneLine);
      }
      
   }while(true);

   cout << "Program terminate" << endl;


   

   //Next you need to design a sentinel-value controlled while loop base on 'answer'
   //If user answer is 'yes', get departure address, run Dijkstra algorithm, print
   //shortest traveling time and path, then ask the user whether he want to continue or not...

}

//********************************************************************************
//Give one line in input file, this function extract tokens and get departure address
//and all arrival info.
void getDepartureInfo(string oneLine, string& depAddress, ArrivalList* arrList)
{
    //the departure is up to the first ( so we extract that 
   string delimiter = ",";
   int pos=oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   depAddress = token;
   oneLine.erase(0, pos+delimiter.length());

  //need to extract all the adjacent vectors  
  //if the oneLine is not empty keep looping as there are still vertixes
   while(oneLine.length() != 0){

    string arrAddress;
    double distance;
    string roadCategory;

   //this the arrival code below
     string delimiter = "(";
     int pos=oneLine.find(delimiter);
     string token = oneLine.substr(0,pos);
     arrAddress = token;
     oneLine.erase(0, pos+delimiter.length());

     if(token != ","){
        delimiter = "/";
        pos=oneLine.find(delimiter);
        token = oneLine.substr(0,pos);
        distance = stod(token);
        oneLine.erase(0, pos+delimiter.length());

        delimiter = ")";
        pos=oneLine.find(delimiter);
        token = oneLine.substr(0,pos);
         roadCategory = token;
        oneLine.erase(0, pos+delimiter.length());

        delimiter = ",";
        pos = oneLine.find(delimiter);
        oneLine.erase(0,pos+delimiter.length());
        arrList -> addArrival(arrAddress,distance,roadCategory);
     }else{
         delimiter = ",";
         pos = oneLine.find(delimiter);
         oneLine.erase(0,pos+delimiter.length());
     }
     
   }
}
   



   


//******************************************************************************************
//Given such as Y(1803.2/I), this function extracts arrival Address "Y", distance 1803.2
//and roadCategory "I" info. out
void getArrivalInfo(string oneArrivalInfo, string& arrAddress, double& distance, string& roadCategory)
{

    string delimiter = "(";
   int pos=oneLine.find(delimiter);
    string token = oneLine.substr(0,pos);
   arrAddress = token;
   oneLine.erase(0, pos+delimiter.length());

   delimiter = "/";
   pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
   distance = stod(token);
   oneLine.erase(0, pos+delimiter.length());

   delimiter = ")";
   pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
   roadCategory = token;
   oneLine.erase(0, pos+delimiter.length());

   delimiter = ",";
    pos = oneLine.find(delimiter);
    //may cause an error
    oneLine.erase(0,pos+delimiter.length());

   //cout << oneArrivalInfo << endl;

}