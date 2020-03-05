//
// Created by lotte on 27.02.20.
//

#ifndef PSE_STATION_H
#define PSE_STATION_H

#include "string"

class Station {
public:
    /**
     * @brief Constructor van een station, de parameters worden members
     *
     * @param _Naam : een string dat de naam van dit station zal zijn
     * @param _Volgende : een string dat de naam van het volgende station voorstelt
     * @param _Vorige : een string dat de naam van het vorige station voorstelt
     * @param _Spoor : een integer dat aangeeft welk spoor hierdoor loopt
     * */
    Station(const std::string &_Naam, const std::string &_Volgende, const std::string &_Vorige, int _Spoor);

private:
    std::string _Naam;
    std::string _Volgende;
    std::string _Vorige;
    int _Spoor;
};


#endif //PSE_STATION_H
