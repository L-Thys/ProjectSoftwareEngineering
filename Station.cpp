//
// Created by lotte on 27.02.20.
//

#include "Station.h"

Station::Station(const std::string name){
    Station::_Naam = name;                // the name is set on the empty string
    std::vector<int> null;              // a empty vector is made
    Station::_Sporen = null;            // we associate the empty vector with the tracks of the station
    Station::_propInit = this;

    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");
}


Station::Station(const std::string &_Naam, std::map<int,Station*> &_Volgende, std::map<int,Station*> &_Vorige,
        int _Spoor, std::string _Type)
        : _Naam(_Naam), _Volgende(_Volgende), _Vorige(_Vorige), _Type(_Type) {
    REQUIRE(is_valid_station_type(_Type),"the variable \"_Type\" has to be a valid station type");
    Station::_Sporen.push_back(_Spoor);             // because we are not sure what happens if we write _Sporen(_Spoor)
    Station::_propInit = this;

    // We make sure that the object is properly initialized by using the ENSURE function
    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");
    validStationMembers();
}

const std::string & Station::getNaam() const{
    // we need to have a correctly initialized object
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getNaam");

    // we ensure that the name is a correct string
    ENSURE(is_valid_String(_Naam), "getNaam must return a valid string");
    return _Naam;
}
Station* Station::getVolgende(int x) const {
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getVolgende");
    Station* vld = findStationInNext(x);
    ENSURE(is_valid_String(vld->getNaam()), "getVolgende must return a valid Station");
    return vld;
}

Station* Station::getVorige(int x) const {
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getVorige");
    Station* vrg = findStationInNext(x);
    ENSURE(is_valid_String(vrg->getNaam()), "getVorige must return a valid Station");
    return vrg;
}

int Station::getSpoor() const{
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getSpoor");
    return _Sporen[0];      // momentarily this vector only consists of 1, so we return only 1
}

std::vector<int> Station::getSporen() {
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getSporen");
    return Station::_Sporen;
}


bool Station::properlyInitialized() const{
    return _propInit == this;
}

void Station::validStationMembers() {
    // we ensure that all the members are valid
    ENSURE(is_valid_String(_Naam), "A station has to have a name consisting of a-z, A-Z");


    // the tracks in _Sporen are always valid integers, otherwise the compiler will give an error
}

void Station::setVolgende(int x, Station *volgende) {
    REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling Station");
    _Volgende[x] = volgende;
    ENSURE(getVolgende(x)==volgende, "_Volgende should be equal to param volgende");
}

void Station::setVorige(int x, Station *vorige) {
    REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling setVorige");
    _Vorige[x] = vorige;
    ENSURE(getVorige(x)==vorige, "_Vorige should be equal to param vorige");
}

void Station::setSporen(const std::vector<int> &sporen) {
    REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling setSporen");
    _Sporen = sporen;
    ENSURE(getSporen()==sporen, "_Sporen should be equal to param sporen");
}

const std::string &Station::getType() const {
    return _Type;
}

void Station::setType(const std::string &type) {
    _Type = type;
}

bool Station::moveTramFrom(Tram *tram) {
    for(std::vector<Tram *>::iterator it = _Trams.begin(); it != _Trams.end(); it++){
        if(*it == tram){
            _Trams.erase(it);
            return true;
        }
    }
    return false;
}

void Station::moveTramTo(Tram *tram) {
    _Trams.push_back(tram);
}

bool Station::isInStation(Tram *tram) {
    for(std::vector<Tram *>::iterator it = _Trams.begin(); it != _Trams.end(); it++){
        if(*it == tram){
            return true;
        }
    }
    return false;
}

bool Station::isInStation(int a) {
    for(std::vector<Tram *>::iterator it = _Trams.begin(); it != _Trams.end(); it++){
        if((*it)->getLijn() == a){
            return true;
        }
    }
    return false;
}

Station * Station::findStationInNext(int x) const {
    for (std::map<int,Station*>::const_iterator it = _Volgende.begin(); it != _Volgende.end(); ++it){
        if (it->first == x) return it->second;
    }
    return NULL;
}

Station * Station::findStationInPrev(int x) const {
    for (std::map<int,Station*>::const_iterator it = _Vorige.begin(); it != _Vorige.end(); ++it){
        if (it->first == x) return it->second;
    }
    return NULL;
}

void Station::addSpoor(int spoor) {
    _Sporen.push_back(spoor);
}

//---------------------------------//
//// Tests

class ValidStationTest: public ::testing::Test {
public:
    ValidStationTest() {
        station = new Station("A",stationB,stationC,12,"Halte");
        stationB = new Station("B",stationC,station,12,"Halte");
        stationC = new Station("C",station, stationB,12,"Halte");
    }

    void SetUp() {
        // code here will execute just before the test ensues
    }

    void TearDown() {
        delete station;
    }

    Station* station;
    Station* stationB;
    Station* stationC;

};


// tests getter functions from Station
TEST_F(ValidStationTest, getters){
    EXPECT_EQ("A",station->getNaam());
    EXPECT_EQ("B",station->getVolgende());
    EXPECT_EQ("C",station->getVorige());
    EXPECT_EQ(12,station->getSpoor());
    std::vector<int> testsporen;
    testsporen.push_back(12);
    EXPECT_EQ(testsporen, station->getSporen());

}

// tests properlyInitialized in metronet
TEST_F(ValidStationTest, properlyInitialized){
    EXPECT_TRUE(station->properlyInitialized());
}
