//
// Created by lotte on 27.02.20.
//

#include "tinyXML/tinyxml.h"
#include "library.h"
#include "Station.h"


int main(){
    // commentaartje
    std::map<std::string,Station> stationnen;

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
            Station huidige = Station();
            std::string stationnaam;
            for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                std::string naam = e->Value();
                if(naam == "naam"){
                    TiXmlText *text = e->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    huidige.setFNaam(text->Value());
                    stationnaam = text->Value();
                }
                if(naam == "volgende"){
                    TiXmlText *text = e->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    huidige.setFVolgende(text->Value());
                }
                if(naam == "vorige"){
                    TiXmlText *text = e->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    huidige.setFVorige(text->Value());
                }
                if(naam == "spoor"){
                    TiXmlText *text = e->FirstChild()->ToText();
                    if (text == NULL) {
                        continue;
                    }
                    huidige.setFSpoor(std::atol(text->Value()));
                }

            }
            stationnen[stationnaam] = huidige;
        }

    }
    doc.Clear();
    return 0;
}
