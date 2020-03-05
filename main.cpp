//
// Created by lotte on 27.02.20.
//

#include "tinyXML/tinyxml.h"
#include "library.h"
#include "Station.h"
#include "Tram.h"


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
                    if (text == NULL) {
                        continue;
                    }
                    stationnaam = text->Value();
                }
                if(naam == "volgende"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    volgende = text->Value();
                }
                if(naam == "vorige"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    vorige = text->Value();
                }
                if(naam == "spoor"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    spoor = std::atol(text->Value());
                }
            }
            // voeg een Station met deze informatie toe aan stationnen
            stationnen.insert(std::pair<std::string,Station>(stationnaam,Station(stationnaam,volgende,vorige,spoor)));
        }

        // als het element TRAM is
        if (type == "TRAM"){
            int lijn=0;
            int zitplaatsen=0;
            int snelheid=0;
            std::string beginstation;
            // lees verdere informatie voor het element
            for(TiXmlNode* attribuut = element->FirstChild(); attribuut != NULL; attribuut = attribuut->NextSibling()){
                std::string naam = attribuut->Value();
                if(naam == "lijn"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    lijn = std::atol(text->Value());
                }
                if(naam == "zitplaatsen"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    zitplaatsen = std::atol(text->Value());
                }
                if(naam == "snelheid"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    snelheid = std::atol(text->Value());
                }
                if(naam == "beginStation"){
                    TiXmlText *text = attribuut->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    beginstation = text->Value();
                }
            }
            // voeg een Tram met deze informatie toe aan trammen
            trammen.insert(std::pair<int,Tram>(lijn,Tram(lijn,zitplaatsen,snelheid,beginstation)));
        }
    }
    doc.Clear();
    return 0;
}
