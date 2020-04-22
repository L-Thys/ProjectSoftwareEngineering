//
// Created by bas on 27/02/2020.
//

#include "Tram.h"
#include "DesignByContract.h"
#include "Station.h"

Tram::Tram() {
    _Lijn = -1;
    _Seats = -1;
    _Speed = -1;
    _StartStation = NULL;
    _CurrentStation = NULL;

    Tram::_propInit = this;
}

Tram::Tram(const int _Lijn, const int _Seats, const int _Speed, Station* _StartStation) {
    Tram::_Lijn = _Lijn;
    Tram::_Seats = _Seats;
    Tram::_Speed = _Speed;
    Tram::_StartStation = _StartStation;
    Tram::_CurrentStation = _StartStation;

    Tram::_propInit = this;
    // We make sure that the object is properly initialized by using the ENSURE function
    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");

}

Tram::Tram(int lijn, Station *startStation, const std::string &type) : _Lijn(lijn), _StartStation(startStation),
_Type(type) {
    Tram::_CurrentStation = _StartStation;
    if(type=="Albatros"){
        _Seats = 72;
        _Speed = 70;
    }else if(type ==  "PCC"){
        _Seats = 16;
        _Speed = 40;
    }
    Tram::_propInit = this;
    // We make sure that the object is properly initialized by using the ENSURE function
    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");

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

const Station* Tram::getStartStation() {
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getStartStation");
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

const Station* Tram::getCurrentStation() const {
    return _CurrentStation;
}

void Tram::setCurrentStation(Station* currentStation) {
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling Tram");
    _CurrentStation = currentStation;
    ENSURE(getCurrentStation()==currentStation, "the _CurrentStation should be currentStation");
}

bool Tram::drive(const Station *station) {
    REQUIRE(properlyInitialized(), "Tram was not properly or no initialized before calling drive");
    REQUIRE(station != NULL, "The given station-pointer was NULL");
    bool result;

    // we check if the needed tram its station is indeed the needed station
    if (getCurrentStation() == station){                // if so, we move it
        _CurrentStation = station->getVolgende();      // we move the Tram

        // the message of movement is given by printing the track (also tram name), the start and finish station
        std::cout << "Tram " << _Lijn << " drove from station " << station << " to station " << _CurrentStation << std::endl;
        result = true;
    }

        // the given station and the current station do not aling, it is not possible to move a Tram that is not there
    else {                                                      // if not we give an error message
        std::cerr << "There is no Tram present on track " << _Lijn << " in station " << station << ". Give another instruction." << std::endl;
        result =false;
    }

    ENSURE(getCurrentStation() == station->getVolgende() || !result, "drive was unsuccessful");
    ENSURE(getCurrentStation() != NULL, "drive was unsuccessful");
    return result;
}




//---------------------------------//
//// Tests

class ValidTramTest: public ::testing::Test {
public:
    ValidTramTest() {

        tram = new Tram(12,32,60,stationA);
        stationA = new Station("A",stationB,stationB,12);
        stationB = new Station("B",stationA,stationA,12);
    }

    void SetUp() {
        // code here will execute just before the test ensues
    }

    void TearDown() {
        delete tram;
        delete stationA;
        delete stationB;
    }
    Station* stationA;
    Station* stationB;

    Tram* tram;

};

// tests getter and setter functions from Tram
TEST_F(ValidTramTest, getters){
    EXPECT_EQ(12,tram->getLijn());
    EXPECT_EQ(32,tram->getSeats());
    EXPECT_EQ(60,tram->getSpeed());
    EXPECT_EQ("A",tram->getStartStation()->getNaam());
    EXPECT_EQ("A",tram->getCurrentStation()->getNaam());
    tram->setCurrentStation(stationB);
    EXPECT_EQ("B",tram->getCurrentStation()->getNaam());
}

// tests properlyInitialized in metronet
TEST_F(ValidTramTest, properlyInitialized){
    EXPECT_TRUE(tram->properlyInitialized());
}


