/*!
 * \file loadbalancer.cpp
 * \brief Implementation of the loadbalancer simulation
 * \author Brack Harmon
 * \date 6/10/2024
 */

#include "loadbalancer.h"

/*!
 * \brief Constructor for the loadbalancer class.
 * \param s Number of servers.
 * \param c Total clock cycles.
 */
loadbalancer::loadbalancer(int s, int c){
    numServers = s;
    totalClockCycles = c;
}

/*!
 * \brief Generates a random IP address.
 * \return A random IP address as a string.
 */
std::string loadbalancer::generateRandomIPAddress(){

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

/*!
 * \brief Generates the servers for the load balancer.
 */
void loadbalancer::generateServers(){
    
    for(int i = 0; i < numServers; i++){
        //std::cout << "IP address " << i << ":" << generateRandomIPAddress() << std::endl;
        webserver server(i);
        servers.push_back(server);
    }
}

/*!
 * \brief Fills the request queue with random requests.
 */
void loadbalancer::fillQueue(){

    // Initialize random seed
    std::srand(std::time(0));

    std::cout << "---- filling queue ----" << std::endl;
    for(int i = 0; i < numServers * 100; i++){
        request req;
        req.ip = generateRandomIPAddress();
        reqQueue.push(req);
    }

    logFile << "Queue size: " << reqQueue.size() << std::endl;

}

/*!
 * \brief Generates the log file for the load balancer.
 */
void loadbalancer::generateLogFile(){
    
    
    logFile.open("log.txt", std::ios::trunc);

    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file" << std::endl;
        return;
    }

    logFile << "-------- Load Balancer Log file ------" << std::endl;

}


/*!
 * \brief Handles a request for a server.
 * \param server Pointer to the webserver handling the request.
 * \param file Pointer to the log file.
 */
void loadbalancer::handleRequest(webserver* server, std::ofstream* file) {

    //gets the start time based on the system clock's current time
    auto startTime = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);

    // Simulate some work by sleeping for a random duration
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 401 + 100));

    //gets the end time based on the system clock's current time
    auto endTime = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);

    //finds the difference between the start and end time to calculate time duration
    double duration = std::difftime(end_time, start_time);
    *(file) <<  server->getServerID() << " started request " << server->getReqIP() << " which took " << duration << "s" << std::endl;
    server->endProcess();
    
}

/*!
 * \brief Runs the load balancer simulation.
 */
void loadbalancer::run(){

    generateLogFile();
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();

    // Estimate CPU frequency in cycles per second (Hz)
    std::chrono::duration<double> duration = end - start;
    
    // Calculate the time to wait for the target number of cycles
    double targetTimeInMs = totalClockCycles / 1000;

    // Start a busy-wait loop for the target time
    start = std::chrono::high_resolution_clock::now();
    logFile << "Starting..." << std::endl;
    int reqHandled = 0;
    std::cout << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
    
    std::cout << rand() % 200 << std::endl;
    std::vector<std::thread> threads;
    while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() < targetTimeInMs) {

        // Seed with a real random value, if available
        std::random_device rd;

        // Choose a random number generator
        std::mt19937 gen(rd());

        // Define the range
        std::uniform_int_distribution<> dis(1, 10);

        // Generate a random number between 1 and 10
        int randomNumber = dis(gen);

        //1 in 10 chance of adding a new request to the
        if(randomNumber == 1){
            request req;
            req.ip = generateRandomIPAddress();
            logFile << "++ Adding " << req.ip << " to the queue";
            reqQueue.push(req);
        }

        
        for (int j = 0; j < numServers; ++j) {
            if(reqQueue.size() > 0 && !servers.at(j).getStatus()){
                //logFile << "starting request..." << std::endl;
                request req(reqQueue.pop());
                servers.at(j).startRequest(req.ip);
                logFile << "Server: " << servers.at(j).getServerID() << " started request " << servers.at(j).getReqIP() << " at time: " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
                threads.push_back(std::thread(handleRequest,&servers.at(j), &logFile));
                //threads.push_back(std::thread(&webserver::processRequest,&servers.at(j),&logFile));
                
                reqHandled++;
            }
           
        }

        

    }
    for (auto& thread : threads) {
            thread.join();
        }
    
    logFile << "Total number of requests processed: " << reqHandled << std::endl;
    logFile << "Total time to complete: " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
    logFile << "Ending..." << std::endl;

}