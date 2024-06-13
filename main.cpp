/*
    Author: Brack Harmon
    Date: 6/10/2024
 
 */


#include "loadbalancer.cpp"


#include <iostream>
#include <vector>
using std::cout;


int main(){
    std::cout << "--------- Load balancing -----------" << std::endl;
    std::cout << "Number of Servers: ";
    int numServers = 0;
    double runtime = 0.0;
    std::cin >> numServers;
    std::cout << "Number of clock cycles to run the load balancer: ";
    std::cin >> runtime;

    //initalize load balancer to handle 10 servers
    loadbalancer lb(numServers,runtime);

    std::cout << "------- Creating Servers --------" << std::endl;
    lb.generateServers();

    std::cout << "------- Generating Full Queue--------" << std::endl;
    lb.fillQueue();

    std::cout << "------- Starting servers ---------" << std::endl;
    lb.run();
    

    return 0;
}