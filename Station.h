//
// Created by lotte on 27.02.20.
//

#ifndef PSE_STATION_H
#define PSE_STATION_H

#include "string"

class Station {
private:
    std::string fNaam;
    std::string fVolgende;
    std::string fVorige;
    int fSpoor;

public:
    Station(const std::string &fNaam, const std::string &fVolgende, const std::string &fVorige, int fSpoor);

};


#endif //PSE_STATION_H
