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

    // we bekijken elk station in ons network
    for (std::map<std::string, Station *>::iterator station = _stations.begin();
        station != _stations.end(); station++) {

        // we checken of de standaard waarde van een spoor is aangepast of niet
        if (station->second->getSpoor() == -1) {
            return false;
        }

        // we checken of de vorige of volgende van een station hetzelfde spoor heeft
        else if (station->second->getSpoor() != Metronet::findStation(station->second->getVolgende())->getSpoor()){
            return false;
        }
        else if (station->second->getSpoor() != Metronet::findStation(station->second->getVorige())->getSpoor()){
            return false;
        }
    }

    for (std::map<int, Tram *>::iterator tram = _trams.begin(); tram != _trams.end(); tram++){
        if (tram->second->getLijn() != Metronet::findStation(tram->second->getStartStation())->getSpoor()){
            return false;
        }

        // we zoeken het homestation in het network
        std::string home = tram->second->getStartStation();
        if (Metronet::_stations.find(home) == Metronet::_stations.end()){
            return false;
        }

    }

// TODO : • elk spoor heeft exact 1 tram.

    return true;
}

Tram * Metronet::findTram(int spoor) {
    return Metronet::_trams[spoor];
}

Station * Metronet::findStation(std::string name) {
    return Metronet::_stations[name];
}

