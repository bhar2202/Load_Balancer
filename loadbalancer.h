/*
    Author: Brack Harmon
    Date: 6/10/2024
 
 */

#include "RequestQueue.cpp"
#include "webserver.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <chrono>
#include <thread>
#include <fstream>

class loadbalancer{

    
    private:
        
        std::vector<webserver> servers;
        std::string generateRandomIPAddress(int serverID);
        std::ofstream logFile;
        void generateLogFile();

    public:
        RequestQueue reqQueue;
        int numServers;
        int totalClockCycles;

        loadbalancer(int numServers,int numClockCycles);
        void generateServers();
        void fillQueue();
        void run();
        

};