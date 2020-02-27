//
// Created by lotte on 27.02.20.
//

#include "tinyXML/tinyxml.h"
#include "iostream"
#include "string"


int main(){
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
        const char* naam;
        if (type == "STATION"){
            naam = elem->Attribute("naam");
            if(naam != NULL)
                std::cout << naam << std::endl; // Do stuff with it
        }
    }
    return 0;
}
