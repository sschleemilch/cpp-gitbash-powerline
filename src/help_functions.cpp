#include "help_functions.hpp"
#include <sstream>
#include <iostream>
std::string getCWDString(std::string cwd, std::string home) {
    std::string pathString = cwd;

    size_t start_pos = cwd.find(home);
    if(start_pos != std::string::npos) {
        pathString.replace(start_pos, home.length(), "~");
    }

    std::vector<std::string> pathSplit = split(pathString, '/');
    std::vector<std::string> pathShort;

    int pathSplitLength = pathSplit.size();

    if(pathSplitLength > 4) {
        pathShort.push_back(pathSplit[0]);
        pathShort.push_back("...");
        pathShort.push_back(pathSplit[pathSplitLength - 2]);
        pathShort.push_back(pathSplit[pathSplitLength - 1]);
        pathString = "";
        for(std::vector<int>::size_type i = 0; i != pathShort.size(); i++) {
            if (i == 0) {
                pathString += pathShort[i];
            } else {
                pathString += "/" + pathShort[i];
            }
        }
    }

    return " " + pathString;
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

