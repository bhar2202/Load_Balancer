/*
    Author: Brack Harmon
    Date: 6/10/2024
 
 */


class webserver{

    private:
        bool isRunningProcess = false;
        int serverID;


    public:
        webserver(int serverID);
        void startRequest(){isRunningProcess = true;}
        void processRequest();
        bool getStatus(){return isRunningProcess;}

};