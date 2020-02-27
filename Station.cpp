//
// Created by lotte on 27.02.20.
//

#include "Station.h"


Station::Station() {}

const std::string &Station::getFNaam() const {
    return fNaam;
}

void Station::setFNaam(const std::string &fNaam) {
    Station::fNaam = fNaam;
}

const std::string &Station::getFVolgende() const {
    return fVolgende;
}

void Station::setFVolgende(const std::string &fVolgende) {
    Station::fVolgende = fVolgende;
}

const std::string &Station::getFVorige() const {
    return fVorige;
}

void Station::setFVorige(const std::string &fVorige) {
    Station::fVorige = fVorige;
}

int Station::getFSpoor() const {
    return fSpoor;
}

void Station::setFSpoor(int fSpoor) {
    Station::fSpoor = fSpoor;
}
