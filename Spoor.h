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
     * @brief : deze constructor maakt eeen spoor aan dat al een nummer heeft
     *
     * @param _track : dit is het cijfer dat dit spoor representeert
     * */
    Spoor(int _track);

    /**
     *
     *
     * @param _track : dit is het cijfer dat dit spoor representeert
     * @param tram :
     * */
    Spoor(int _track, Tram* tram);

    /**
     * @brief : deze constructor maakt een object aan en steekt hier de track-nummer in en steekt er al een station in
     *
     * @param _track : dit is het cijfer dat dit spoor representeert
     * @param station :
     * */
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
