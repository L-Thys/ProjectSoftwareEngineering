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

    Tram::_propInit = this;
    // We make sure that the object is properly initialized by using the ENSURE function
    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");

    ENSURE(validTramMembers(),"The parameter _StartStation must be a valid string");
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

bool Tram::properlyInitialized() {
    return _propInit == this;
}

bool Tram::validTramMembers() {
    return is_valid_String(_StartStation);
}
