//
// Created by bas on 05/03/2020.
//

#include "Spoor.h"

Spoor::Spoor(int _track) : _track(_track) {}

Spoor::Spoor(int _track, Tram *tram) : _track(_track) {
    Spoor::_trams.push_back(tram);
}

Spoor::Spoor(int _track, Station *station) : _track(_track) {
    Spoor::_stations.push_back(station);
}
