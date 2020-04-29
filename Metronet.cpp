//
// Created by bas on 05/03/2020.
//

#include "Metronet.h"
#include "tinyXML/tinyxml.h"
#include <fstream>
#include <string>
#include <iostream>



const std::map<std::string, Station *> &Metronet::getStations() {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling getStations");
    return _stations;
}

const std::vector<Tram *> &Metronet::getTrams() {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling getTrams");
    return _trams;
}

bool Metronet::addStation(Station *station) {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling addStation");
    bool result = Metronet::_stations.insert(std::pair<std::string, Station*>(station->getNaam(), station)).second;
    ENSURE(findStation(station->getNaam())==station || !result, "the station should be in the _station map if the result is True");
    return result;
}

void Metronet::addTram(Tram *tram) {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling addTram");
    Metronet::_trams.push_back(tram);
}

bool Metronet::isConsistent() {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling isConsistent");
    // -- We check every station in our network -- //
    for (std::map<std::string, Station *>::iterator station = _stations.begin();
        station != _stations.end(); station++) {

        // ~ Spoor is automatically set on -1 to easily check if Spoor is changed or not ~ //
        if (station->second->getSporen().size()==0) {
            return false;
        }

        for (int pcs = 0; pcs < station->second->getSporen().size(); ++pcs) {
            int cs = station->second->getSporen()[pcs];
            // ~ If the station has a valid Spoor, we check if the following and the previous Station also have this Spoor ~ //
            if (station->second->getVolgende(cs) == NULL
                or findStation(station->second->getVolgende(cs)->getNaam()) == NULL
                or !findInVector(cs, station->second->getVolgende(cs)->getSporen())) {
                return false;       // we return false if the equality of the integers in the Spoor member is false
            }

            if (station->second->getVorige(cs) == NULL
                or findStation(station->second->getVorige(cs)->getNaam()) == NULL
                or !findInVector(cs, station->second->getVorige(cs)->getSporen())) {
                return false;       // idem
            }
        }
    }
    // ------------------------------------------- //

    // -- We now check every tram inside _trams if they are initiated correctly -- //
    // tram is a pair <int Tram*>, we need to take tram.second to get the tram itself
    for (std::vector<Tram *>::iterator tram = _trams.begin(); tram != _trams.end(); tram++) {

        // ~ Home is the start Station of our tram, we check if this station is a valid station in our network ~ //
        const Station* home = (*tram)->getStartStation();
        if (findStation(home->getNaam()) == NULL) {
            return false;
        }

        // ~ We also check if the Spoor of the tram is equal to the Spoor that runs through its Start Station ~ //
        if ((*tram)->getLijn() != (*tram)->getStartStation()->getSpoor()) {
            return false;
        }
    }
    // --------------------------------------------------------------------------- //

    return true;
}



void Metronet::makeGraphicalASCII(std::string bestandsnaam) const {
    REQUIRE(properlyInitialized(), "The Metronet was not properly or not initialized before calling findStation");
    std::ofstream file;
    file.open(bestandsnaam.c_str());

    std::vector<int> vec;       // the set of tracks

    // search for every track
    for (std::vector<Tram*>::const_iterator it = _trams.begin(); it != _trams.end(); ++it){
        if (!findInVector((*it)->getLijn(), vec)){
            vec.push_back((*it)->getLijn());
        }
    }

    for (int x = 0; x < vec.size(); ++x){
        int a = vec[x];                         // take the line

        std::vector<Station*> cycleOfStations;

        Station* st = getStationOnTrack(a);     // this is the station to start with
        cycleOfStations.push_back(st);          // add it to the vector

        Station* nst = st->getVolgende(a);       // save the next

        while (nst != st) {                     // the condition that a track must be like a circle shape
            cycleOfStations.push_back(nst);     // as long the next is not the first we add
            nst = nst->getVolgende(a);
        }

        for (int s = 0; s < cycleOfStations.size(); ++s) {                      // write every station
            file << "=" + cycleOfStations[s]->getNaam() + "==";
        }
        file << "(spoor " << a << ")" << std::endl;                             // write the track and a endLine

        for (int s = 0; s < cycleOfStations.size(); ++s) {                      // write every tram
            Tram* t = getStationedTram(cycleOfStations[s], a);
            if (t != NULL) {
                file << " T ";
            }
            else {
                file << "   ";
            }

            Tram* t2 = getMovingTram(cycleOfStations[s], a);
            if (t2 != NULL){
                file << "T";
            }
            else {
                file << " ";
            }
        }
        file << std::endl;
    }
    file.close();
}

Station * Metronet::getStationOnTrack(int track) const {
    REQUIRE(properlyInitialized(), "The Metronet was not properly or not initialized before calling findStation");
    for (std::map<std::string, Station*>::const_iterator it = _stations.begin(); it != _stations.end(); ++it) {
        std::vector<int> sporen = it->second->getSporen();                  // all the tracks we have in the station
        if (findInVector(track, sporen)){                                // if the given track is present
            return it->second;
        }
    }
    return NULL;                                                            // return NULL if no station is found
}

Tram * Metronet::getMovingTram(Station *station, int a) const {
    REQUIRE(properlyInitialized(), "The Metronet was not properly or not initialized before calling findStation");
    // check for a tram from which its current station equals the given, the tracks must be the same and it needs to be moving
    for (std::vector<Tram*>::const_iterator it = _trams.begin(); it != _trams.end(); ++it) {
        if ((*it)->getCurrentStation() == station and (*it)->getLijn() and (*it)->isOnderweg()) return (*it);
    }
    return NULL;                // return NULL if no tram is found
}

Tram * Metronet::getStationedTram(Station *station, int a) const {
    REQUIRE(properlyInitialized(), "The Metronet was not properly or not initialized before calling findStation");
    // check for a tram from which its current station equals the given, the tracks must be the same, it may not be moving
    for (std::vector<Tram*>::const_iterator it = _trams.begin(); it != _trams.end(); ++it) {
        if ((*it)->getCurrentStation() == station and (*it)->getLijn() == a and !(*it)->isOnderweg()) return (*it);
    }
    return NULL;                // return NULL if no tram is found
}

// if name isn't in the list, NULL is returned, so it's best to check if you get NULL from this function before using the returned value
Station * Metronet::findStation(const std::string& name) {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling findStation");
    REQUIRE (is_valid_String(name), "The given string is not a valid name for a Station");
    try {
        return Metronet::_stations.at(name);
    }
    catch(std::out_of_range& e){
        return NULL;
    }
}

Metronet::~Metronet() {
    for(std::vector<Tram*>::iterator it=_trams.begin(); it!=_trams.end(); ++it){
        delete *it;
    }
    for(std::map<std::string, Station*>::iterator it=_stations.begin(); it!=_stations.end(); ++it){
        delete it->second;
    }
}

Metronet::Metronet() {
    _propInit = this;
    ENSURE(properlyInitialized(), "A constructor must end in a properlyInitialized state");
}

bool Metronet::properlyInitialized() const {
    return _propInit == this;
}


void Metronet::writeToFile(const char *filename) {
    REQUIRE(mapsAreNotEmpty() && isConsistent(), "This object should contain a consistent metronet");
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling writeToFile");
    // Open uitvoerbestand
    std::ofstream file(filename);

    // WHILE Nog stations beschikbaar
    for (std::map<std::string,Station*>::iterator it = _stations.begin(); it != _stations.end(); ++it) {
        // Schrijf station-gegevens ui
        file << "Station " << it->second->getNaam() << std::endl;
        std::vector<int> sporen = (*it).second->getSporen();
        for(std::vector<int>::iterator i = sporen.begin(); i != sporen.end(); i++){
            file << "<- Station " << it->second->getVorige(*i) << std::endl;
            file << "-> Station " << it->second->getVolgende(*i) << std::endl;
            file << "Spoor " << *i << std::endl;
        }

    }

    file << std::endl;
    //WHILE Nog voertuigen beschikbaar
    for (int i = 0; i < _trams.size() ; ++i) {
        // Schrijf voertuig-gegevens uit
        file << "Tram " << _trams[i]->getLijn() << " in Station " << _trams[i]->getCurrentStation();
        file << ", " << _trams[i]->getSeats() << " zitplaatsen" << std::endl;
    }
    // Sluit uitvoerbestand
    file.close();
}

bool Metronet::mapsAreNotEmpty() {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling isConsistent");
    return !_trams.empty() && !_stations.empty();
}



void Metronet::driveAutomaticaly(int n) {
    REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling writeToFile");
    REQUIRE(mapsAreNotEmpty() && isConsistent(), "This object should contain a consistent metronet");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; i < _trams.size() ; ++i) {
            _trams[j]->drive();
        }
    }
}

void Metronet::addSignaal(Signaal *signaal) {
    Metronet::_signalen.push_back(signaal);
}


Metronet* readFromXml(const char* file){
    // maak een map stationnen aan, waar een station op naam gezocht kan worden
    // maak een map trammen aan, waar een tram op nummer gezocht kan worden
    Metronet* metronet = new Metronet();

    // open het invoerbestand
    TiXmlDocument doc;
    if(!doc.LoadFile(file)) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return metronet;
    }
    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return metronet;
    }

    // while bestand niet volledig gelezen
    for(TiXmlElement* element = root->FirstChildElement(); element != NULL; element = element->NextSiblingElement()) {
        std::string type = element->Value();

        // herken het type element
        // als het element STATION is
        try {
            if (type == "STATION"){
                std::string stationnaam = "";
                Station* volgende = NULL;
                Station* vorige = NULL;
                int spoor=-1;
                std::string typenaam = "";

                // lees verdere informatie voor het element
                for(TiXmlNode* attribuut = element->FirstChild(); attribuut != NULL; attribuut = attribuut->NextSibling()){

                    std::string naam = attribuut->Value();
                    if (attribuut->FirstChild() == NULL) throw ongeldige_informatie();
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if(naam == "naam"){
                        if (!is_valid_String(text->Value())) throw ongeldige_informatie();
                        stationnaam = text->Value();
                    }
                    else if(naam == "volgende"){
                        if (!is_valid_String(text->Value())) throw ongeldige_informatie();
                        volgende = metronet->findStation(text->Value());
                        if(volgende == NULL){
                            volgende = new Station(text->Value());
                            metronet->addStation(volgende);
                        }
                    }
                    else if(naam == "vorige"){
                        if (!is_valid_String(text->Value())) throw ongeldige_informatie();
                        vorige = metronet->findStation(text->Value());
                        if(vorige == NULL) {
                            vorige = new Station(text->Value());
                            metronet->addStation(vorige);
                        }
                    }
                    else if(naam == "spoor"){
                        if (!is_Integer(text->Value())) throw ongeldige_informatie();
                        spoor = std::atol(text->Value());
                    }
                    else if(naam == "type"){
                        if (!is_valid_station_type(text->Value())) throw ongeldige_informatie();
                        typenaam = text->Value();
                    }
                    else throw ongeldige_informatie();
                }
                if(stationnaam == ""|| typenaam == "" || volgende == NULL || vorige == NULL || spoor == -1) throw onvoldoende_informatie();

                // voeg een Station met deze informatie toe aan stations in metronet of pas een bestaande pointer aan
                Station* station= metronet->findStation(stationnaam);
                if(station != NULL){
                    station->setVolgende(spoor,volgende);
                    station->setVorige(spoor,vorige);
                    station->addSpoor(spoor);
                    station->setType(type);
                }else{
                    std::map<int,Station*>vorigemap;
                    vorigemap[spoor]=vorige;
                    std::map<int,Station*>volgendemap;
                    volgendemap[spoor]=volgende;
                    station = new Station(stationnaam,volgendemap,vorigemap,spoor,typenaam);
                    metronet->addStation(station);
                }
                vorige->setVolgende(spoor,station);
                volgende->setVorige(spoor,station);

            }

            // als het element TRAM is
            else if (type == "TRAM"){
                int lijn=-1;
                int voertuigNr = -1;
                Station* beginstation = NULL;
                std::string typenaam = "";
                // lees verdere informatie voor het element
                for(TiXmlNode* attribuut = element->FirstChild(); attribuut != NULL; attribuut = attribuut->NextSibling()){
                    std::string naam = attribuut->Value();
                    if (attribuut->FirstChild() == NULL) throw ongeldige_informatie();
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if(naam == "lijn"){
                        if (!is_Integer(text->Value())) throw ongeldige_informatie();
                        lijn = std::atol(text->Value());
                    }
                    else if(naam == "beginStation"){
                        if (!is_valid_String(text->Value()) ) throw ongeldige_informatie();
                        beginstation = metronet->findStation(text->Value());
                        if(beginstation == NULL) {
                            beginstation = new Station(text->Value());
                            metronet->addStation(beginstation);
                        }
                    }
                    else if(naam == "type"){
                        if (!is_valid_tram_type(text->Value())) throw ongeldige_informatie();
                        typenaam = text->Value();
                    }
                    else if(naam == "voertuigNr"){
                        if (!is_Integer(text->Value())) throw ongeldige_informatie();
                        voertuigNr = std::atol(text->Value());
                    }
                    else throw ongeldige_informatie();
                }
                if(lijn==-1||beginstation==NULL||typenaam == "") throw onvoldoende_informatie();
                // voeg een Tram met deze informatie toe aan trammen
                Tram* tram = new Tram(lijn,beginstation,typenaam);
                metronet->addTram(tram);
                if(voertuigNr!=-1){
                    tram->setVoertuigNr(voertuigNr);
                }
            }
            else if (type == "SIGNAAL"){
                std::string typenaam = "";
                Station* volgende = NULL;
                Station* vorige = NULL;
                int spoor=-1;
                int limiet = -1;

                // lees verdere informatie voor het element
                for(TiXmlNode* attribuut = element->FirstChild(); attribuut != NULL; attribuut = attribuut->NextSibling()){

                    std::string naam = attribuut->Value();
                    if (attribuut->FirstChild() == NULL) throw ongeldige_informatie();
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if(naam == "limiet"){
                        if (!is_Integer(text->Value())) throw ongeldige_informatie();
                        spoor = std::atol(text->Value());
                    }
                    else if(naam == "volgende"){
                        if (!is_valid_String(text->Value())) throw ongeldige_informatie();
                        volgende = metronet->findStation(text->Value());
                        if(volgende == NULL){
                            volgende = new Station(text->Value());
                            metronet->addStation(volgende);
                        }
                    }
                    else if(naam == "vorige"){
                        if (!is_valid_String(text->Value())) throw ongeldige_informatie();
                        vorige = metronet->findStation(text->Value());
                        if(vorige == NULL) {
                            vorige = new Station(text->Value());
                            metronet->addStation(vorige);
                        }
                    }
                    else if(naam == "spoor"){
                        if (!is_Integer(text->Value())) throw ongeldige_informatie();
                        spoor = std::atol(text->Value());
                    }
                    else if(naam == "type"){
                        if (!is_valid_signaal_type(text->Value())) throw ongeldige_informatie();
                        typenaam = text->Value();
                    }
                    else throw ongeldige_informatie();
                }
                if(typenaam == "" || volgende == NULL || vorige == NULL || spoor == -1) throw onvoldoende_informatie();

                // voeg een Signaal met deze informatie toe aan signalen in metronet
                Signaal* signaal = new Signaal(spoor,limiet,typenaam,vorige,volgende);
                metronet->addSignaal(signaal);
                volgende->addSignaal(spoor,signaal);
            }
            else{
                std::cerr << "onherkenbaar element" << std::endl;
            }
        } catch (ongeldige_informatie& e){
            std::cerr << e.what() << std::endl;
            continue;
        } catch (onvoldoende_informatie& e) {
            std::cerr << e.what() << std::endl;
            continue;
        }
    }
    doc.Clear();
    if(!metronet->isConsistent()){
        std::cerr << "The metronet from the xml-file isn't consistent"<<std::endl;
    }
    for (__gnu_cxx::__normal_iterator<Tram *const *, std::vector<Tram *> > tram = metronet->getTrams().begin(); tram != metronet->getTrams().end(); tram++) {
        (*tram)->getStartStation()->addTram(*tram);
    }
    return metronet;
}

//---------------------------------//
//// Tests

class ValidMetronetTest: public ::testing::Test {
public:
    ValidMetronetTest() {
        metronet = new Metronet();
        Station* stationB = NULL;
        std::map<int,Station*> b;
        b[12] = stationB;

        Station* stationC = NULL;
        std::map<int,Station*> c;
        c[12] = stationB;

        Station* stationA = new Station("A", b, c, 12, "Halte");
        std::map<int,Station*> a;
        a[12] = stationB;

        stationB = new Station("B", c,a, 12, "Halte");
        stationC = new Station("C", a, b, 12, "Halte");
        metronet->addStation(stationA);
        metronet->addStation(stationB);
        metronet->addStation(stationC);
        stations["A"]=stationA;
        stations["B"]=stationB;
        stations["C"]=stationB;
        Tram* tram = new Tram(12,stationA,"PCC");
        metronet->addTram(tram);
        trams[12]=tram;
    }

    void SetUp() {
        // code here will execute just before the test ensues
    }

    void TearDown() {
        delete metronet;
    }
    Metronet* metronet;
    std::map<std::string, Station *> stations;
    std::map<int, Tram *> trams;

};


// tests properlyInitialized in metronet
TEST_F(ValidMetronetTest, properlyInitialized){
    EXPECT_TRUE(metronet->properlyInitialized());
}

// tests mapsAreNotEmpty in metronet
TEST_F(ValidMetronetTest, mapsAreNotEmpty){
    EXPECT_TRUE(metronet->mapsAreNotEmpty());
}

// tests getter and find functions of Metronet
TEST_F(ValidMetronetTest, gettersAndFinds){
    Station* nullstation = NULL;
    EXPECT_EQ(metronet->getStations(), stations);
    EXPECT_EQ(metronet->getTrams(), trams);
    EXPECT_EQ(*metronet->findStation("A"), *stations["A"]);
    EXPECT_EQ(metronet->findStation("q"),nullstation);
}

// tests adder functions of Metronet
TEST_F(ValidMetronetTest, adders){
    Tram* tram = new Tram(1,metronet->findStation("A"),"PCC");
    metronet->addTram(tram);

    std::map<int,Station*> map;

    Station* station = new Station("Q", map, map,1,"Halte");
    metronet->addStation(station);
    EXPECT_EQ(*metronet->findStation("Q"),*station);


}

// tests isConsistent() in metronet
TEST_F(ValidMetronetTest, Consistence){
    EXPECT_TRUE(metronet->isConsistent());
}

// TODO : de testen voor als er meerdere tracks zijn en als een track meerdere keren in een station voorkomt

// the test with a wrong next station
TEST(Consistence, stationNextNotConsistent){
    Metronet* net = new Metronet();
    Station* st1 = new Station("A");
    Station* st2 = new Station("B");
    Station* st3 = new Station("C");
    st1->setVorige(1, st2);
    st1->setVolgende(1, st2);
    std::vector<int> vec; vec.push_back(1);
    st1->setSporen(vec);
    st2->setVolgende(1, st3);
    st2->setVorige(1, st1);
    st2->setSporen(vec);
    Tram* tr1 = new Tram(1, st1,"PCC");
    net->addStation(st1);
    net->addStation(st2);
    net->addTram(tr1);
    EXPECT_FALSE(net->isConsistent());
    delete net;
}

// the test with a wrong next station
TEST(Consistence, stationNextNull){
    Metronet* net = new Metronet();
    Station* st1 = new Station("A");
    Station* st2 = new Station("B");

    std::vector<int> vec; vec.push_back(1);
    st1->setVorige(1, st2);
    st1->setVolgende(1, st2);
    st1->setSporen(vec);
    st2->setVolgende(1, NULL);
    st2->setVorige(1, st1);
    st2->setSporen(vec);

    Tram* tr1 = new Tram(1, st1,"PCC");
    net->addStation(st1);
    net->addStation(st2);
    net->addTram(tr1);
    EXPECT_FALSE(net->isConsistent());
    delete net;
}

// the test with a wrong previous station
TEST(Consistence, stationPreviousNotConsistent){
    Metronet* net = new Metronet();
    Station* st1 = new Station("A");
    Station* st2 = new Station("B");
    Station* st3 = new Station("C");

    std::vector<int> vec; vec.push_back(1);
    st1->setVorige(1, st2);
    st1->setVolgende(1, st2);
    st1->setSporen(vec);
    st2->setVolgende(1, st1);
    st2->setVorige(1, st3);
    st2->setSporen(vec);

    Tram* tr1 = new Tram(1, st1, "PCC");
    net->addStation(st1);
    net->addStation(st2);
    net->addTram(tr1);
    EXPECT_FALSE(net->isConsistent());
    delete net;
}

// the test with a wrong previous station
TEST(Consistence, stationPreviousNull){
    Metronet* net = new Metronet();
    Station* st1 = new Station("A");
    Station* st2 = new Station("B");

    std::vector<int> vec; vec.push_back(1);
    st1->setVorige(1, st2);
    st1->setVolgende(1, st2);
    st1->setSporen(vec);
    st2->setVolgende(1, st1);
    st2->setVorige(1, NULL);
    st2->setSporen(vec);

    Tram* tr1 = new Tram(1, st1, "PCC");
    net->addStation(st1);
    net->addStation(st2);
    net->addTram(tr1);
    EXPECT_FALSE(net->isConsistent());
    delete net;
}

// the test with the wong track
TEST(Consistence, stationTrackNotConsistent){
    Metronet* net = new Metronet();
    Station* st1 = new Station("A");
    Station* st2 = new Station("B");

    std::vector<int> vec; vec.push_back(2);
    st1->setVolgende(1, st2);
    st1->setVorige(1, st2);
    st2->setVolgende(2, st1);
    st2->setVorige(2, st1);
    std::vector<int> vec2; vec2.push_back(1);
    st1->setSporen(vec);
    st2->setSporen(vec2);

    Tram* tr1 = new Tram(1, st1,"PCC");
    net->addStation(st1);
    net->addStation(st2);
    net->addTram(tr1);
    EXPECT_FALSE(net->isConsistent());
    delete net;
}

// the test where the next's track is wrong
TEST(Consistence, stationNextTrackNotConsistent){
    Metronet* net = new Metronet();
    Station* st1 = new Station("A");
    std::map<int, Station*> map;
    map[2] = st1;

    Station* st2 = new Station("B", map, map, 2, "Halte");
    Tram* tr1 = new Tram(1, st1, "PCC");

    st1->setVolgende(1,st2);
    st1->setVorige(1,st2);
    std::vector<int> vec; vec.push_back(1);
    st1->setSporen(vec);

    net->addStation(st1);
    net->addStation(st2);
    net->addTram(tr1);
    EXPECT_FALSE(net->isConsistent());
    delete net;
}

TEST(Consistence, tramStartNotConsistent){
    Metronet* net = new Metronet();
    Station* st1 = new Station("A");
    std::map<int,Station*> map;
    map[1] = st1;
    Station* st2 = new Station("B", map, map, 1,"Halte");
    Station* st3 = new Station("C", map, map, 1,"Halte");
    Tram* tr1 = new Tram(1, st3, "PCC");

    st1->setVolgende(1, st2);
    st1->setVorige(1, st2);
    std::vector<int> vec; vec.push_back(1);
    st1->setSporen(vec);

    net->addStation(st1);
    net->addStation(st2);
    net->addTram(tr1);
    EXPECT_FALSE(net->isConsistent());
    delete net;
}

// the start station's track is not equal to the track of the tram
TEST(Consistence, stationStartTrackNotConsistent){
    Metronet* net = new Metronet();
    Station* st1 = new Station("A");
    std::map<int,Station*> map;
    map[1] = st1;
    Station* st2 = new Station("B", map, map, 1, "Halte");
    Tram* tr1 = new Tram(2, st1, "PCC");

    st1->setVolgende(1, st2);
    st1->setVorige(1, st2);
    std::vector<int> vec; vec.push_back(1);
    st1->setSporen(vec);

    net->addStation(st1);
    net->addStation(st2);
    net->addTram(tr1);
    EXPECT_FALSE(net->isConsistent());
    delete net;
}

TEST_F(ValidMetronetTest, writeToFile){
    metronet->writeToFile("testresult.txt");
    std::ifstream result ("testresult.txt");
    std::ifstream compare ("testcomp.txt");
    std::string resultstr;
    std::string comparestr;
    while(std::getline(compare,comparestr) ){
        std::getline(result,resultstr);
        EXPECT_EQ(resultstr,comparestr);
    }
    EXPECT_FALSE(std::getline(result,resultstr));
    result.close();
    compare.close();
}


// tests driveAutomaticaly
TEST_F(ValidMetronetTest, driveAutomaticaly){
    metronet->driveAutomaticaly(5);
    EXPECT_EQ("C",metronet->getTrams()[0]->getCurrentStation());
}


// tests readFromXml()
TEST(readFromXml, input){
    Metronet* metronet = readFromXml("test.xml");
    int size = metronet->getStations().size();
    EXPECT_EQ(3,size);
    size = metronet->getTrams().size();
    EXPECT_EQ(1,size);
}

TEST_F(ValidMetronetTest, ASCIIoneTrack){


}