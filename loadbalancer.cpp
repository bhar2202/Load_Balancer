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

    //empties log file
    logFile.clear();

    logFile << "-------- Load Balancer Log file ------" << std::endl;


}

void loadbalancer::handleRequest(int threadId) {
    auto startTime = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);
    //log("Thread " + std::to_string(threadId) + " started at " + std::ctime(&start_time));

    // Simulate some work by sleeping for a random duration
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 200 + 50));

    auto endTime = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    //log("Thread " + std::to_string(threadId) + " ended at " + std::ctime(&end_time));
}

void loadbalancer::run(){
    generateLogFile();
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();

    // Estimate CPU frequency in cycles per second (Hz)
    std::chrono::duration<double> duration = end - start;
    double cyclesPerSecond = std::chrono::high_resolution_clock::period::den / std::chrono::high_resolution_clock::period::num;
    
    // Calculate the time to wait for the target number of cycles
    double targetTimeInMs = totalClockCycles / 1000;

    // Start a busy-wait loop for the target time
    start = std::chrono::high_resolution_clock::now();
    logFile << "Starting..." << std::endl;
    int i = 0;
    int reqHandled = 0;
    std::cout << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
    
    std::cout << rand() % 200 << std::endl;
    
    while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() < targetTimeInMs) {
        // Busy-wait loop to simulate running for the target number of cycles
        logFile << "time " << i++ << ":" << std::endl;

        // Seed with a real random value, if available
    std::random_device rd;

    // Choose a random number generator
    std::mt19937 gen(rd());

    // Define the range
    std::uniform_int_distribution<> dis(1, 10);

    // Generate a random number between 1 and 10
    int randomNumber = dis(gen);

    if(randomNumber == 1){
        request req;
        reqQueue.push(req);
    }

        std::vector<std::thread> threads;
        for (int j = 0; j < numServers; ++j) {
            if(reqQueue.size() > 0){
                //logFile << "starting request..." << std::endl;
                //threads.push_back(std::thread(handleRequest, j));
            
                reqQueue.pop();
                reqHandled++;
            }
            
           
        }

        for (auto& thread : threads) {
            thread.join();
        }

    }
    
    logFile << "Total number of requests processed: " << reqHandled << std::endl;
    logFile << "Total time to complete: " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
    logFile << "Ending..." << std::endl;
}