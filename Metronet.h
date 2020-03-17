//
// Created by bas on 05/03/2020.
//

#ifndef PSE_METRONET_H
#define PSE_METRONET_H

#include "library.h"
#include "Tram.h"
#include "Station.h"
#include "Spoor.h"


class Metronet {
public:
    /**
     * @brief : the constructor of an object of type Metronet, this constructor takes no parameters to initialise the object

     *
     * @post This constructor will make sure the object is properly initialized
     *       --> ENSURE (properlyInitialized(), "A constructor must end in a properlyInitialized state");
     */
    Metronet();

    /**
     * @brief: the destructor of an object of type Metronet
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling the destructor")
     *
     * @post : the destructor will make sure all pointers are NULL because the objects they were pointing to have been deleted
     *      --> ENSURE (properlyDeleted(), "A destructor must end in a properlyDeleted state");
     */
    virtual ~Metronet();

    /**
     * @brief : deze methode geeft de verzameling trammen terug
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling getStations")
     *
     * @return : geeft de map van strings en Station-pointers terug
     * */
    const std::map<std::string, Station *> &getStations();

    /**
     * @brief : deze methode geeft de verzameling trammen terug
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling getTrams")
     *
     * @return : geeft de map van strings en Tram-pointers terug
     * */
    const std::map<int, Tram *> &getTrams();

    /**
     * @brief : deze methode steekt een gegeven station in ons netwerk
     *
     * @param station : een pointer naar een station object dat als pair zal geinsert worden in de overeenkomstige map
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling addStation")
     *
     * @return : true als toevoegen gelukt is, false als er al een station met dezelfde naam bestaat
     * */
    bool addStation(Station* station);

    /**
     * @brief : deze methode steekt een gegeven tram in ons netwerk
     *
     * @param tram : een pointer naar een tram object dat als pair zal geinsert worden in de overeenkomstige map
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling addTram")
     *
     * @return : true als toevoegen gelukt is, false als er al een station met dezelfde naam bestaat
     * */
    bool addTram (Tram* tram);

    /**
     * @brief : gegeven een naam zoekt deze methode een station dat dit als naam heeft
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling findStation")
     *
     * @return : een pointer naar een station
     * */
    Station* findStation(const std::string& name);

    /**
     * @brief : gegeven een spoor geeft deze methode de tram terug die op dit spoor rijdt
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling findTram")
     *
     * @return : een pointer naar een tram
     * */
    Tram* findTram(int spoor);


    /**
     * @brief we check if a network is consistent, this means that the station has only 1 track,
     *        a next station and a previous station which are valid stations
     *        and every track occurs a maximum of 1 time (now it is trivial) in the object.
     *        The trams have a track which is the same as the track in their start station,
     *        the tracks only have 1 tram and
     *        the start station of a tram is a valid station.
     *
     * @return a boolean which indicates if the network is consistent
     *
     * @pre this object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling isConsistent")
     */
    bool isConsistent();

    /**
     * @brief this method needs no ENSURE or REQUIRE, it checks if the object is properly initialized by checking if the
     *        'this' pointer still points to the same object as the _propInt member
     *
     * @return this method returns a boolean that indicates if the object is still properly initialized
     */
    bool properlyInitialized();

    /**
     * @brief this method needs no ENSURE or REQUIRE, it checks if the object is properly deleted
     *
     * @return this method returns a boolean that indicates if the object is properly deleted
     */
    bool properlyDeleted();

    /**
     * @pre this object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling isConsistent")
     *
     * @return whether there's at least one station in _stations and at least one tram in _trams
     */
    bool mapsAreNotEmpty();

    /**
     * @brief writes the information about the metronet to an outputfile with filename param filename
     *
     * @param filename : the name of the file to which the information is to be written
     *
     *  @pre this object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling writeToFile")
     *
     * @pre : there's at least one station in _stations and at least one tram in _trams
     *      and the metronet is consistent
     *      --> REQUIRE(mapsAreNotEmpty() && isConsistent(), "this object should contain a consistent metronet")
     *
     * @post : there's a file with the information from this metronet written in it
     */
    void writeToFile(const char *filename);

    bool drive(int _spoor, std::string &_station);

private:
    std::map<std::string, Station*> _stations;
    std::map<int, Tram*> _trams;

    Metronet* _propInit;
};


#endif //PSE_METRONET_H
