//
// Created by bas on 05/03/2020.
//

#include "Metronet.h"

const std::map<std::string, Station *> &Metronet::getStations() const {
    return _stations;
}

const std::map<int, Tram *> &Metronet::getTrams() const {
    return _trams;
}

void Metronet::addStation(Station *station) {
    Metronet::_stations.insert(std::pair<std::string, Station*>(station->getNaam(), station));
}

void Metronet::addTram(Tram *tram) {
    Metronet::_trams.insert(std::pair<int, Tram*>(tram->getLijn(), tram));
}

bool Metronet::isConsistent() {
    try {
        for (std::map<std::string, Station *>::iterator station = _stations.begin();
             station != _stations.end(); station++) {
            if (station->second->getSpoor() == 0) {
                throw
            }
        }
    }
    catch(){

    }
}


