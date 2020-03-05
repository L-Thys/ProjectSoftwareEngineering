//
// Created by lotte on 27.02.20.
//

#include "tinyXML/tinyxml.h"
#include "library.h"
#include "Station.h"
#include "Tram.h"

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


// TODO : extra simulatie functie zodat main niet te groot wordt

int main(){
    // maak een map stationnen aan, waar een station op naam gezocht kan worden
    // maak een map trammen aan, waar een tram op nummer gezocht kan worden
    std::map<std::string,Station> stationnen;
    std::map<int,Tram> trammen;


    // open het invoerbestand
    TiXmlDocument doc;
    if(!doc.LoadFile("test.xml")) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return 1;
    }
    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return 1;
    }

    // while bestand niet volledig gelezen
    for(TiXmlElement* element = root->FirstChildElement(); element != NULL; element = element->NextSiblingElement()) {
        std::string type = element->Value();

        // herken het type element
        // als het element STATION is
        if (type == "STATION"){
            std::string stationnaam;
            std::string volgende;
            std::string vorige;
            int spoor=0;

            // lees verdere informatie voor het element
            for(TiXmlNode* attribuut = element->FirstChild(); attribuut != NULL; attribuut = attribuut->NextSibling()){
                std::string naam = attribuut->Value();
                if(naam == "naam"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL or !is_valid_String(text->Value())) {
                        std::cerr << "ongeldige informatie" << std::endl;
                        continue;
                    }
                    stationnaam = text->Value();
                }
                else if(naam == "volgende"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL or !is_valid_String(text->Value())) {
                        std::cerr << "ongeldige informatie" << std::endl;
                        continue;
                    }
                    volgende = text->Value();
                }
                else if(naam == "vorige"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL or !is_valid_String(text->Value())) {
                        std::cerr << "ongeldige informatie" << std::endl;
                        continue;
                    }
                    vorige = text->Value();
                }
                else if(naam == "spoor"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();

                    if (text == NULL or !is_Integer(text->Value())) {
                        std::cerr << "ongeldige informatie" << std::endl;
                        continue;
                    }
                    spoor = std::atol(text->Value());
                }else{
                    std::cerr << "ongeldige informatie" << std::endl;
                }
            }
            // voeg een Station met deze informatie toe aan stationnen
            stationnen.insert(std::pair<std::string,Station>(stationnaam,Station(stationnaam,volgende,vorige,spoor)));
        }

        // als het element TRAM is
        else if (type == "TRAM"){
            int lijn=0;
            int zitplaatsen=0;
            int snelheid=0;
            std::string beginstation;
            // lees verdere informatie voor het element
            for(TiXmlNode* attribuut = element->FirstChild(); attribuut != NULL; attribuut = attribuut->NextSibling()){
                std::string naam = attribuut->Value();
                if(naam == "lijn"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL or !is_Integer(text->Value())) {
                        std::cerr << "ongeldige informatie" << std::endl;
                        continue;
                    }
                    lijn = std::atol(text->Value());
                }
                else if(naam == "zitplaatsen" ){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL or !is_Integer(text->Value())) {
                        std::cerr << "ongeldige informatie" << std::endl;
                        continue;
                    }
                    zitplaatsen = std::atol(text->Value());
                }
                else if(naam == "snelheid"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL or !is_Integer(text->Value())) {
                        std::cerr << "ongeldige informatie" << std::endl;
                        continue;
                    }
                    snelheid = std::atol(text->Value());
                }
                else if(naam == "beginStation"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL or !is_valid_String(text->Value()) ) {
                        std::cerr << "ongeldige informatie" << std::endl;
                        continue;
                    }
                    beginstation = text->Value();
                }else{
                    std::cerr << "ongeldige informatie" << std::endl;
                }
            }
            // voeg een Tram met deze informatie toe aan trammen
            trammen.insert(std::pair<int,Tram>(lijn,Tram(lijn,zitplaatsen,snelheid,beginstation)));
        }
        else{
            std::cerr << "onherkenbaar element" << std::endl;
        }
    }
    doc.Clear();
    return 0;
}
