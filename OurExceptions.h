//
// Created by lotte on 05.03.20.
//

#ifndef PSE_OUREXCEPTIONS_H
#define PSE_OUREXCEPTIONS_H


#include <bits/exception.h>

class ongeldige_informatie: public std::exception{
public:
    virtual const char* what() const throw(){
        return "ongeldige informatie";
    }
};


#endif //PSE_OUREXCEPTIONS_H
