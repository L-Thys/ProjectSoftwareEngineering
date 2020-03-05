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

    /**
     * @brief : this constructor creates an object with a number as track-number
     *
     * @param _track : this is an integer that is going to be used as track-number
     * */
    Spoor(int _track);

    /**
     * @brief : this constructor constructs a Spoor with a given Tram and a track-number
     *
     * @param _track : this is an integer that is going to be used as track-number
     * @param tram :
     * */
    Spoor(int _track, Tram *tram);

    /**
     * @brief : this constructor constructs a Spoor with a given Tram and a Station
     *
     * @param _track : this is an integer that is going to be used as track-number
     * @param station :
     * */
    Spoor(int _track, Station *station);

    /**
     * @brief : deze methode voegt een tram toe aan de trams die rijden op dit spoor
     * */
    void addTram(Tram *tram);

    void addStation(Station *station);

private:
    int _track;
    std::vector<Station *> _stations;
    std::vector<Tram *> _trams;
};


#endif //PSE_SPOOR_H
