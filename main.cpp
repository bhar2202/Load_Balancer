/*
    Author: Brack Harmon
    Date: 6/10/2024
 
 */

#include "webserver.cpp"
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
    std::cout << "Time to run the load balancer: ";
    std::cin >> runtime;

    std::cout << "------- Creating Servers --------" << std::endl;
    std::vector<webserver> servers;
    
    for(int i = 0; i < numServers; i++){
        webserver server;
        servers.push_back(server);
    }

    std::cout << "------- Generating Full Queue--------" << std::endl;

    loadbalancer lb;
    lb.fillQueue(numServers);

    

    return 0;
}