//
// Created by lotte on 27.02.20.
//

#include "Station.h"


Station::Station(const std::string &_Naam, const std::string &_Volgende, const std::string &_Vorige, int _Spoor)
        : _Naam(_Naam), _Volgende(_Volgende), _Vorige(_Vorige), _Spoor(_Spoor) {}

const std::string &Station::getNaam() const {
    return _Naam;
}

const std::string &Station::getVolgende() const {
    return _Volgende;
}

const std::string &Station::getVorige() const {
    return _Vorige;
}

int Station::getSpoor() const {
    return _Spoor[0];                               // momentarily this vector only consists of 1, so we return only 1
}
