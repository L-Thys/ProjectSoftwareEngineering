//
// Created by lotte on 27.04.20.
//

#include "Signaal.h"

Signaal::Signaal(int spoor, int limiet, const std::string &type, Station *vorige, Station *volgende) : spoor(spoor),
                                                                                                       limiet(limiet),
                                                                                                       type(type),
                                                                                                       vorige(vorige),
                                                                                                       volgende(
                                                                                                               volgende) {}

Signaal::Signaal(int spoor, const std::string &type, Station *vorige, Station *volgende) : spoor(spoor), type(type),
                                                                                           vorige(vorige),
                                                                                           volgende(volgende) {}

int Signaal::getLimiet() const {
    return limiet;
}

const std::string &Signaal::getType() const {
    return type;
}
