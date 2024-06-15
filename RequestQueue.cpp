/*!
 * \file RequestQueue.cpp
 * \brief Implementation of the Request queue class
 * \author Brack Harmon
 * \date 6/10/2024
 */

#include "RequestQueue.h"


void RequestQueue::push(request req){
    queue.push_back(req);
}

request RequestQueue::pop(){
    request item;
    item = queue.at(0);
    queue.erase(queue.begin(),queue.begin()+1);
    return item;
};

size_t RequestQueue::size(){
    return queue.size();
}