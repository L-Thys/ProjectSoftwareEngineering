//
// Created by bas on 27/02/2020.
//

#include "Tram.h"
#include "DesignByContract.h"
#include "Station.h"
#include "signal.h"


Tram::Tram(int lijn, Station *startStation) : _Lijn(lijn), _StartStation(startStation){
    //REQUIRE(is_valid_tram_type(type),"the variable \"type\" has to be a valid tram type");
    Tram::_CurrentStation = _StartStation;
//    if(type=="Albatros"){
//        _Seats = 72;
//        _Speed = 70;
//    }else if(type ==  "PCC"){
//        _Seats = 16;
//        _Speed = 40;
//    }
    _Onderweg = false;
    _TijdTotVerandering=60;
    _AtStop = false;
    _Passengers = 0;
    _Opbrengst = 0;
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

bool Tram::properlyInitialized() const{
    return _propInit == this;
}

const Station* Tram::getCurrentStation() const {
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getStartStation");
    ENSURE(_CurrentStation!=NULL, "the current station of a tram cannot be NULL");
    return _CurrentStation;
}

void Tram::setCurrentStation(Station* currentStation) {
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling Tram");
    _CurrentStation = currentStation;
    ENSURE(getCurrentStation()==currentStation, "the _CurrentStation should be currentStation");
}

int Tram::getVoertuigNr() const {
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getStartStation");
    return _VoertuigNr;
}

void Tram::setVoertuigNr(int voertuigNr) {
    REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getStartStation");
    Tram::_VoertuigNr = voertuigNr;
    ENSURE(getVoertuigNr()==voertuigNr, "member _VoertuigNr should be equal to param voertuigNr after calling setVoertuigNr");
}

bool Tram::isOnderweg() const {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling isConsistent");
    return _Onderweg;
}

Tram::~Tram() {

}

int Tram::getPassengers() const {
    return _Passengers;
}

int Tram::getOpbrengst() const {
    return _Opbrengst;
}

void Tram::setOpbrengst(int opbrengst) {
    _Opbrengst = opbrengst;
}


Albatros::Albatros(int lijn, Station *startStation) : Tram(lijn, startStation) {
    _Seats = 72;
    _Speed = 70;
    _Type = _Albatros;

    // We make sure that the object is properly initialized by using the ENSURE function
    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");

}

bool Albatros::drive(std::string& resultstring) {
    REQUIRE(properlyInitialized(), "Tram was not properly or no initialized before calling drive");
    int previousTijdTotVerandering = _TijdTotVerandering;
    _TijdTotVerandering --;
    if(_TijdTotVerandering <= 0){
        std::ostringstream lijn; // nodig voor resultstring aangezien to_string() pas in c++ 11 werkt
        lijn <<_Lijn;

        bool drive = false;
        if(_AtStop){
            if(!_CurrentStation->getVolgende(_Lijn)->findTram(_Lijn)){
                drive = true;
                resultstring += "Tram " + lijn.str() + " vertrekt uit de stop richting station " + _CurrentStation->getVolgende(_Lijn)->getNaam() + ".\n";
            }
        }
        else if(!_Onderweg){
            int newPassengers = std::rand()%(_Seats-_Passengers);
            _Passengers += newPassengers;
            _Opbrengst += 2*newPassengers;

            std::ostringstream passagiers; // nodig voor resultstring aangezien to_string() pas in c++ 11 werkt
            passagiers << newPassengers;
            if(_CurrentStation->getVolgende(_Lijn)->findTram(_Lijn)){
                Signaal* signaal =_CurrentStation->getVolgende(_Lijn)->getSignaal(_Lijn);
                if (!_AtStop && signaal != NULL && signaal->getType()==Stop){
                    _AtStop = true;
                    _CurrentStation->removeTram(this);
                    resultstring += "Tram " + lijn.str() + " wacht aan stop en " + passagiers.str() + " passagiers stappen op.\n";
                }
            }else{
                drive = true;
                resultstring += "Tram " + lijn.str() + " vertrekt uit station " + _CurrentStation->getNaam() + " richting station " + _CurrentStation->getVolgende(_Lijn)->getNaam() + " en " + passagiers.str() + " passagiers stappen op.\n";
            }
        }
        else{
            _Onderweg = false;
            _CurrentStation = _CurrentStation->getVolgende(_Lijn);
            if(_CurrentStation == NULL) return false;

            if(_CurrentStation->getType() == Halte){
                _TijdTotVerandering = 1;
                if(previousTijdTotVerandering == 1) previousTijdTotVerandering --;

                resultstring +=  "Tram " + lijn.str() + " stopt niet in halte " + _CurrentStation->getNaam() + " aangezien het een Albatros is, de tram rijdt door naar station" + _CurrentStation->getVolgende(_Lijn)->getNaam() +"\n";
            }else {
                int lessPassengers = std::rand()%_Passengers;
                _Passengers -= lessPassengers;
                std::ostringstream passagiers; // nodig voor resultstring aangezien to_string() pas in c++ 11 werkt
                passagiers <<lessPassengers;

                _CurrentStation->addTram(this);
                _TijdTotVerandering = 60;
                resultstring+=  "Tram " + lijn.str() + " komt aan in station " + _CurrentStation->getNaam() + " en " + passagiers.str() + " passagiers stappen af.\n" ;
            }
        }
        if(drive){
            _CurrentStation->removeTram(this);
            _Onderweg = true;
            _TijdTotVerandering = 7200/70; //speed of albatros is 70
            Signaal* signaal =_CurrentStation->getVolgende(_Lijn)->getSignaal(_Lijn);
            if(signaal != NULL && signaal->getType()==Snelheid){
                _TijdTotVerandering = 7200/signaal->getLimiet();
            }

        }
    }
    ENSURE(previousTijdTotVerandering != _TijdTotVerandering, "drive was unsuccessful, time until next movement change hasn't changed");
    return true;
}

Albatros::~Albatros() {

}


PCC::PCC(int lijn, Station *startStation) : Tram(lijn, startStation) {
    _Seats = 16;
    _Speed = 40;
    _Type = _PCC;
    // We make sure that the object is properly initialized by using the ENSURE function
    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");
}

bool PCC::drive(std::string& resultstring) {
    REQUIRE(properlyInitialized(), "Tram was not properly or no initialized before calling drive");
    int previousTijdTotVerandering = _TijdTotVerandering;
    _TijdTotVerandering --;
    if(_TijdTotVerandering <= 0){
        std::ostringstream lijn; // nodig voor resultstring aangezien to_string() pas in c++ 11 werkt
        lijn <<_Lijn;
        bool drive = false;
        if(_AtStop){
            if(!_CurrentStation->getVolgende(_Lijn)->findTram(_Lijn)){
                drive = true;
                resultstring += "Tram " + lijn.str() + " vertrekt uit de stop richting station " + _CurrentStation->getVolgende(_Lijn)->getNaam() + ".\n";
            }
        }
        else if(!_Onderweg){
            int newPassengers = std::rand()%(_Seats-_Passengers);
            _Passengers += newPassengers;
            _Opbrengst += 2*newPassengers;
            std::ostringstream passagiers; // nodig voor resultstring aangezien to_string() pas in c++ 11 werkt
            passagiers << newPassengers;
            if(_CurrentStation->getVolgende(_Lijn)->findTram(_Lijn)){
                Signaal* signaal =_CurrentStation->getVolgende(_Lijn)->getSignaal(_Lijn);
                if (!_AtStop && signaal != NULL && signaal->getType()==Stop){
                    _AtStop = true;
                    _CurrentStation->removeTram(this);
                    resultstring += "Tram " + lijn.str() + " wacht aan stop en " + passagiers.str() + " passagiers stappen op.\n";
                }
            }else{
                drive = true;
                resultstring += "Tram " + lijn.str() + " vertrekt uit station " + _CurrentStation->getNaam() + " richting station " + _CurrentStation->getVolgende(_Lijn)->getNaam() + " en " + passagiers.str() + " passagiers stappen op.\n";
            }
        }
        else{
            _Onderweg = false;
            _CurrentStation = _CurrentStation->getVolgende(_Lijn);
            if(_CurrentStation == NULL) return false;

            int lessPassengers = std::rand()%_Passengers;
            _Passengers -= lessPassengers;
            std::ostringstream passagiers; // nodig voor resultstring aangezien to_string() pas in c++ 11 werkt
            passagiers <<lessPassengers;

            _CurrentStation->addTram(this);
            _TijdTotVerandering = 60;
            resultstring+=  "Tram " + lijn.str() + " komt aan in station " + _CurrentStation->getNaam() + " en " + passagiers.str() + " passagiers stappen af.\n" ;

        }
        if(drive){
            _CurrentStation->removeTram(this);
            _Onderweg = true;
            _TijdTotVerandering = 7200/40; //speed of PCC is 40
            Signaal* signaal =_CurrentStation->getVolgende(_Lijn)->getSignaal(_Lijn);
            if(signaal != NULL && signaal->getType()==Snelheid){
                _TijdTotVerandering = 7200/signaal->getLimiet();
            }
        }
    }
    ENSURE(previousTijdTotVerandering != _TijdTotVerandering, "drive was unsuccessful, time until next movement change hasn't changed");
    return true;
}

PCC::~PCC() {

}

//---------------------------------//
//// Tests

class ValidTramTest: public ::testing::Test {
public:
    ValidTramTest() {
        std::string a= "A";
        std::string b= "B";
        stationB = new Station("B");
        stationA = new Station(a,std::pair<int,Station*>(12,stationB),std::pair<int,Station*>(12,stationB),12,Halte);
        stationB->setVolgende(12,stationA);
        stationB->setVorige(12,stationA);
        stationB->addSpoor(12);
        stationB->setType(Metrostation);
        tram = new PCC(12,stationA);
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
    tram->setVoertuigNr(5);
    EXPECT_EQ(5,tram->getVoertuigNr());
    EXPECT_EQ("B",tram->getCurrentStation()->getNaam());
    Tram* tram2 = new Albatros(11,stationA);
    EXPECT_EQ(70,tram2->getSpeed());
    EXPECT_EQ(72,tram2->getSeats());
    EXPECT_FALSE(tram->isOnderweg());
    delete tram2;
}

// tests properlyInitialized in metronet
TEST_F(ValidTramTest, properlyInitialized){
    EXPECT_TRUE(tram->properlyInitialized());
}

TEST_F(ValidTramTest, driveCPP){
    std::string result;
    tram->drive(result);
    EXPECT_FALSE(tram->isOnderweg());
    for(int i=1;i<60;i++){
        tram->drive(result);
    }
    EXPECT_TRUE(tram->isOnderweg());
    EXPECT_FALSE(stationA->findTram(tram));
    EXPECT_EQ(stationA,tram->getCurrentStation());
    for(int i=0;i<180;i++){
        tram->drive(result);
    }
    EXPECT_TRUE(stationB->findTram(tram));
    EXPECT_EQ(stationB,tram->getCurrentStation());
}

TEST_F(ValidTramTest, omzetTest){
    std::string result;
    for(int i=0;i<61;i++){
        tram->drive(result);
    }
    EXPECT_EQ(tram->getPassengers()*2,tram->getOpbrengst());
}
