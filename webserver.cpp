/*!
 * \file webserver.cpp
 * \brief Implementation of the webserver class
 * \author Brack Harmon
 * \date 6/10/2024
 */

#include "webserver.h"

/*!
 * \brief webserver constructor
 * \param id id number of server
 */
webserver::webserver(int id){
    serverID = id;
}

/*!
 * \brief tells the server to start handling requst
 */
void webserver::startRequest(){
    isRunningProcess = true;
}  

/*!
 * \brief server reports being done with process
 */
void webserver::endProcess(){
    isRunningProcess = false;
}

/*!
 * \brief returns if the server is currently running a process or not
 */
bool webserver::getStatus(){return isRunningProcess;}

/*!
 * \brief returns the ip address of the request that is currently being processed
 */
std::string webserver::getReqIP(){return ipProcessing;}

/*!
 * \brief returns the id of this specific server
 */
int webserver::getServerID(){return serverID;}

/*!
 * \brief sets the ip currently being processed
 */
void webserver::setReqIP(std::string ip){
    ipProcessing = ip;
}