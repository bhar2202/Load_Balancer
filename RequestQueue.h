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

class RequestQueue{

    private:
        

    public:
        std::vector<request> queue;
        void push(request req);
        request pop();
        size_t size();


};