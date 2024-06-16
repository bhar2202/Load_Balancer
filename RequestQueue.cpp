/*!
 * \file RequestQueue.cpp
 * \brief Implementation of the Request queue class
 * \author Brack Harmon
 * \date 6/10/2024
 */

#include "RequestQueue.h"

/*!
 * \brief pushes a request onto the queue
 * \param req request pushed
 */
void RequestQueue::push(request req){
    queue.push_back(req);
}

/*!
 * \brief pops a request off the front of the queue
 * \param req request popped
 */
request RequestQueue::pop(){
    request item;
    item = queue.at(0);
    queue.erase(queue.begin(),queue.begin()+1);
    return item;
};

/*!
 * \brief returns the number of requests in the queue
 */
size_t RequestQueue::size(){
    return queue.size();
}