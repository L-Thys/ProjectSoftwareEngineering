//
// Created by bas on 05/03/2020.
//

#ifndef PSE_SPOOR_H
#define PSE_SPOOR_H

#include "library.h"

class Station;
class Tram;

class Spoor {
public:

    Spoor(int _track);

    Spoor(int _track, Tram* tram);

    Spoor(int _track, Station* station);

    /**
     * @brief : deze methode voegt een tram toe aan de trams die rijden op dit spoor
     * */
    void addTram(Tram* tram);

    void addStation(Station* station);

private:
    int _track;
    std::vector<Station*> _stations;
    std::vector<Tram*> _trams;
};


#endif //PSE_SPOOR_H
