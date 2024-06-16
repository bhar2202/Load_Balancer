/*!
 * \file loadbalancer.h
 * \brief headerfile for loadbalancer class
 * \author Brack Harmon
 * \date 6/10/2024
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

/*!
 * \brief functions for a load balancer simulation
 */
class loadbalancer{
    
    private:
        int numServers;
        int totalClockCycles;
        std::vector<webserver> servers;
        std::string generateRandomIPAddress();
        void generateLogFile();
        uint32_t ipToInteger(const std::string &ip);
        bool isIpInRange(const std::string &ip);

    public:
        RequestQueue reqQueue;
        std::ofstream logFile;
        loadbalancer(int numServers,int numClockCycles);
        static void handleRequest(webserver* server, request* req, std::ofstream* file);
        void generateServers();
        void fillQueue();
        void run();

};