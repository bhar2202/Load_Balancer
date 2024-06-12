/*
    Author: Brack Harmon
    Date: 6/10/2024
 
 */

#include <iostream>
#include <string>
#include <vector>
#include "request.h"

class RequestQueue{

    private:
        std::vector<request> queue;

    public:
        void push(request req){queue.push_back(req);};
        request pop();
        size_t size(){return queue.size();}


};