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
    _Onderweg = false;
    Tram::_propInit = this;
}

Tram::Tram(int lijn, Station *startStation, const std::string &type) : _Lijn(lijn), _StartStation(startStation),
_Type(type) {
    REQUIRE(is_valid_tram_type(type),"the variable \"type\" has to be a valid tram type");
    Tram::_CurrentStation = _StartStation;
    if(type=="Albatros"){
        _Seats = 72;
        _Speed = 70;
    }else if(type ==  "PCC"){
        _Seats = 16;
        _Speed = 40;
    }
    _Onderweg = false;
    Tram::_propInit = this;
    // We make sure that the object is properly initialized by using the ENSURE function
    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");

}


const int Tram::getLijn() const{
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getLijn");
    return _Lijn;
}

const int Tram::getSeats() const{
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getSeats");
    return _Seats;
}

const int Tram::getSpeed() const{
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getSpeed");
    return _Speed;
}

Station* Tram::getStartStation() const{
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

bool Tram::properlyInitialized() const{
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

bool Tram::drive() {
    REQUIRE(properlyInitialized(), "Tram was not properly or no initialized before calling drive");

   if(!_Onderweg){
       if(!_CurrentStation->isInStation(this)) return false;
       _TijdTotVerandering --;
       if(_TijdTotVerandering == 0){
           _CurrentStation->moveTramFrom(this);
           _Onderweg = true;
           _TijdTotVerandering = 7200/_Speed;
           std::cout << "Tram " << _Lijn << " vertrekt uit station " << _CurrentStation->getNaam() << " richting station " << _CurrentStation->getVolgende()->getNaam() << "."<< std::endl;
       }

   }else{
       _TijdTotVerandering --;
       if(_TijdTotVerandering == 0){
           _Onderweg = false;
           _CurrentStation = _CurrentStation->getVolgende();
           if(_CurrentStation == NULL) return false;
           if(_Type == "Albatros" && _CurrentStation->getType() == "Halte"){
               _TijdTotVerandering = 1;
               std::cout << "Tram " << _Lijn << " stopt niet in halte " << _CurrentStation->getNaam() << " aangezien het een Albatros is, de tram rijdt door naar station"<< _CurrentStation->getVolgende()->getNaam() << std::endl;
           }else {
               _CurrentStation->moveTramTo(this);
               _TijdTotVerandering = 60;
               std::cout << "Tram " << _Lijn << " komt aan in station " << _CurrentStation->getNaam() << "." << std::endl;
           }
       }

   }

    ENSURE(getCurrentStation() != NULL, "drive was unsuccessful");
    return true;
}

int Tram::getVoertuigNr() const {
    return _VoertuigNr;
}

void Tram::setVoertuigNr(int voertuigNr) {
    _VoertuigNr = voertuigNr;
}

bool Tram::isOnderweg() const {
    return _Onderweg;
}





//---------------------------------//
//// Tests

class ValidTramTest: public ::testing::Test {
public:
    ValidTramTest() {

        tram = new Tram(12,stationA,"PCC");
        stationA = new Station("A",stationB,stationB,12,"Halte");
        stationB = new Station("B",stationA,stationA,12,"Halte");
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

// tests getter and setter functions from Tram and whether the constructor deals with the types correctly
TEST_F(ValidTramTest, getters){
    EXPECT_EQ(12,tram->getLijn());
    EXPECT_EQ(16,tram->getSeats());
    EXPECT_EQ(40,tram->getSpeed());
    EXPECT_EQ("A",tram->getStartStation()->getNaam());
    EXPECT_EQ("A",tram->getCurrentStation()->getNaam());
    tram->setCurrentStation(stationB);
    EXPECT_EQ("B",tram->getCurrentStation()->getNaam());
    Tram* tram2 = new Tram(11,stationA,"Albatros");
    EXPECT_EQ(70,tram2->getSpeed());
    EXPECT_EQ(72,tram2->getSeats());
    delete tram2;
}

// tests properlyInitialized in metronet
TEST_F(ValidTramTest, properlyInitialized){
    EXPECT_TRUE(tram->properlyInitialized());
}



