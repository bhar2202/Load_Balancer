/*!
 * \file RequestQueue.h
 * \brief header file for the request queue class
 * \author Brack Harmon
 * \date 6/10/2024
 */

#include <iostream>
#include <string>
#include <vector>
#include "request.h"

/*!
 * \brief functions for handling a queue structure of requests
 */
class RequestQueue{

    private:
        std::vector<request> queue;

    public:
        void push(request req);
        request pop();
        size_t size();


};