// Created by hani on 23/12/2019.
//
#include <iostream>
#include "lexer.h"
#include <algorithm>

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
        unsigned treated = 0;
        std::size_t prev = 0, pos;
        int strpos = line.find(" ");
        std::string tempLine = line;
        string input = line.substr(0, strpos);
        int strpos1 = line.find("(");
        string input1 = line.substr(0, strpos1);
        int strpos2 = line.find(" ");
        string input2 = line.substr(0, strpos2);
        int strpos3 = line.find(" ");
        int strpos10 = line.find("\t");
        string input3 = line.substr(0, strpos3);
        int strpos4 = line.find("->");
        string input4 = line.substr(0, strpos4);
        int strpos5 = line.find("<-");
        string input5 = line.substr(0, strpos5);
        //while case
        //This section deals with a line that starts with a while, and separates the condition
        if (input == "while") {
            treated = 1;
            string tempWord = "while ";
            tempLine.replace(0, tempWord.length(), "");
            std::string chars = "{";
            for (char c:chars) {
                tempLine.erase(std::remove(tempLine.begin(), tempLine.end(), c), tempLine.end());
            }
            stringArray.push_back("while");
            int startIndex = 0;
            int endIndex = 0;
            unsigned treatedMoreEqual = 0;
            while ((endIndex = tempLine.find(">=", startIndex)) < tempLine.size()) {
                treatedMoreEqual = 1;
                std::string partOne = tempLine.substr(startIndex, endIndex - startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
                stringArray.push_back(">=");
                startIndex = endIndex + 2;
            }
            if (startIndex < tempLine.size() && treatedMoreEqual == 1) {
                std::string partOne = tempLine.substr(startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
            }
            unsigned treatedLessEqual = 0;
            while ((endIndex = tempLine.find("<=", startIndex)) < tempLine.size()) {
                treatedLessEqual = 1;
                std::string partOne = tempLine.substr(startIndex, endIndex - startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
                stringArray.push_back("<=");
                startIndex = endIndex + 2;
            }

            if (startIndex < tempLine.size() && treatedLessEqual == 1) {
                std::string partOne = tempLine.substr(startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
            }
            unsigned treatedEqual = 0;
            while ((endIndex = tempLine.find("==", startIndex)) < tempLine.size()) {
                treatedEqual = 1;
                std::string partOne = tempLine.substr(startIndex, endIndex - startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
                stringArray.push_back("==");
                startIndex = endIndex + 2;
            }

            if (startIndex < tempLine.size() && treatedEqual == 1) {
                std::string partOne = tempLine.substr(startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
            }
            unsigned treatedUnequal = 0;
            while ((endIndex = tempLine.find("!=", startIndex)) < tempLine.size()) {
                treatedUnequal = 1;
                std::string partOne = tempLine.substr(startIndex, endIndex - startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
                stringArray.push_back("!=");
                startIndex = endIndex + 2;
            }

            if (startIndex < tempLine.size() && treatedUnequal) {
                std::string partOne = tempLine.substr(startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
            }
            unsigned treatedLess = 0;
            while ((endIndex = tempLine.find("<", startIndex)) < tempLine.size()) {
                treatedLess = 1;
                std::string partOne = tempLine.substr(startIndex, endIndex - startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
                stringArray.push_back("<");
                startIndex = endIndex + 2;
            }

            if (startIndex < tempLine.size() && treatedLess == 1) {

                std::string partOne = tempLine.substr(startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
            }
            unsigned treatedMore = 0;
            while ((endIndex = tempLine.find(">", startIndex)) < tempLine.size()) {
                treatedMore = 1;
                std::string partOne = tempLine.substr(startIndex, endIndex - startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
                stringArray.push_back(">");
                startIndex = endIndex + 2;
            }

            if (startIndex < tempLine.size() && treatedMore == 1) {
                std::string partOne = tempLine.substr(startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
            }
            stringArray.push_back("{");
            //This section deals with finding if the line is a Print line, and whether it's a string or a value
            //keeping the quotation marks if it's a string.
        } else if (line.find("Print") != std::string::npos && treated == 0) {
            treated = 1;
            if (line.find("\"") != std::string::npos) {
                std::stringstream quotationStream(tempLine);
                std::string quotation;
                int index1 = 0;
                while (std::getline(quotationStream, quotation, '"')) {
                    index1++;
                    if (index1 == 2) {
                        stringArray.push_back("Print");
                        stringArray.push_back("\"" + quotation + "\"");
                    }
                }
            } else {
                std::string chars = " \t)";
                for (char c:chars) {
                    tempLine.erase(std::remove(tempLine.begin(), tempLine.end(), c), tempLine.end());
                }
                string tempWord = "Print ";
                tempLine.replace(0, tempWord.length(), "");
                stringArray.push_back("Print");
                stringArray.push_back(tempLine);
            }
            //This section finds if the line is a Sleep line and separates the command from the value to sleep.
        } else if (line.find("Sleep") != std::string::npos && treated == 0) {
            treated = 1;
            std::string chars = " \t)";
            for (char c:chars) {
                tempLine.erase(std::remove(tempLine.begin(), tempLine.end(), c), tempLine.end());
            }
            string tempWord = "Sleep ";
            tempLine.replace(0, tempWord.length(), "");
            stringArray.push_back("Sleep");
            stringArray.push_back(tempLine);
        }
        //This section finds if the line starts with an If and separates the condition.
        else if (input2 == "if" && treated == 0) {
            treated = 1;
            string tempWord = "if ";
            tempLine.replace(0, tempWord.length(), "");
            std::string chars = "{";
            for (char c:chars) {
                tempLine.erase(std::remove(tempLine.begin(), tempLine.end(), c), tempLine.end());
            }
            stringArray.push_back("if");
            int startIndex = 0;
            int endIndex = 0;
            unsigned treatedMoreEqual = 0;
            while ((endIndex = tempLine.find(">=", startIndex)) < tempLine.size()) {
                treatedMoreEqual = 1;
                std::string partOne = tempLine.substr(startIndex, endIndex - startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
                stringArray.push_back(">=");
                startIndex = endIndex + 2;
            }
            if (startIndex < tempLine.size() && treatedMoreEqual == 1) {
                std::string partOne = tempLine.substr(startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
            }
            unsigned treatedLessEqual = 0;
            while ((endIndex = tempLine.find("<=", startIndex)) < tempLine.size()) {
                treatedLessEqual = 1;
                std::string partOne = tempLine.substr(startIndex, endIndex - startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
                stringArray.push_back("<=");
                startIndex = endIndex + 2;
            }

            if (startIndex < tempLine.size() && treatedLessEqual == 1) {
                std::string partOne = tempLine.substr(startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
            }
            unsigned treatedEqual = 0;
            while ((endIndex = tempLine.find("==", startIndex)) < tempLine.size()) {
                treatedEqual = 1;
                std::string partOne = tempLine.substr(startIndex, endIndex - startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
                stringArray.push_back("==");
                startIndex = endIndex + 2;
            }

            if (startIndex < tempLine.size() && treatedEqual == 1) {
                std::string partOne = tempLine.substr(startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
            }
            unsigned treatedUnequal = 0;
            while ((endIndex = tempLine.find("!=", startIndex)) < tempLine.size()) {
                treatedUnequal = 1;
                std::string partOne = tempLine.substr(startIndex, endIndex - startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
                stringArray.push_back("!=");
                startIndex = endIndex + 2;
            }

            if (startIndex < tempLine.size() && treatedUnequal) {
                std::string partOne = tempLine.substr(startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
            }
            unsigned treatedLess = 0;
            while ((endIndex = tempLine.find("<", startIndex)) < tempLine.size()) {
                treatedLess = 1;
                std::string partOne = tempLine.substr(startIndex, endIndex - startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
                stringArray.push_back("<");
                startIndex = endIndex + 2;
            }

            if (startIndex < tempLine.size() && treatedLess == 1) {

                std::string partOne = tempLine.substr(startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
            }
            unsigned treatedMore = 0;
            while ((endIndex = tempLine.find(">", startIndex)) < tempLine.size()) {
                treatedMore = 1;
                std::string partOne = tempLine.substr(startIndex, endIndex - startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
                stringArray.push_back(">");
                startIndex = endIndex + 2;
            }

            if (startIndex < tempLine.size() && treatedMore == 1) {
                std::string partOne = tempLine.substr(startIndex);
                std::string chars = " ";
                for (char c:chars) {
                    partOne.erase(std::remove(partOne.begin(), partOne.end(), c), partOne.end());
                }
                stringArray.push_back(partOne);
            }

            stringArray.push_back("{");;
        } else if ((strpos4 != std::string::npos || strpos5 != std::string::npos) && treated == 0) {
            treated = 1;
            std::stringstream ss(tempLine);
            std::string partString;
            unsigned i = 0;
            while (std::getline(ss, partString, ' ')) {
                i++;
                std::string chars = "()";
                for (char c:chars) {
                    partString.erase(std::remove(partString.begin(), partString.end(), c), partString.end());
                }
                if (i == 4) {
                    string tempWord = "sim";
                    partString.replace(0, tempWord.length(), "");
                }
                stringArray.push_back(partString);
            }
            //separates any other line, like variable assignment.
        } else if ((strpos3 != std::string::npos && treated == 0 || strpos10 != std::string::npos) && input != "var") {
            treated = 1;
            std::stringstream ss(tempLine);
            std::string partString;
            unsigned i = 0;
            while (std::getline(ss, partString, '=')) {
                i++;
                std::string chars = " \t";
                for (char c:chars) {
                    partString.erase(std::remove(partString.begin(), partString.end(), c), partString.end());
                }
                stringArray.push_back(partString);
                if (i == 1) {
                    stringArray.push_back("=");
                }
            }
        }
      //normally separate by space ; , newline tab ( ) "
        else {
            while ((pos = line.find_first_of(" \";\n\t(),", prev)) != std::string::npos) {
                if (pos > prev) {
                    std::string chars = "\t ";
                    stringArray.push_back(line.substr(prev, pos - prev));
                }
                prev = pos + 1;
            }
            if (prev < line.length()) {
                std::string chars = "\t ";
                stringArray.push_back(line.substr(prev, std::string::npos));
            }
        }
    }
}


std::vector<string> lexer::getTokens() {
    for (int i = 0; i < stringArray.size(); i++) {
        cout << stringArray.at(i) +" "+to_string(i)<< endl;

    }
    return stringArray;
}

lexer::~lexer() {}
