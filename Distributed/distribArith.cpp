#include "mpi.h"
#include <list>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <thread>

std::list<int> unavailableNodes = {};
int current_val;
std::string lastUsedOp = "";

bool isNodeAvailable(int node){
  if (node != unavailableNodes.front() && node != unavailableNodes.back())return true;
  return false;
}

void removeNode(int node){
  unavailableNodes.pop_front();
}
void addNode(int node){
  unavailableNodes.push_back(node);
}
int determineArith(int randNum, int numPassed){
  if (randNum < 3 && lastUsedOp != "+"){
    lastUsedOp = "+";
    current_val += numPassed;
    return current_val + numPassed;
  }
  if (randNum < 6 && lastUsedOp != "-"){
    lastUsedOp = "-";
    current_val -= numPassed;
    return current_val - numPassed;
  }
  if (randNum < 9 && lastUsedOp != "*"){
    lastUsedOp = "*";
    current_val *= numPassed;
    return current_val * numPassed;
  }
}
int determineNextNode(int currentNode, int mpiSize){
  int destination;
  do{
    destination = rand()%mpiSize;
  }while(!isNodeAvailable(destination));
  return destination;
}
int main(){
  
  srand(time(NULL));
  MPI_Init(NULL, NULL);
  char node_name[MPI_MAX_PROCESSOR_NAME];
  int rank,size, namelen;
  MPI_Comm comm;
  comm = MPI_COMM_WORLD;
  int passNum = 6;
  int current_node = 0;
  
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(node_name, &namelen);
  
  while(true){
    if(rank == 0){
      addNode(current_node);
      int nextNode = determineNextNode(current_node, size);
      addNode(nextNode);
      int operatorDet = rand()%10;
      int updatedVal = determineArith(operatorDet, passNum);
      std::cout << "New value is: " << updatedVal << " on node " << nextNode << std::endl;
      removeNode(current_node);
      current_node = nextNode;
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  }
  
  MPI_Finalize();
}