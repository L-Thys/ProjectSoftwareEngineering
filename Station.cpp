//
// Created by lotte on 27.02.20.
//

#include "Station.h"

const std::string &Station::getFNaam() const {
    return fNaam;
}

void Station::setFNaam(const std::string &fNaam) {
    Station::fNaam = fNaam;
}

Station *Station::getFVolgende() const {
    return fVolgende;
}

void Station::setFVolgende(Station *fVolgende) {
    Station::fVolgende = fVolgende;
}

Station *Station::getFVorige() const {
    return fVorige;
}

void Station::setFVorige(Station *fVorige) {
    Station::fVorige = fVorige;
}

int Station::getFSpoor() const {
    return fSpoor;
}

void Station::setFSpoor(int fSpoor) {
    Station::fSpoor = fSpoor;
}

Station::Station() {}
