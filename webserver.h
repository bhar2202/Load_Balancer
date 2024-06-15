/*!
 * \file webserver.h
 * \brief header file for the webserver class
 * \author Brack Harmon
 * \date 6/10/2024
 */

#include <ctime>
#include <sstream>
#include <chrono>
#include <iostream>
#include <thread>
#include <fstream>

class webserver{

    private:
        bool isRunningProcess = false;
        int serverID;
        std::string ipProcessing;

    public:
        webserver(int id);
        void startRequest(std::string ip){isRunningProcess = true; ipProcessing = ip;}    
        void endProcess(){isRunningProcess = false;}
        bool getStatus(){return isRunningProcess;}
        std::string getReqIP(){return ipProcessing;}
        int getServerID(){return serverID;}

};