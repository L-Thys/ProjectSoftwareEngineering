//
// Created by bas on 05/03/2020.
//

#ifndef PSE_METRONET_H
#define PSE_METRONET_H

#include "library.h"
#include "Tram.h"
#include "Station.h"
#include "Spoor.h"
#include "Signaal.h"


class Metronet {


public:
    // constructor & destructor -------------------------------------------------------
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
     */
    virtual ~Metronet();

    // graphical ASCII & write to file -----------------------------------------------------------------

    /**
     * @brief this method makes an ascii file which will contain a very basic graphical interpretation of the network
     *
     * @param bestandsnaam is a string, this name is from the file that will be opened
     *
     * @pre The Metronet must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "The Metronet was not properly or not initialized before calling makeGraphicalASCII");
     *
     *
     */
    void makeGraphicalASCII (std::string bestandsnaam) const;

    /**
     * @brief this method outputs a very basic graphical interpretation of the network to the terminal
     *
     * @pre The Metronet must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "The Metronet was not properly or not initialized before calling coutGraphicalASCII");
     */
    void coutGraphicalASCII () const;

    /**
     * @brief this method appends a very basic graphical interpretation of the network to the string
     *
     * @param string is a string, to which the graphical interpretation of the network will be appended
     *
     * @pre The Metronet must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "The Metronet was not properly or not initialized before calling stringGraphicalASCII");
     */
    void stringGraphicalASCII (std::string& string) const;

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

    // getters & finders------------------------------------------------------------------

    /**
     * @brief : this method returns the full set of stations
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
     * @return : a vector of Trams
     * */
    const std::vector<Tram *> &getTrams();

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

    // adders ------------------------------------------------------------------------------

    /**
     * @brief : this method adds a Station to the collection of stations
     *
     * @param station : a pointer to a station
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling addStation")
     *
     * @post : the station should be in the _station map if the result is True
     *      --> ENSURE(findStation(station->getNaam())==station || !result, "the station should be in the _station map if the result is True")
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
     * @post : the tram should be in the _trams vector
     *      --> ENSURE(findInVector(tram,_trams), "the tram should be in the _trams vector");
     *
     * */
    void addTram (Tram* tram);

    /**
     * @brief : this method adds param signaal to the _Signalen vector
     *
     * @param signaal: signaalpointer
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling addSignaal")
     *
     * @post : the signaal should be in the _signalen vector
     *      --> ENSURE(findInVector(signaal, _signalen), "the signaal should be in the _signalen vector");
     *
     */
    void addSignaal (Signaal* signaal);

    // drive ------------------------------------------------------------------------------------

    /**
     * @brief lets the simulation run for a certain time (n)
     *
     * @pre this object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling driveAutomaticale")
     *
     * @pre there's at least one station in _stations and at least one tram in _trams
     *      and the metronet is consistent
     *      --> REQUIRE(mapsAreNotEmpty() && isConsistent(), "this object should contain a consistent metronet")
     *
     * @param n: the amount of seconds the metronet should simulate
     */
    void driveAutomaticaly(int n, bool cout= false);

    // check functions ----------------------------------------------------------------------------------------

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
    bool properlyInitialized() const;

    /**
     * @brief this method check whether there are stations and trams in the network or not
     *
     * @pre this object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling isConsistent")
     *
     * @return whether there's at least one station in _stations and at least one tram in _trams
     */
    bool mapsAreNotEmpty();

protected:

    /**
     * @brief This method takes a station and checks if the station has had a tram leave, this means that there could be
     *        a Tram on his way to the next but isn't there yet
     * @param station a pointer to a Station
     * @param a is an integer
     * @return a pointer to a Tram, is NULL if there is no on that part of the track
     * @pre The Metronet must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "The Metronet was not properly or not initialized before calling getMovingTram");
     */
    Tram* getMovingTram (Station* station, int a) const ;

    /**
     * @brief This method takes a station and checks if the station has currently a waiting train
     * @param station a pointer to a Station
     * @param a is an integer
     * @return a pointer to a Tram, is NULL if there is no Tram in this station
     * @pre The Metronet must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "The Metronet was not properly or not initialized before calling getStationedTram");
     */
    Tram* getStationedTram (Station* station, int a) const ;

    /**
     * @brief This method searches a station that lies on the given track, it gives the first found
     * @param track an integer
     * @return a pointer to a station
     * @pre The Metronet must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "The Metronet was not properly or not initialized before calling getStationOnTrack");
     */
    Station* getStationOnTrack (int track) const;

private:
    std::map<std::string, Station*> _stations;
    std::vector<Tram*> _trams;
    std::vector<Signaal*> _signalen;

    Metronet* _propInit;
};

/**
 * @brief reads xml file that's made up according to Specificatie 2.0 (1.1-1.5) and makes a Metronet that reflects the xml
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

/**
 * @brief Searches a Tram* in a vector
 * @param i an Tram*
 * @param goi a vector<Tram*>
 * @return a boolean, true if the Tram* is present
 */
bool findInVector (Tram* i, const std::vector<Tram*>& goi);

/**
 * @brief Searches a Signaal* in a vector
 * @param i an Signaal*
 * @param goi a vector<Signaal*>
 * @return a boolean, true if the Signaal* is present
 */
bool findInVector (Signaal* i, const std::vector<Signaal*>& goi);



#endif //PSE_METRONET_H
