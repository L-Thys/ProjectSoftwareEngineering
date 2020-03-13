//
// Created by lotte on 27.02.20.
//

#include "Station.h"


Station::Station(const std::string &_Naam, const std::string &_Volgende, const std::string &_Vorige, int _Spoor)
        : _Naam(_Naam), _Volgende(_Volgende), _Vorige(_Vorige) {
    Station::_Sporen.push_back(_Spoor);             // because we are not sure what happens if we write _Sporen(_Spoor)
}

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
    return _Sporen[0];                               // momentarily this vector only consists of 1, so we return only 1
}

std::vector<int> Station::getSporen() {
    return Station::_Sporen;
}

bool Station::operator==(const Station &rhs) const {
    return _Naam == rhs._Naam &&
           _Volgende == rhs._Volgende &&
           _Vorige == rhs._Vorige &&
           _Sporen == rhs._Sporen;
}

bool Station::operator!=(const Station &rhs) const {
    return !(rhs == *this);
}
