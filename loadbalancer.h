/*
    Author: Brack Harmon
    Date: 6/10/2024
 
 */

#include "RequestQueue.cpp"
#include "webserver.cpp"
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
        std::string generateRandomIPAddress();
        
        void generateLogFile();

    public:
        RequestQueue reqQueue;
        int numServers;
        int totalClockCycles;
        std::ofstream logFile;
        loadbalancer(int numServers,int numClockCycles);
        static void handleRequest(webserver* server, std::ofstream* file);
        void generateServers();
        void fillQueue();
        void run();
        

};