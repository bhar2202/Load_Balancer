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
#include <mutex>
#include <random>

class loadbalancer{

    
    private:
        
        std::vector<webserver> servers;
        std::string generateRandomIPAddress(int serverID);
        
        void generateLogFile();

    public:
        RequestQueue reqQueue;
        int numServers;
        int totalClockCycles;
        std::ofstream logFile;
        loadbalancer(int numServers,int numClockCycles);
        static void handleRequest(int reqID);
        void generateServers();
        void fillQueue();
        void run();
        

};