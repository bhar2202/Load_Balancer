/*
    Author: Brack Harmon
    Date: 6/10/2024
 
 */

#include <iostream>
#include <string>
#include <vector>

struct request {

    std::string method;
    std::string url;
    std::string protocol;
    std::string header;

};

class queue{

    private:
        std::vector<request> queue;

    public:
        void push(request req);
        request pop();


};