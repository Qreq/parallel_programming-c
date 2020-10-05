#include <iostream>
#include <cmath>
#include <cstdlib>
#include <thread>
#include <fstream>
#include <vector>
#include <mutex>
#include <condition_variable>

int pos = 0;

std::mutex mutx;
std::condition_variable cv;
bool ready = false;

void printArray(std::vector<std::string> array, int pos){
    
    std::unique_lock<std::mutex> lck (mutx);//critical section
    while(!ready) cv.wait(lck);
    
    std::cout << array.at(pos) << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
}
void increasePos(){
    pos++;
}

void start(){
    std::unique_lock<std::mutex> lck (mutx);//critical section
    ready = true;
    cv.notify_all();
}
int main(){

    std::string line;
    std::vector<std::string> poemLines = {};
    std::ifstream poem("ritmo_rhythm.txt");
    std::thread t1, t2;
    
    
    while(getline(poem, line)){
        poemLines.emplace_back(line);
    }
    start();
    while(pos < poemLines.size()){
        t2 = std::thread(printArray, poemLines, pos);
        t2.join();//prevents unpredictable behaviour
        t1 = std::thread(increasePos);
        t1.join();
    }
    
    return 0;
}
