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
                 std::vector<int> _Sporen, StationType _Type)
        : _Naam(_Naam), _Volgende(_Volgende), _Vorige(_Vorige), _Type(_Type) {
    //REQUIRE(is_valid_station_type(_Type),"the variable \"_Type\" has to be a valid station type");
    Station::_Sporen= _Sporen;             // because we are not sure what happens if we write _Sporen(_Spoor)
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
    Station* result = NULL;
    for (std::map<int,Station*>::const_iterator it = _Volgende.begin(); it != _Volgende.end(); ++it){
        if (it->first == x) result =it->second;
    }

    return result;
}

Station* Station::getVorige(int x) const {
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getVorige");
    Station* result= NULL;
    for (std::map<int,Station*>::const_iterator it = _Vorige.begin(); it != _Vorige.end(); ++it){
        if (it->first == x) result= it->second;
    }

    return result;
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

const StationType &Station::getType() const {
    REQUIRE(properlyInitialized(), "Station was not properly or not initialized before calling getSpoor");
    return _Type;
}

void Station::setType(const StationType &type) {
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getStartStation");
    _Type = type;
    ENSURE(getType()==type, "member _Type should be equal to param type after calling setType");
}

bool Station::removeTram(Tram *tram) {
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling removeTram");
    bool result = false;
    for(std::vector<Tram *>::iterator it = _Trams.begin(); it < _Trams.end(); it++){
        if(*it == tram){
            _Trams.erase(it);
            result = true;
        }
    }
    ENSURE(!findTram(tram), "param tram should not be in _Trams after calling removeTrams");
    return result;
}

void Station::addTram(Tram *tram) {
    REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling addTram");
    _Trams.push_back(tram);
    ENSURE(findTram(tram), "param tram should be in _Trams after calling addTram");
}

bool Station::findTram(Tram *tram) {
    REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling findTram");
    for(std::vector<Tram *>::iterator it = _Trams.begin(); it != _Trams.end(); it++){
        if(*it == tram){
            return true;
        }
    }
    return false;
}

bool Station::findTram(int a) {
    REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling findTram");
    for(std::vector<Tram *>::iterator it = _Trams.begin(); it != _Trams.end(); it++){
        if((*it)->getLijn() == a){
            return true;
        }
    }
    return false;
}

void Station::addSpoor(int spoor) {
    REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling setSporen");
    _Sporen.push_back(spoor);
    ENSURE(findInVector(spoor,_Sporen), "param spoor should be in _Sporen after calling addSpoor");
}

void Station::addSignaal(int spoor, Signaal *signaal) {
    REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling addTram");
    _Signalen[spoor]=signaal;
    ENSURE(getSignaal(spoor)==signaal, "param signaal should be in _Signalen on track spoor after calling addSignaal");
}

Signaal *Station::getSignaal(int spoor) const {
    REQUIRE(properlyInitialized(), "Station was not properly or not initialized before calling getSignal");
    for(std::map<int, Signaal*>::const_iterator it = _Signalen.begin(); it != _Signalen.end(); it++){
        if(it->first == spoor){
            return it->second;
        }
    }
    return NULL;
}

bool Station::operator==(const Station &rhs) const {
    return _Naam == rhs._Naam &&
           _Volgende == rhs._Volgende &&
           _Vorige == rhs._Vorige &&
           _Sporen == rhs._Sporen &&
           _Type == rhs._Type &&
           _Trams == rhs._Trams &&
           _Signalen == rhs._Signalen;
}

bool Station::operator!=(const Station &rhs) const {
    return !(rhs == *this);
}

Station::Station(const std::string &naam, const std::pair<int, Station *> &volgende,
                 const std::pair<int, Station *> &vorige, int spoor, const StationType &type)
        : _Naam(naam), _Type(type) {
    _Volgende[volgende.first]=volgende.second;
    _Vorige[vorige.first]=vorige.second;
    _Sporen.push_back(spoor);
    Station::_propInit = this;
    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");

}

void Station::setVolgende1(const std::map<int, Station *> &volgende) {
    _Volgende = volgende;
}

void Station::setVorige1(const std::map<int, Station *> &vorige) {
    _Vorige = vorige;
}

Station::Station(const std::string &_Naam, std::map<int, Station *> &_Volgende, std::map<int, Station *> &_Vorige,
                 int _Spoor, StationType _Type):
    _Naam(_Naam), _Volgende(_Volgende), _Vorige(_Vorige), _Type(_Type) {
        //REQUIRE(is_valid_station_type(_Type),"the variable \"_Type\" has to be a valid station type");
        Station::_Sporen.push_back(_Spoor);             // because we are not sure what happens if we write _Sporen(_Spoor)
        Station::_propInit = this;

        // We make sure that the object is properly initialized by using the ENSURE function
        ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");
        validStationMembers();
    }

//---------------------------------//
//// Tests

class ValidStationTest: public ::testing::Test {
public:
    ValidStationTest() {
        stationC = new Station("C");
        stationB = new Station("B");
        stationA = new Station("A",std::pair<int,Station*>(12,stationB),std::pair<int,Station*>(12,stationC),12,Halte);
        stationB->setVorige(12, stationA);
        stationB->setVolgende(12,stationC);
        stationB->setType(Halte);
        stationB->addSpoor(12);
        stationC->setVorige(12,stationB);
        stationC->setVolgende(12,stationA);
        stationC->setType(Halte);
        stationC->addSpoor(12);
    }

    void SetUp() {
        // code here will execute just before the test ensues
    }

    void TearDown() {
        delete stationA;
        delete stationB;
        delete stationC;
    }

    Station* stationA;
    Station* stationB;
    Station* stationC;

};


// tests getter functions from Station
TEST_F(ValidStationTest, gettersAndSetters){
    EXPECT_EQ("A",stationA->getNaam());
    EXPECT_EQ(stationB,stationA->getVolgende(12));
    EXPECT_EQ(stationC,stationA->getVorige(12));
    std::vector<int> testsporen;
    testsporen.push_back(12);
    EXPECT_EQ(testsporen, stationA->getSporen());
    Station* stationD = new Station("D",std::pair<int,Station*>(13,stationC),std::pair<int,Station*>(13,stationC),13,Metrostation);
    stationC->addSpoor(13);
    stationC->setVolgende(13,stationD);
    stationC->setVorige(13,stationD);
    testsporen.push_back(13);
    EXPECT_EQ(testsporen, stationC->getSporen());
    EXPECT_EQ(stationD,stationC->getVolgende(13));
    EXPECT_EQ(stationD,stationC->getVorige(13));
    stationD->setSporen(testsporen);
    EXPECT_EQ(testsporen, stationD->getSporen());


    delete stationD;
}

// tests properlyInitialized in metronet
TEST_F(ValidStationTest, properlyInitialized){
    EXPECT_TRUE(stationA->properlyInitialized());
}
