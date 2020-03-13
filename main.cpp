//
// Created by lotte on 27.02.20.
//

#include "tinyXML/tinyxml.h"
#include "library.h"
#include "Station.h"
#include "Tram.h"
#include "Metronet.h"
#include "systeem.h"

int main(){
    Metronet* metronet = readFromXml("test.xml");
    metronet->isConsistent();
    delete metronet;
    return 0;
}
