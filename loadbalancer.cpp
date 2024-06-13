/*
    Author: Brack Harmon
    Date: 6/10/2024
 
 */

#include "loadbalancer.h"
loadbalancer::loadbalancer(int s, int c){
    numServers = s;
    totalClockCycles = c;
    
}

std::string loadbalancer::generateRandomIPAddress(int serverID){
    // Initialize random seed
    std::srand(std::time(0) + serverID);

    std::ostringstream ip;
    for (int i = 0; i < 4; ++i) {
        // Generate a random number between 0 and 255
        int octet = std::rand() % 256;
        ip << octet;
        if (i < 3) {
            ip << ".";
        }
    }

    return ip.str();
}

void loadbalancer::generateServers(){
    
    for(int i = 0; i < numServers; i++){
        std::cout << "IP address " << i << ":" << generateRandomIPAddress(i) << std::endl;
        //webserver server(5);
        //servers.push_back(server);
    }
}

void loadbalancer::fillQueue(){

    std::cout << "---- filling queue ----" << std::endl;
    for(int i = 0; i < numServers * 100; i++){
        request req;
        reqQueue.push(req);
    }

    std::cout << "Queue size: " << reqQueue.size();

}

void loadbalancer::generateLogFile(){
    
logFile.open("log.txt",std::ios::out | std::ios::app);

    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file" << std::endl;
        return;
    }

    logFile << "-------- Load Balancer Log file ------";


}

void loadbalancer::run(){
    generateLogFile();

}