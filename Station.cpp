//
// Created by lotte on 27.02.20.
//

#include "Station.h"

Station::Station(const std::string name){
    Station::_Naam = name;                // the name is set on the empty string
    Station::_Volgende = NULL;          // the next and previous station are seen as null_pointers
    Station::_Vorige = NULL;
    std::vector<int> null;              // a empty vector is made
    Station::_Sporen = null;            // we associate the empty vector with the tracks of the station
    Station::_propInit = this;

    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");
}

Station::Station(const std::string &_Naam, Station* _Volgende, Station* _Vorige, int _Spoor)
        : _Naam(_Naam), _Volgende(_Volgende), _Vorige(_Vorige) {
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
Station* Station::getVolgende() const {
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getVolgende");
    ENSURE(is_valid_String(_Volgende->getNaam()), "getVolgende must return a valid Station");
    return _Volgende;
}

Station* Station::getVorige() const {
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getVorige");
    ENSURE(is_valid_String(_Vorige->getNaam()), "getVorige must return a valid Station");
    return _Vorige;
}

int Station::getSpoor() const{
    REQUIRE(properlyInitialized(), "The station was not properly or not initialized before calling getSpoor");
    return _Sporen[0];      // momentarily this vector only consists of 1, so we return only 1
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

bool Station::properlyInitialized() const{
    return _propInit == this;
}

void Station::validStationMembers() {
    // we ensure that all the members are valid
    ENSURE(is_valid_String(_Naam), "A station has to have a name consisting of a-z, A-Z");


    // the tracks in _Sporen are always valid integers, otherwise the compiler will give an error
}

void Station::setVolgende(Station *volgende) {
    REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling Station");
    _Volgende = volgende;
    ENSURE(getVolgende()==volgende, "_Volgende should be equal to param volgende");
}

void Station::setVorige(Station *vorige) {
    REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling setVorige");
    _Vorige = vorige;
    ENSURE(getVorige()==vorige, "_Vorige should be equal to param vorige");
}

void Station::setSporen(const std::vector<int> &sporen) {
    REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling setSporen");
    _Sporen = sporen;
    ENSURE(getSporen()==sporen, "_Sporen should be equal to param sporen");
}

//---------------------------------//
//// Tests

class ValidStationTest: public ::testing::Test {
public:
    ValidStationTest() {
        station = new Station("A","B","C",12);
    }

    void SetUp() {
        // code here will execute just before the test ensues
    }

    void TearDown() {
        delete station;
    }

    Station* station;

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
