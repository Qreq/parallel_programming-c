#include <omp.h>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

std::string determine_sched_type(){
    std::string type;
    do{
        std::cout << "What type of scheduling would you like?(auto, static, dynamic, guided) ";
        std::getline(std::cin,type);
        if (type == "auto") return type;
        if (type == "static") return type;
        if (type == "dynamic") return type;
        if (type == "guided") return type;
    }while(true);
    return type;
}
int main(){

    std::string type_sched = determine_sched_type();
    if (type_sched == "auto") omp_set_schedule(omp_sched_auto,0);
    if (type_sched == "static") omp_set_schedule(omp_sched_static,0);
    if (type_sched == "dynamic") omp_set_schedule(omp_sched_dynamic,0);
    if (type_sched == "guided") omp_set_schedule(omp_sched_guided,0);

    std::vector<int> v1 = {5,14,10};
    std::vector<int> v2 = {7,-8,-14};
    std::vector<int> v3 = {-2,9,8};
    std::vector<int> v4 = {15,-6,3};
    std::vector<int> v5 = {12,4,-5};
    std::vector<int> v6 = {4,20,17};
    std::vector<int> v7 = {-16,5,-1};
    std::vector<int> v8 = {-11,3,16};
    std::vector<int> v9 = {3,10,-19};
    std::vector<int> v10 = {-16,7,4};

    std::cout << "Original State of Vectors:" << std::endl;
    std::cout << v1.at(0) << "," << v1.at(2) << "," << v1.at(2) << std::endl;
    std::cout << v2.at(0) << "," << v2.at(2) << "," << v2.at(2) << std::endl;
    std::cout << v3.at(0) << "," << v3.at(2) << "," << v3.at(2) << std::endl;
    std::cout << v4.at(0) << "," << v4.at(2) << "," << v4.at(2) << std::endl;
    std::cout << v5.at(0) << "," << v5.at(2) << "," << v5.at(2) << std::endl;
    std::cout << v6.at(0) << "," << v6.at(2) << "," << v6.at(2) << std::endl;
    std::cout << v7.at(0) << "," << v7.at(2) << "," << v7.at(2) << std::endl;
    std::cout << v8.at(0) << "," << v8.at(2) << "," << v8.at(2) << std::endl;
    std::cout << v9.at(0) << "," << v9.at(2) << "," << v9.at(2) << std::endl;
    std::cout << v10.at(0) << "," << v10.at(2) << "," << v10.at(2) << std::endl;
    srand(time(NULL));
    #pragma omp parallel for schedule(runtime)
    for (int z = 0; z <10; z++)
        {
            const auto processor_count = std::thread::hardware_concurrency();
            std::cout << "Processor Count: " << processor_count << std::endl;

            system("cat /proc/cpuinfo | grep 'cpu MHz'");
            system("free -m | grep 'Mem'");
            system("du -sh /home"); //cannot gain access to some folders due to not having sudo access
        }
    #pragma omp parallel for num_threads(1)
    for (int step = 0; step < 5; step++)
        {
            
            short co_ord_rand = rand()%3;
            short rand_direct = rand()%100 +1; // x>50, increment.  x<=50, decerement

            //if chosen to add
            if (rand_direct > 50){
                v1.at(co_ord_rand)++;
                v2.at(co_ord_rand)++;
                v3.at(co_ord_rand)++;
                v4.at(co_ord_rand)++;
                v5.at(co_ord_rand)++;
                v6.at(co_ord_rand)++;
                v7.at(co_ord_rand)++;
                v8.at(co_ord_rand)++;
                v9.at(co_ord_rand)++;
                v10.at(co_ord_rand)++;
            }else{
                v1.at(co_ord_rand)--;
                v2.at(co_ord_rand)--;
                v3.at(co_ord_rand)--;
                v4.at(co_ord_rand)--;
                v5.at(co_ord_rand)--;
                v6.at(co_ord_rand)--;
                v7.at(co_ord_rand)--;
                v8.at(co_ord_rand)--;
                v9.at(co_ord_rand)--;
                v10.at(co_ord_rand)--;
            }
            //questions wants 5th and 10th steps
            if (step == 4){
                std::cout << "Values of vectors on step #" << step + 1 << ": " << std::endl;
                std::cout << v1.at(0) << "," << v1.at(2) << "," << v1.at(2) << std::endl;
                std::cout << v2.at(0) << "," << v2.at(2) << "," << v2.at(2) << std::endl;
                std::cout << v3.at(0) << "," << v3.at(2) << "," << v3.at(2) << std::endl;
                std::cout << v4.at(0) << "," << v4.at(2) << "," << v4.at(2) << std::endl;
                std::cout << v5.at(0) << "," << v5.at(2) << "," << v5.at(2) << std::endl;
                std::cout << v6.at(0) << "," << v6.at(2) << "," << v6.at(2) << std::endl;
                std::cout << v7.at(0) << "," << v7.at(2) << "," << v7.at(2) << std::endl;
                std::cout << v8.at(0) << "," << v8.at(2) << "," << v8.at(2) << std::endl;
                std::cout << v9.at(0) << "," << v9.at(2) << "," << v9.at(2) << std::endl;
                std::cout << v10.at(0) << "," << v10.at(2) << "," << v10.at(2) << std::endl;
            }
        }
         #pragma omp parallel num_threads(1) 
    for (int steppt2 = 0; steppt2 <=5; steppt2++)
        {
            
            short co_ord_rand = rand()%3;
            short rand_direct = rand()%100 +1; // x>50, increment.  x<=50, decerement

            //if chosen to add
            if (rand_direct > 50){
                v1.at(co_ord_rand)++;
                v2.at(co_ord_rand)++;
                v3.at(co_ord_rand)++;
                v4.at(co_ord_rand)++;
                v5.at(co_ord_rand)++;
                v6.at(co_ord_rand)++;
                v7.at(co_ord_rand)++;
                v8.at(co_ord_rand)++;
                v9.at(co_ord_rand)++;
                v10.at(co_ord_rand)++;
            }else{
                v1.at(co_ord_rand)--;
                v2.at(co_ord_rand)--;
                v3.at(co_ord_rand)--;
                v4.at(co_ord_rand)--;
                v5.at(co_ord_rand)--;
                v6.at(co_ord_rand)--;
                v7.at(co_ord_rand)--;
                v8.at(co_ord_rand)--;
                v9.at(co_ord_rand)--;
                v10.at(co_ord_rand)--;
            }
            //questions wants 5th and 10th steps
            if (steppt2 == 5){
                std::cout << "Values of vectors on step #10: " << std::endl;
                std::cout << v1.at(0) << "," << v1.at(2) << "," << v1.at(2) << std::endl;
                std::cout << v2.at(0) << "," << v2.at(2) << "," << v2.at(2) << std::endl;
                std::cout << v3.at(0) << "," << v3.at(2) << "," << v3.at(2) << std::endl;
                std::cout << v4.at(0) << "," << v4.at(2) << "," << v4.at(2) << std::endl;
                std::cout << v5.at(0) << "," << v5.at(2) << "," << v5.at(2) << std::endl;
                std::cout << v6.at(0) << "," << v6.at(2) << "," << v6.at(2) << std::endl;
                std::cout << v7.at(0) << "," << v7.at(2) << "," << v7.at(2) << std::endl;
                std::cout << v8.at(0) << "," << v8.at(2) << "," << v8.at(2) << std::endl;
                std::cout << v9.at(0) << "," << v9.at(2) << "," << v9.at(2) << std::endl;
                std::cout << v10.at(0) << "," << v10.at(2) << "," << v10.at(2) << std::endl;
            }
        }
}