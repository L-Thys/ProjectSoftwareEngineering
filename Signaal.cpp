//
// Created by lotte on 27.04.20.
//

#include "Signaal.h"

Signaal::Signaal(int spoor, int limiet, const SignaalType &type, Station *vorige, Station *volgende) : spoor(spoor),
                                                                                                       limiet(limiet),
                                                                                                       type(type),
                                                                                                       vorige(vorige),
                                                                                                       volgende(
                                                                                                               volgende){
    _propInit = this;
    ENSURE(properlyInitialized(),"A constructor must end in a properlyInitialized state" );
}

Signaal::Signaal(int spoor, const SignaalType &type, Station *vorige, Station *volgende) : spoor(spoor), type(type),
                                                                                           vorige(vorige),
                                                                                           volgende(volgende) {
    ENSURE(properlyInitialized(),"A constructor must end in a properlyInitialized state" );
}

int Signaal::getLimiet() const {
    REQUIRE(properlyInitialized(), "The Signal was not or not properly initialized befor calling getLimiet");
    REQUIRE(type == Snelheid, "The type of the signal must be \"SNELHEID\" when calling getLimiet");
    return limiet;
}

const SignaalType &Signaal::getType() const {
    REQUIRE(properlyInitialized(), "The Signal was not or not properly initialized befor calling getType");
    return type;
}

Signaal::~Signaal() {

}

bool Signaal::properlyInitialized() const {
    return this == _propInit;
}