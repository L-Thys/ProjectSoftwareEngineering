//
// Created by bas on 27/02/2020.
//

#include "Tram.h"

Tram::Tram(const int fLijn, const int fSeats, const int fSpeed, std::string fStartStation) {
    Tram::fLijn = fLijn;
    Tram::fSeats = fSeats;
    Tram::fSpeed = fSpeed;
    Tram::fStartStation = fStartStation;
}