#include <vector>
#include "mpi.h"
#include <fstream>
#include <omp.h>
#include <algorithm>
#include <string>

std::vector<std::string> make_sentence(std::string s){
  std::string word = "";
  std::vector<std::string> sentence;
  for(int i = 0; i<s.size(); ++i){
    if (s[i] != ' '){
      word += s[i];
    }
    else if (s[i] == ' '){
      sentence.push_back(word);
      word = "";
    }
  }
  if (word != ""){
    sentence.push_back(word);
  }
  return sentence;
}
int main(){
  
  MPI_Init(NULL, NULL);
  char node_name[MPI_MAX_PROCESSOR_NAME];
  int rank,size, namelen;
  MPI_Comm comm;
  comm = MPI_COMM_WORLD;
  
  
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(node_name, &namelen);
  
  std::string line;
  std::vector<std::string> poemLines = {};
  std::vector<std::string> jumbledUpPoem = {};
  std::ifstream poem("ritmo_rhythm.txt");
  
  while(getline(poem, line)){
    poemLines.emplace_back(line);
  }
  
  jumbledUpPoem = poemLines;
  if (rank == 0){
    std::vector<std::string> originalPoem = poemLines;
  }
  #pragma omp parallel for num_threads(1)
  for (int i = 0; i < poemLines.size(); i++){
    if (rank == i){
      std::string j_line = jumbledUpPoem[i];
      //std::cout << j_line << std::endl;
      std::vector<std::string> sentence = make_sentence(j_line);
      std::random_shuffle(sentence.begin(), sentence.end());
      for(auto word : sentence){
        std::cout << word << " ";
      }
     std::cout << std::endl;      
    }
  }
  MPI_Finalize();
}