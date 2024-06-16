/*!
 * \file loadbalancer.cpp
 * \brief Implementation of the loadbalancer simulation
 * \author Brack Harmon
 * \date 6/10/2024
 */

#include "loadbalancer.h"


/*!
 * \brief converts an ipv4 adress into an integer
 * \param ip string representation of an ip address
 */
uint32_t loadbalancer::ipToInteger(const std::string &ip) {
    std::istringstream iss(ip);
    std::string token;
    uint32_t result = 0;

    while (std::getline(iss, token, '.')) {
        result = (result << 8) | std::stoi(token);
    }

    return result;
}

/*!
 * \brief Determines if an ip adress is in a valid range
 * \param ip string representation of an ip address
 */
bool loadbalancer::isIpInRange(const std::string &ip) {
    uint32_t startRange = ipToInteger("25.0.0.0");
    uint32_t endRange = ipToInteger("250.255.255.255");
    uint32_t ipValue = ipToInteger(ip);

    return ipValue >= startRange && ipValue <= endRange;
}

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
        req.time = rand() % 5 + 1;
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
void loadbalancer::handleRequest(webserver* server, request* req, std::ofstream* file) {

    // Simulate some work by sleeping for a random duration
    std::this_thread::sleep_for(std::chrono::milliseconds((int) req->time));

    //output that the request has finished processing
    *(file) <<  "Server: " << server->getServerID() << " finished request " << server->getReqIP() << " which took " << req->time << "ms" << std::endl;
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
    

    // Start a busy-wait loop for the target time
    start = std::chrono::high_resolution_clock::now();
    logFile << "Starting..." << std::endl;
    logFile << "Starting Queue size: " << reqQueue.size() << std::endl;
    logFile << "Number of servers: " << numServers << std::endl;
    logFile << "Number of clock cycles to run: " << totalClockCycles << std::endl;
    int reqHandled = 0;
    int clockCycle = 0;
    int numInvalidReqs = 0;
    
    std::vector<std::thread> threads;
    while (clockCycle++ < totalClockCycles) {

        // Seed with a real random value, if available
        std::random_device rd;

        // Choose a random number generator
        std::mt19937 gen(rd());

        // Define the range
        std::uniform_int_distribution<> dis(1, 100);

        // Generate a random number between 1 and 100
        int randomNumber = dis(gen);

        //1 in 100 chance of adding a new request to the
        if(randomNumber == 1){
            request req;
            req.ip = generateRandomIPAddress();
            req.time = rand() % 5 + 1;
            logFile << "++ Adding " << req.ip << " to the queue. Queue size is now: " << reqQueue.size() << std::endl;
            reqQueue.push(req);
        }

        //round robin check if servers are available for requests
        for (int j = 0; j < numServers; ++j) {
            if(reqQueue.size() > 0 && !servers.at(j).getStatus()){
                 request req(reqQueue.pop());

                //slow loris detection
                if(req.time > 4){
                    logFile << "Slow loris detected. removing request: " << req.ip << std::endl;
                    numInvalidReqs++;
                    break;
                }

                //ip blocker firewall
                if(!isIpInRange(req.ip)){
                    logFile << "Request outside of range. removing request: " << req.ip << std::endl;
                    numInvalidReqs++;
                    break;
                }

                //dos attack detection
                if((int)reqQueue.size() > numServers * 200){
                    logFile << "Warning: Potential DOS attack detected. large queue size of: " << reqQueue.size() << std::endl;
                }

                servers.at(j).setReqIP(req.ip);
                servers.at(j).startRequest();
                logFile << "Server: " << servers.at(j).getServerID() << " starting request " << servers.at(j).getReqIP() << " at clock cycle: " << clockCycle << std::endl;
                threads.push_back(std::thread(handleRequest,&servers.at(j),&req, &logFile));
                //threads.push_back(std::thread(&webserver::processRequest,&servers.at(j),&logFile));
                
                reqHandled++;
            }
           
        }   

    }

    for (auto& thread : threads) {
            thread.join();
        }
    
    logFile << "Total number of requests processed: " << reqHandled << std::endl;
    logFile << "Total number of invalid requests: " << numInvalidReqs << std::endl;
    logFile << "Ending queue size: " << reqQueue.size() << std::endl;
    logFile << "Total time to complete: " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() << "s" << std::endl;
    logFile << "Range of task times: 1 to 4 ms" << std::endl;
    logFile << "Ending..." << std::endl;

}