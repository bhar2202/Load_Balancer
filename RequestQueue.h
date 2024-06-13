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
        request pop(){
            request item;
            item = queue.at(0);
            queue.erase(queue.begin(),queue.begin()+1);
            return item;
        };
        size_t size(){return queue.size();}


};