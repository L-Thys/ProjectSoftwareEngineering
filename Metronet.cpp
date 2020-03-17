//
// Created by bas on 05/03/2020.
//

#include "Metronet.h"
#include <fstream>
#include <string>
#include <iostream>

const std::map<std::string, Station *> &Metronet::getStations() {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling getStations");
    return _stations;
}

const std::map<int, Tram *> &Metronet::getTrams() {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling getTrams");
    return _trams;
}

bool Metronet::addStation(Station *station) {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling addStation");
    return Metronet::_stations.insert(std::pair<std::string, Station*>(station->getNaam(), station)).second;
}

bool Metronet::addTram(Tram *tram) {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling addTram");
    return Metronet::_trams.insert(std::pair<int, Tram*>(tram->getLijn(), tram)).second;
}

bool Metronet::isConsistent() {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling isConsistent");
    // -- We check every station in our network -- //
    for (std::map<std::string, Station *>::iterator station = _stations.begin();
        station != _stations.end(); station++) {

        // ~ Spoor is automatically set on -1 to easily check if Spoor is changed or not ~ //
        if (station->second->getSpoor() == -1) {
            return false;
        }

        // ~ If the station has a valid Spoor, we check if the following and the previous Station also have this Spoor ~ //
        if(Metronet::findStation(station->second->getVolgende())==NULL
        or station->second->getSpoor() != Metronet::findStation(station->second->getVolgende())->getSpoor())
        {
            return false;       // we return false if the equality of the integers in the Spoor member is false
        }

        if(Metronet::findStation(station->second->getVorige())==NULL
        or station->second->getSpoor() != Metronet::findStation(station->second->getVorige())->getSpoor())
        {
            return false;       // idem
        }

        /* The input of a station is standard given with only 1 track for now, we thus have always no duplicates*/
        if (station->second->getSporen().empty()) return false;
    }
    // ------------------------------------------- //

    // -- We now check every tram inside _trams if they are initiated correctly -- //
    std::vector<int> as_tracks;             // to be used later on

    // tram is a pair <int Tram*>, we need to take tram.second to get the tram itself
    for (std::map<int, Tram *>::iterator tram = _trams.begin(); tram != _trams.end(); tram++) {

        // ~ Home is the start Station of our tram, we check if this station is a valid station in our network ~ //
        std::string home = tram->second->getStartStation();
        if (Metronet::_stations.find(home) == Metronet::_stations.end()) {
            return false;
        }

        // ~ We also check if the Spoor of the tram is equal to the Spoor that runs through its Start Station ~ //
        if (tram->second->getLijn() != Metronet::findStation(tram->second->getStartStation())->getSpoor()) {
            return false;
        }

        // ~ This part checks if each Spoor occurs exactly 1 time ~ //
            // we use the already initialised vector of int 'as_tracks' which stands for "already seen tracks"
        for (std::vector<int>::iterator it = as_tracks.begin(); it != as_tracks.end(); it++){

            // if the line is already is the as_tracks, it has been used so we can't use it again, we return false
            if (*it == tram->second->getLijn()){
                return false;
            }
            else {      // if the line is not present in the as_tracks
                        // we push it in so we ensure that duplicates are noticed
                as_tracks.push_back(tram->second->getLijn());
            }
        }

    }
    // --------------------------------------------------------------------------- //

    return true;
}

// if spoor isn't in the list, NULL is returned, so it's best to check if you get NULL from this function before using the returned value
Tram * Metronet::findTram(int spoor) {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling findTram");
    try {
        return Metronet::_trams.at(spoor);
    }
    catch(std::out_of_range& e){
        return NULL;
    }


}

// if name isn't in the list, NULL is returned, so it's best to check if you get NULL from this function before using the returned value
Station * Metronet::findStation(const std::string& name) {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling findStation");
    try {
        return Metronet::_stations.at(name);
    }
    catch(std::out_of_range& e){
        return NULL;
    }
}

Metronet::~Metronet() {
    for(std::map<int,Tram*>::iterator it=_trams.begin(); it!=_trams.end(); ++it){
        delete it->second;
    }
    for(std::map<std::string, Station*>::iterator it=_stations.begin(); it!=_stations.end(); ++it){
        delete it->second;
    }
    ENSURE (properlyDeleted(), "A destructor must end in a properlyDeleted state");
}

Metronet::Metronet() {
    _propInit = this;
    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");
}

bool Metronet::properlyInitialized() {
    return _propInit == this;
}

bool Metronet::properlyDeleted() {
    for(std::map<int,Tram*>::iterator it=_trams.begin(); it!=_trams.end(); ++it){
        if(it->second != NULL) return false;
    }
    for(std::map<std::string, Station*>::iterator it=_stations.begin(); it!=_stations.end(); ++it){
        if(it->second != NULL) return false;
    }
    return true;
}

void Metronet::writeToFile(const char *filename) {
    REQUIRE(mapsAreNotEmpty() && isConsistent(), "this object should contain a consistent metronet");
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling writeToFile");
    // Open uitvoerbestand
    std::ofstream file(filename);

    // WHILE Nog stations beschikbaar
    for (std::map<std::string,Station*>::iterator it = _stations.begin(); it != _stations.end(); ++it) {
        // Schrijf station-gegevens ui
        file << "Station " << it->second->getNaam() << std::endl;
        file << "<- Station " << it->second->getVorige() << std::endl;
        file << "-> Station " << it->second->getVolgende() << std::endl;
        file << "Spoor " << it->second->getSpoor() << std::endl;
    }

    file << std::endl;
    //WHILE Nog voertuigen beschikbaar
    for (std::map<int,Tram*>::iterator it = _trams.begin(); it != _trams.end() ; ++it) {
        // Schrijf voertuig-gegevens uit
        file << "Tram " << it->second->getLijn() << " in " << it->second->getCurrentStation();
        file << ", " << it->second->getSeats() << " zitplaatsen" << std::endl;
    }
    // Sluit uitvoerbestand
    file.close();
}

bool Metronet::mapsAreNotEmpty() {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling isConsistent");
    return !_trams.empty() && !_stations.empty();
}

bool Metronet::drive(const int _spoor, std::string &_station) {
    REQUIRE(properlyInitialized(), "Metronet was not initialized when calling drive");

    // we find the 2 corresponding objects
    Tram* cTram = findTram(_spoor);
    Station* cStation = findStation(_station);

    // we check if the needed tram its station is indeed the needed station
    if (cTram->getCurrentStation() == _station){                // if so, we move it
        std::string oSt = cTram->getCurrentStation();           // we shortly save the station
        cTram->setCurrentStation(cStation->getVolgende());      // we move the Tram
        std::string nSt = cTram->getCurrentStation();           // we save the new station

        // the message of movement is given by printing the track (also tram name), the start and finish station
        std::cout << "Tram " << _spoor << " drove from station " << oSt << " to station " << nSt << std::endl;
        return true;
    }
    else {                                                      // if not we give an error message
        std::cerr << "There is no Tram present on track " << _spoor << " in station " << _station << ". Give another instruction." << std::endl;
        return false;
    }
}

void Metronet::driveAutomaticaly(int n) {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling writeToFile");
    REQUIRE(mapsAreNotEmpty() && isConsistent(), "this object should contain a consistent metronet");
    for (int i = 0; i < n; ++i) {
        for (std::map<int,Tram*>::iterator it = _trams.begin(); it != _trams.end() ; ++it) {
            Station* station = findStation(it->second->getCurrentStation());
            drive(it->second->getLijn(), const_cast<std::string &>(station->getVolgende()));
        }
    }
}
