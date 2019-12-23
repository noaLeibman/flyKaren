//
// Created by hani on 21/12/2019.
//

#ifndef EX3_LEXER_H
#define EX3_LEXER_H

#endif //EX3_LEXER_H


#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class lexer {
private:
    std::vector<string> stringArray;
public:
    std::vector<string> getTokens();

    lexer(std::string fileName);

    ~lexer();
};

lexer::lexer(std::string fileName) {
    std::ifstream in_file;
    in_file.open(fileName);
    std::string textString;
    if (in_file.is_open()) {
        std::string str((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
        textString = str;
    }
    std::stringstream stringStream(textString);
    std::string line;
    while (std::getline(stringStream, line)) {
        unsigned treated =0;
        std::size_t prev = 0, pos;
        int strpos = line.find(" ");
        std::string tempLine = line;
        string input = line.substr(0, strpos);
        int strpos1 = line.find("(");
        string input1 = line.substr(0, strpos1);
        int strpos2 = line.find(" ");
        string input2=line.substr(0,strpos2);
        int strpos3 = line.find(" ");
        string input3=line.substr(0,strpos3);
        //while case
        if (input == "while") {
            treated==1;
            string tempWord ="while ";
            tempLine.replace(0,tempWord.length(),"");
            std::string chars = "{";
            for (char c:chars) {
                tempLine.erase(std::remove(tempLine.begin(), tempLine.end(), c), tempLine.end());
            }
            stringArray.push_back("while");
            stringArray.push_back(tempLine);
            stringArray.push_back("{");
            //print case
        } else if (input1 == "Print"&&treated==0) {
            treated==1;
            string tempWord = "Print ";
            tempLine.replace(0, tempWord.length(), "");
            std::string chars = ")\"";
            for (char c:chars) {
                tempLine.erase(std::remove(tempLine.begin(), tempLine.end(), c), tempLine.end());
            }
            stringArray.push_back("Print");
            stringArray.push_back(tempLine);
            // split everything by =
        }
        //"if" case
            else if(input2 == "if"&&treated==0){
            std::string chars = "{";
            for (char c:chars) {
                tempLine.erase(std::remove(tempLine.begin(), tempLine.end(), c), tempLine.end());
            }
            stringArray.push_back(tempLine);
            stringArray.push_back("{");
            }

            else if(strpos3!=std::string::npos&&treated==0&&input!="var"){
                std::stringstream ss(tempLine);
                std::string partString;
                unsigned i=0;
                while(std::getline(ss,partString,'=')){
                    i++;
                    std::string chars = " \t";
                    for (char c:chars) {
                        partString.erase(std::remove(partString.begin(), partString.end(), c), partString.end());
                    }
                    stringArray.push_back(partString);
                    if (i==1){
                        stringArray.push_back("=");
                    }
                }
            }
//normally separate by space ; , newline tab ( ) "
        else {
            while ((pos = line.find_first_of(" \";\n\t(),", prev)) != std::string::npos) {
                if (pos > prev) {
                    std::string chars = "\t ";
//                    for (char c:chars) {
//                        line.erase(std::remove(line.begin(), line.end(), c), line.end());
//                    }
                    stringArray.push_back(line.substr(prev, pos - prev));
                }
                prev = pos + 1;
            }
            if (prev < line.length()) {
                std::string chars = "\t ";
//                for (char c:chars) {
//                    line.erase(std::remove(line.begin(), line.end(), c), line.end());
//                }
                stringArray.push_back(line.substr(prev, std::string::npos));
            }
        }
    }
}


std::vector<string> lexer::getTokens() {
    //printing the vector
    for (int i = 0; i < stringArray.size(); i++) {
        cout << stringArray.at(i) << endl;
    }
    return stringArray;

};

lexer::~lexer() {}
