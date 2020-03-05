//
// Created by bas on 05/03/2020.
//

#ifndef PSE_METRONET_H
#define PSE_METRONET_H

#include "library.h"
#include "Tram.h"
#include "Station.h"


// TODO : maak een destructor aan

class Metronet {
public:
    /**
     * @brief : deze methode geeft de verzameling stationnen terug
     *
     * @return : geeft de map van strings en Station-pointers terug
     * */
    const std::map<std::string, Station *> &getStations() const;

    /**
     * @brief : deze methode geeft de verzameling trammen terug
     *
     * @return : geeft de map van strings en Tram-pointers terug
     * */
    const std::map<int, Tram *> &getTrams() const;

    /**
     * @brief : deze methode steekt een gegeven station in ons netwerk
     *
     * @param station : een pointer naar een station object dat als pair zal geinsert worden in de overeenkomstige map
     * */
    void addStation(Station* station);

    /**
     * @brief : deze methode steekt een gegeven tram in ons netwerk
     *
     * @param tram : een pointer naar een tram object dat als pair zal geinsert worden in de overeenkomstige map
     * */
    void addTram (Tram* tram);

    bool isConsistent();

private:
    std::map<std::string, Station*> _stations;
    std::map<int, Tram*> _trams;
};


#endif //PSE_METRONET_H