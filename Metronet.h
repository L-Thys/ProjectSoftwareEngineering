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
     * @post : the destructor will make sure the object is properly deleted
     */
    virtual ~Metronet();

    /**
     * @brief : this method gives the full set of stations back
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling getStations")
     *
     * @return : a map of stations, with their name as search_key
     * */
    const std::map<std::string, Station *> &getStations();

    /**
     * @brief : this method returns all Trams inside the network
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling getTrams")
     *
     * @return : a map of Trams with their lines (integers) as their search_keys
     * */
    const std::vector<Tram *> &getTrams();

    /**
     * @brief : this method adds a Station to the collection of stations
     *
     * @param station : a pointer to a station
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling addStation")
     *
     * @return : boolean which indicates if the station could be added or not
     * */
    bool addStation(Station* station);

    /**
     * @brief : this method adds a tram to the collection of trams
     *
     * @param tram : a pointer to a tram
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling addTram")
     *
     * @return : boolean which indicates if the tram could be added or not
     * */
    void addTram (Tram* tram);

    /**
     * @brief : given a name, this method searches the corresponding station in the collection
     *
     * @param name is the name of the station
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling findStation")
     *
     * @pre the name must be a valid name
     *      --> REQUIRE (is_valid_String(name), "The given string is not a valid name for a Station")
     *
     * @return a pointer to a station, NULL if there is no corresponding station
     * */
    Station* findStation(const std::string& name);

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
     * @brief this method check whether there are stations and trams in the network or not
     *
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
     * @post : there's a file with the information from this Metronet written in it
     */
    void writeToFile(const char *filename);

    /**
     * @brief this method moves, if possible, the Tram present on the given line which is located in the given station
     *        to the next station.
     *
     * @pre the object must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "Metronet was not properly or no initialized before calling drive")
     *
     * @pre the given string must be a valid name for a station
     *      --> REQUIRE(is_valid_String(_station), "The given station wasn't a valid name of a station")
     *
     * @param _spoor this is a integer that we use to find the right Tram we need to move
     * @param _station this is the station from where we move the tram, this isn't necessarily the right one
     *
     * @return this method returns a boolean that indicates if the move is successfully executed
     */
    bool drive(int _spoor, const Station* _station);

    /**
     * @brief lets the simulation run for a certain time (n)
     *
     * @pre this object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling writeToFile")
     *
     * @pre : there's at least one station in _stations and at least one tram in _trams
     *      and the metronet is consistent
     *      --> REQUIRE(mapsAreNotEmpty() && isConsistent(), "this object should contain a consistent metronet")
     *
     *
     * @param n: the amount of time cycles
     */
    void driveAutomaticaly(int n);

private:
    std::map<std::string, Station*> _stations;
    std::vector<Tram*> _trams;

    Metronet* _propInit;
};

/**
 * @brief reads xml file that's made up according to Specificatie 1.0 and makes a Metronet that reflects the xml
 *
 * @param file: string, path to file from which to read
 *
 * @return the Metronet that was made
 *
 * @pre : this function has no prerequisites
 *
 * @post : this fuction must return a consistent metronet
 *      --> ENSURE (metronet->isConsistent(), "The metronet from the xml-file must be consistent");
 */
Metronet* readFromXml(const char* file);

#endif //PSE_METRONET_H
