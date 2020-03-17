//
// Created by lotte on 27.02.20.
//

#include "Station.h"


Station::Station(const std::string &_Naam, const std::string &_Volgende, const std::string &_Vorige, int _Spoor)
        : _Naam(_Naam), _Volgende(_Volgende), _Vorige(_Vorige) {
    Station::_Sporen.push_back(_Spoor);             // because we are not sure what happens if we write _Sporen(_Spoor)
    Station::_propInit = this;

    // We make sure that the object is properly initialized by using the ENSURE function
    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");
    validStationMembers();
}

const std::string & Station::getNaam() {
    // we need to have a correctly initialized object
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getNaam");

    // we ensure that the name is a correct string
    ENSURE(is_valid_String(_Naam), "getNaam must return a valid string");
    return _Naam;
}

const std::string &Station::getVolgende() {
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getVolgende");
    ENSURE(is_valid_String(_Volgende), "getVolgende must return a valid string");
    return _Volgende;
}

const std::string &Station::getVorige() {
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getVorige");
    ENSURE(is_valid_String(_Vorige), "getVorige must return a valid string");
    return _Vorige;
}

int Station::getSpoor() {
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getSpoor");
    return _Sporen[0];                               // momentarily this vector only consists of 1, so we return only 1
}

std::vector<int> Station::getSporen() {
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getSporen");
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

bool Station::properlyInitialized() {
    return _propInit == this;
}

void Station::validStationMembers() {
    // we ensure that all the members are valid
    ENSURE(is_valid_String(_Naam), "A station has to have a name consisting of a-z, A-Z");
    ENSURE(is_valid_String(_Volgende), "A station's next station should be a valid name");
    ENSURE(is_valid_String(_Vorige), "A station's previous station should be a valid name");

    // the tracks in _Sporen are always valid integers, otherwise the compiler will give an error
}


