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

        if (type == "STATION"){
            
            for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                std::string naam = e->Value();
                if(naam == "naam" ){
                    for(TiXmlNode* te = e->FirstChild(); te != NULL; te = te->NextSibling()) {
                        TiXmlText *text = te->ToText();
                        if (text == NULL) {
                            continue;
                        }
                        std::string t = text->Value();
                        std::cout << t << std::endl;
                    }
                }

            }
        }
    }
    doc.Clear();
    return 0;
}
