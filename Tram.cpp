//
// Created by bas on 27/02/2020.
//

#include "Tram.h"

Tram::Tram(const int _Lijn, const int _Seats, const int _Speed, std::string _StartStation) {
    Tram::_Lijn = _Lijn;
    Tram::_Seats = _Seats;
    Tram::_Speed = _Speed;
    Tram::_StartStation = _StartStation;
}

int Tram::getLijn() const {
    return _Lijn;
}

int Tram::getSeats() const {
    return _Seats;
}

int Tram::getSpeed() const {
    return _Speed;
}

const std::string &Tram::getStartStation() const {
    return _StartStation;
}
