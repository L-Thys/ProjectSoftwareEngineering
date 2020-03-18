//
// Created by bas on 13/03/2020.
//

#include "library.h"


bool is_valid_String(const std::string& s){
    std::string::const_iterator it = s.begin();     // it is the start of the string

    // check on ascii value
    while (it != s.end() && ((*it >= 97 && *it <= 122) || (*it >= 65 && *it <= 90))) ++it;
    return !s.empty() && it == s.end();
}


bool is_Integer(const std::string& s){
    std::string::const_iterator it = s.begin();

    // we check if this char could be an integer
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}