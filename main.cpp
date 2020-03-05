//
// Created by lotte on 27.02.20.
//

#include "tinyXML/tinyxml.h"
#include "library.h"
#include "Station.h"
#include "Tram.h"
#include "Metronet.h"

/**
 * @brief checks if string s represents an integer
 * @param s
 * @return true if s represents an intiger, false if not
 */
bool is_Integer(const std::string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

/**
 * @brief checks if string s is a valid string, according to the specification:
 * String = Letter { Letter } and Letter = "a" ... "z" | "A" ... "Z"
 * @param s
 * @return true if s is valid, false if not
 */
bool is_valid_String(const std::string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && ((*it >= 97 && *it <= 122) || (*it >= 65 && *it <= 90))) ++it;
    return !s.empty() && it == s.end();
}

Metronet* readFromXml(const char* file);

int main(int argc, char** argv) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
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
                std::string stationnaam;
                std::string volgende;
                std::string vorige;
                int spoor=-1;

                // lees verdere informatie voor het element
                for(TiXmlNode* attribuut = element->FirstChild(); attribuut != NULL; attribuut = attribuut->NextSibling()){

                    std::string naam = attribuut->Value();
                    if(naam == "naam"){
                        TiXmlText *text = attribuut->FirstChild()->ToText();
                        if (text == NULL or !is_valid_String(text->Value())) throw ongeldige_informatie();
                        stationnaam = text->Value();
                    }
                    else if(naam == "volgende"){
                        TiXmlText *text = attribuut->FirstChild()->ToText();
                        if (text == NULL or !is_valid_String(text->Value())) throw ongeldige_informatie();
                        volgende = text->Value();
                    }
                    else if(naam == "vorige"){
                        TiXmlText *text = attribuut->FirstChild()->ToText();
                        if (text == NULL or !is_valid_String(text->Value())) throw ongeldige_informatie();
                        vorige = text->Value();
                    }
                    else if(naam == "spoor"){
                        TiXmlText *text = attribuut->FirstChild()->ToText();

                        if (text == NULL or !is_Integer(text->Value())) throw ongeldige_informatie();
                        spoor = std::atol(text->Value());
                    }else throw ongeldige_informatie();
                }
                // voeg een Station met deze informatie toe aan stations in metronet
                Station* station = new Station(stationnaam,volgende,vorige,spoor);
                metronet->addStation(station);
            }

                // als het element TRAM is
            else if (type == "TRAM"){
                int lijn=-1;
                int zitplaatsen=-1;
                int snelheid=-1;
                std::string beginstation;
                // lees verdere informatie voor het element
                for(TiXmlNode* attribuut = element->FirstChild(); attribuut != NULL; attribuut = attribuut->NextSibling()){
                    std::string naam = attribuut->Value();
                    if(naam == "lijn"){
                        TiXmlText *text = attribuut->FirstChild()->ToText();
                        if (text == NULL or !is_Integer(text->Value())) throw ongeldige_informatie();
                        lijn = std::atol(text->Value());
                    }
                    else if(naam == "zitplaatsen" ){
                        TiXmlText *text = attribuut->FirstChild()->ToText();
                        if (text == NULL or !is_Integer(text->Value())) throw ongeldige_informatie();
                        zitplaatsen = std::atol(text->Value());
                    }
                    else if(naam == "snelheid"){
                        TiXmlText *text = attribuut->FirstChild()->ToText();
                        if (text == NULL or !is_Integer(text->Value())) throw ongeldige_informatie();
                        snelheid = std::atol(text->Value());
                    }
                    else if(naam == "beginStation"){
                        TiXmlText *text = attribuut->FirstChild()->ToText();
                        if (text == NULL or !is_valid_String(text->Value()) ) throw ongeldige_informatie();
                        beginstation = text->Value();
                    }else throw ongeldige_informatie();
                }
                // voeg een Tram met deze informatie toe aan trammen
                Tram* tram = new Tram(lijn,zitplaatsen,snelheid,beginstation);
                metronet->addTram(tram);
            }
            else{
                std::cerr << "onherkenbaar element" << std::endl;
            }
        } catch (ongeldige_informatie& e){
            std::cerr << e.what() << std::endl;
            continue;
        }
    }
    doc.Clear();
    return metronet;
}

class myTestFixture1: public ::testing::Test {
public:
    myTestFixture1( ) {
        metronet = readFromXml("test.xml");
        Station* A = new Station("A","B","C",12);
        Station* B = new Station("B","C","A",12);
        Station* C = new Station("C","A","B",12);
        lijst.insert(std::pair<std::string, Station*>("A",A));
        lijst.insert(std::pair<std::string, Station*>("B",B));
        lijst.insert(std::pair<std::string, Station*>("C",C));
    }

    void SetUp( ) {
        // code here will execute just before the test ensues
    }

    void TearDown( ) {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    ~myTestFixture1( )  {
        // cleanup any pending stuff, but no exceptions allowed
    }
    Metronet* metronet;
    std::map<std::string, Station *> lijst;
    // put in any custom data members that you need
};

TEST_F(myTestFixture1, readFromXml){
    EXPECT_EQ(lijst, metronet->getStations());

}