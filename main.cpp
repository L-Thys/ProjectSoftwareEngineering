//
// Created by lotte on 27.02.20.
//

#include "tinyXML/tinyxml.h"
#include "library.h"
#include "Station.h"
#include "Tram.h"


int main(){
    // commentaartje
    std::map<std::string,Station> stationnen;
    std::map<int,Tram> trammen;


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
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        std::string type = elem->Value();

        if (type == "STATION"){
            std::string stationnaam;
            std::string volgende;
            std::string vorige;
            int spoor=0;
            for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                std::string naam = e->Value();
                if(naam == "naam"){
                    TiXmlText *text = e->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    stationnaam = text->Value();
                }
                if(naam == "volgende"){
                    TiXmlText *text = e->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    volgende = text->Value();
                }
                if(naam == "vorige"){
                    TiXmlText *text = e->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    vorige = text->Value();
                }
                if(naam == "spoor"){
                    TiXmlText *text = e->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    spoor = std::atol(text->Value());
                }
            }
            // todo: check if the values in stationnaam,volgende,vorige,spoor are valid
            stationnen.insert(std::pair<std::string,Station>(stationnaam,Station(stationnaam,volgende,vorige,spoor)));
        }
        if (type == "TRAM"){
            int lijn=0;
            int zitplaatsen=0;
            int snelheid=0;
            std::string beginstation;
            for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                std::string naam = e->Value();
                if(naam == "lijn"){
                    TiXmlText *text = e->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    lijn = std::atol(text->Value());
                }
                if(naam == "zitplaatsen"){
                    TiXmlText *text = e->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    zitplaatsen = std::atol(text->Value());
                }
                if(naam == "snelheid"){
                    TiXmlText *text = e->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    snelheid = std::atol(text->Value());
                }
                if(naam == "beginStation"){
                    TiXmlText *text = e->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    beginstation = text->Value();
                }
            }
            // todo: check if the values in lijn,zitplaatsen,snelheid,beginstation are valid
            trammen.insert(std::pair<int,Tram>(lijn,Tram(lijn,zitplaatsen,snelheid,beginstation)));
        }
    }
    doc.Clear();
    return 0;
}
