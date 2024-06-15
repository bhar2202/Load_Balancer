/*
    Author: Brack Harmon
    Date: 6/10/2024
 
 */

#include "webserver.h"

webserver::webserver(int id){
    serverID = id;
}

// void webserver::processRequest(std::ofstream* file){

//     auto startTime = std::chrono::system_clock::now();
//     std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);
//     //log("Thread " + std::to_string(threadId) + " started at " + std::ctime(&start_time));

//     // Simulate some work by sleeping for a random duration
//     std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 200 + 50));

//     auto endTime = std::chrono::system_clock::now();
//     std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);

//     isRunningProcess = false;
// }