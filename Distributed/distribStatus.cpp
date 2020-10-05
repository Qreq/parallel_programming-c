#include <iostream>
#include "mpi.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  char node_name[MPI_MAX_PROCESSOR_NAME];
  int rank,size, namelen,*buf;
  MPI_File fh;
  MPI_Comm comm;
  MPI_Status status;
  comm = MPI_COMM_WORLD;
  
  
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(node_name, &namelen);
  
  FILE *pPipeProc, *pPipeClock, *pPipeRAM;
  pPipeProc = popen("grep 'cpu cores' /proc/cpuinfo | head -n 1", "r");
  pPipeClock = popen("grep 'cpu MHz' /proc/cpuinfo | tail -n 1", "r");
  pPipeRAM = popen("free -m | grep 'Mem'", "r");
  char bufCore[1024],bufClock[1024], bufRAM[1024];
  
  fgets(bufCore, 1024, pPipeProc);
  fgets(bufClock, 1024, pPipeClock);
  fgets(bufRAM, 1024, pPipeRAM);
  
  std::cout << bufCore << std::endl;
  std::cout << bufClock << std::endl;
  std::cout << "RAM for node_name " << node_name << " = " << bufRAM << std::endl;
  
  if (rank==0) {
    std::cout << "Node Count = " << size << std::endl;
    
    std::string sCore(bufCore);
    int cores_per = sCore[12] - '0';
    
    std::cout << "total cores = " <<  cores_per* size << std::endl; //implies single digit core number, since stoi does not work 
    
  
  }
  MPI_Finalize();
}