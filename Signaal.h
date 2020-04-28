//
// Created by lotte on 27.04.20.
//

#ifndef PSE_SIGNAAL_H
#define PSE_SIGNAAL_H


#include "library.h"
#include "Station.h"

class Signaal {
public:
    Signaal(int spoor, int limiet, const std::string &type, Station *vorige, Station *volgende);

    Signaal(int spoor, const std::string &type, Station *vorige, Station *volgende);

    int getLimiet() const;

    const std::string &getType() const;

private:
    int spoor;
    int limiet;
    std::string type;
    Station* vorige;
    Station* volgende;
};


#endif //PSE_SIGNAAL_H
