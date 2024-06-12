/*
    Author: Brack Harmon
    Date: 6/10/2024
 
 */



#include <iostream>
#include "loadbalancer.h"
// loadbalancer::loadbalancer(){

// }

void loadbalancer::fillQueue(int numServers){

    std::cout << "---- filling queue ----" << std::endl;
    for(int i = 0; i < numServers * 100; i++){
        request req;
        reqQueue.push(req);
    }

    std::cout << "Queue size: " << reqQueue.size();

}

