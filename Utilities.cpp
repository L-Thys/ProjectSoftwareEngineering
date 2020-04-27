//
// Created by bas on 27/04/2020.
//

#include "Utilities.h"

bool findInVector (std::string s, std::vector<std::string>& gos) {
    for (std::vector<std::string>::iterator it = gos.begin(); it != gos.end(); ++it){
        if (s == *it) return true;
    }
    return false;
}

bool findInVector (int i, std::vector<int>& goi) {
    for (std::vector<int>::iterator it = goi.begin(); it != goi.end(); ++it){
        if (i == *it) return true;
    }
    return false;
}
