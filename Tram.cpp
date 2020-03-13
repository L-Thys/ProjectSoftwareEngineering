//
// Created by bas on 27/02/2020.
//

#include "Tram.h"
#include "DesignByContract.h"

Tram::Tram(const int _Lijn, const int _Seats, const int _Speed, std::string _StartStation) {
    Tram::_Lijn = _Lijn;
    Tram::_Seats = _Seats;
    Tram::_Speed = _Speed;
    Tram::_StartStation = _StartStation;
}

const int Tram::getLijn() const {
    return _Lijn;
}

const int Tram::getSeats() const {
    return _Seats;
}

const int Tram::getSpeed() const {
    return _Speed;
}

const std::string &Tram::getStartStation() const {
    return _StartStation;
}

bool Tram::operator==(const Tram &rhs) const {
    return _Lijn == rhs._Lijn &&
           _Seats == rhs._Seats &&
           _Speed == rhs._Speed &&
           _StartStation == rhs._StartStation;
}

bool Tram::operator!=(const Tram &rhs) const {
    return !(rhs == *this);
}
