//
// Created by hani on 23/12/2019.
//


#include <sstream>
#include "OpenServerCommand.h"
#include <algorithm>
#include <unordered_map>


OpenServerCommand::~OpenServerCommand() = default;

int OpenServerCommand::execute(int i) {
    std::vector<string> tokens = MapHolder::getMapHolder()->getTokens();

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        cerr << "Could not create a socket" << endl;
        return -1;
    }
//    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    Interpreter *interpreter = new Interpreter();
    interpreter->setVarMap(SetVariables::getSetVariables()->getVarMap());
    Expression *ex1 = interpreter->interpret(tokens[i+1]);
    try {
        address.sin_port = htons(ex1->calculate());
    }
    catch (exception e) {
        cout << "stoi error" << endl;
    }
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }
    if (listen(socketfd, 5) == -1) {
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    }
    client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);

    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }
    close(socketfd);
  //The thread opening
    thread serverThread;
    OpenServerCommand *tmp = new OpenServerCommand();
    serverThread = std::thread(&OpenServerCommand::ReadFromSim, this);
    serverThread.detach();
    return 2;
}

//This is the function sent to the thread, responsible for reading data from the simulator and updating
//the data in the maps.
void OpenServerCommand::ReadFromSim() {
    mutex mutex_lock;
  //getStopProgram is a flag that tells the thread when to stop;
    while (!MapHolder::getMapHolder()->getStopProgram()) {
        char buffer[1024] = {0};
        vector<double> double_Vector;
        int valread = read(client_socket, buffer, 1024);
        std::string bufferString(buffer);
        std::stringstream bufferStream(bufferString);
        std::string partString;
        int indexOfN = 0;
        while (std::getline(bufferStream, partString, '\n')) {
            if (indexOfN == 1) {
                std::stringstream firstNStream(partString);
                std::string partString1;
                std::getline(firstNStream, partString1, '\n');
                std::string chars = " \t\r\n";
                for (char ch:chars) {
                    partString.erase(std::remove(partString.begin(), partString1.end(), ch), partString.end());
                }
                std::stringstream workingStream(partString1);
                std::string partStringOne;
                while (std::getline(workingStream, partStringOne, ',')) {
                    double_Vector.push_back(stod(partStringOne));
                }
            }
            indexOfN++;
            if (indexOfN >= 2) {
                cout << "break" << endl;
                break;
            }

        }
        if (indexOfN == 1) {
            std::string oneN;
            std::string chars = " \t\r\n";
            for (char ch:chars) {
                bufferString.erase(std::remove(bufferString.begin(), bufferString.end(), ch), bufferString.end());
            }
            std::stringstream workingStream(bufferString);
            std::string partStringOne;
            while (std::getline(workingStream, partStringOne, ',')) {
                double_Vector.push_back(stod(partStringOne));
            }
        }
        //map updating
        //critical section
        mutex_lock.lock();
        auto it = VarsToUpdate::getVarsToUpdate()->getBeginMap();
        for (it = VarsToUpdate::getVarsToUpdate()->getBeginMap();
             it != VarsToUpdate::getVarsToUpdate()->getEndMap(); it++) {
            Var *currVar = it->second;
            int curr_index = it->first;
            currVar->setValue(double_Vector[curr_index]);
        }
        mutex_lock.unlock();
    }
}