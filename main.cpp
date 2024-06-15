/*!
 * \file main.cpp
 * \brief main launcher for the program
 * \author Brack Harmon
 * \date 6/10/2024
 */

#include "loadbalancer.cpp"
#include <iostream>
#include <vector>

/*!
 * \brief The main launcher for the project
 */
int main(){
    
    //variables to store input
    int numServers = 0;
    double runtime = 0.0;

    //user input
    std::cout << "--------- Load balancing -----------" << std::endl;
    std::cout << "Number of Servers: ";
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