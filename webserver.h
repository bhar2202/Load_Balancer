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

/*!
 * \brief simulates functions of a webserver that processes requests
 */
class webserver{

    private:
        bool isRunningProcess = false;
        int serverID;
        std::string ipProcessing;

    public:
        webserver(int id);
        void startRequest(); 
        void endProcess();
        bool getStatus();
        std::string getReqIP();
        int getServerID();

};