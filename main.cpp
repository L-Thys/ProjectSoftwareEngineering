//
// Created by lotte on 27.02.20.
//
#include "tinyXML/tinyxml.h"
#include "iostream"

int main(){
    TiXmlDocument doc;
    if(!doc.LoadFile("../test.xml")) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return 1;
    }
    return 0;
}
