//
// Created by bas on 27/02/2020.
//

#include "Tram.h"
#include "DesignByContract.h"

Tram::Tram(const int _Lijn, const int _Seats, const int _Speed, std::string _StartStation) {
    Tram::_Lijn = _Lijn;
    Tram::_Seats = _Seats;
    Tram::_Speed = _Speed;
    Tram::_StartStation = _StartStation;
    Tram::_CurrentStation = _StartStation;

    Tram::_propInit = this;
    // We make sure that the object is properly initialized by using the ENSURE function
    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");

    ENSURE(validTramMembers(),"The parameter _StartStation must be a valid string");
}

const int Tram::getLijn(){
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getLijn");
    return _Lijn;
}

const int Tram::getSeats(){
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getSeats");
    return _Seats;
}

const int Tram::getSpeed(){
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getSpeed");
    return _Speed;
}

const std::string &Tram::getStartStation() {
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getStartStation");
    ENSURE(is_valid_String(_StartStation), "getStartStation must return a valid string");
    return _StartStation;
}

bool Tram::operator==(const Tram &rhs) const {
    return _Lijn == rhs._Lijn &&
           _Seats == rhs._Seats &&
           _Speed == rhs._Speed &&
           _StartStation == rhs._StartStation;
}

bool Tram::operator!=(const Tram &rhs) const {
    return !(rhs == *this);
}

bool Tram::properlyInitialized() {
    return _propInit == this;
}

bool Tram::validTramMembers() {
    return is_valid_String(_StartStation);
}

const std::string &Tram::getCurrentStation() const {
    return _CurrentStation;
}

void Tram::setCurrentStation(const std::string &currentStation) {
    _CurrentStation = currentStation;
}

//---------------------------------//
//// Tests

class ValidTramTest: public ::testing::Test {
public:
    ValidTramTest() {
        tram = new Tram(12,32,60,"A");
    }

    void SetUp() {
        // code here will execute just before the test ensues
    }

    void TearDown() {
        delete tram;
    }

    Tram* tram;

};

// tests getter and setter functions from Tram
TEST_F(ValidTramTest, getters){
    EXPECT_EQ(12,tram->getLijn());
    EXPECT_EQ(32,tram->getSeats());
    EXPECT_EQ(60,tram->getSpeed());
    EXPECT_EQ("A",tram->getStartStation());
    EXPECT_EQ("A",tram->getCurrentStation());
    tram->setCurrentStation("B");
    EXPECT_EQ("A",tram->getCurrentStation());
}

// tests properlyInitialized in metronet
TEST_F(ValidTramTest, properlyInitialized){
    EXPECT_TRUE(tram->properlyInitialized());
}

// tests properlyInitialized in metronet
TEST_F(ValidTramTest, validTramMembers){
    EXPECT_TRUE(tram->validTramMembers());
}
