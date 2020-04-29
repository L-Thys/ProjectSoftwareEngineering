// ------------------------------------------------------------------------------------------------------------------ //
// Date: 27.02.20.
//

#ifndef PSE_STATION_H
#define PSE_STATION_H

#include "library.h"
#include "Tram.h"
#include "Utilities.h"
#include "Signaal.h"

// TODO : all ENSURE bij getters, de operators ook

class Station {
public:

    /**
     * @brief this constructor will make a station with no next or previous or name, this station would not be a very
     *          useful station in our simulation because it can't do anything
     *
     * @param name is the only parameter given, this is the name we give the station
     *
     * @post this method ensure that our station is properly initialized
     *      --> ENSURE properlyInitialized(), "A constructor must end in a properlyInitialized state")
     */
    Station(std::string name);

    /**
     * @brief constructor of a station, this constructor takes 5 parameters and initialises the whole object at once
     *        all the members that are initialised are strings, those are given in the constructor, only the track
     *        that is given as member _Spoor is an integer
     *
     * @param _Naam a string that will be the name of our Station
     * @param _Volgende a map that contains the next station when a tram passes through, the key is the track
     * @param _Vorige a map that cointains the previous station, the track is the key
     * @param _Spoor this is an integer that represents the track (Spoor) that runs through
     * @param _Type is a string that denotes the type of station
     *
     * @pre _Type should be a valid Station type
     *      --> REQUIRE(is_valid_station_type(_Type),"the variable \"_Type\" has to be a valid station type");
     *
     * @post This constructor will make sure the object is properly initialized
     *       --> ENSURE (properlyInitialized(), "A constructor must end in a properlyInitialized state")
     * */
    Station(const std::string &_Naam, std::map<int,Station*> &_Volgende, std::map<int,Station*> &_Vorige, int _Spoor, std::string _Type);

    /**
     * @brief this method returns the Name of the station for purposes like finding the station inside Metronet
     *
     * @return this returns a constant string in reference, this string is the name and may not be changed
     *
     * @pre the object must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "The Station is not properly or not initialized before calling getNaam")
     *
     * @post the return value must be a valid name (string)
     *       --> ENSURE(is_valid_String(_Naam), "getNaam must return a valid string")
     */
    const std::string & getNaam() const;

    /**
     * @brief this method return the next station on the line
     *
     * @return this returns a station pointer
     *
     * @param x: an int referring to the line on which to look for the next station
     *
     * @pre the object must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "Station was not properly or not initialized before calling getVolgende")
     *
     * @post getVolgende should not return NULL
     *       --> ENSURE(result!=NULL, "getVolgende should not return NULL")
     */
    Station* getVolgende(int x) const;

    /**
     * @brief this method return the previous station on the line
     *
     * @return this returns a station pointer
     *
     * @param x: an int referring to the line on which to look for the previous station
     *
     * @pre the object must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "Station was not properly or not initialized before calling getVorige")
     *
     * @post this method must should not return NULL
     *       --> ENSURE(result!=NULL, "getVorige should not return NULL")
     */
    Station* getVorige(int x) const;

    /**
     * @brief this method returns Spoor from this station, the member _Spoor consists momentarily only of 1 Spoor
     *          the return is thus the first, and only, Spoor in the vector of integers
     *
     * @return this returns the integer that indicates which Spoor we use in this station
     *
     * @pre the object must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "Station was not properly or not initialized before calling getSpoor")
     *
     * @post this method must return a valid integer,
     *       but it is unnecessary to make an ENSURE because the compiler already made sure this was the case
     */
    int getSpoor() const;


    /**
     * @brief this method gives the full vector of tracks of the station, this is at the moment from a maximum length of 1
     *
     * @return a vector of integers that represent the tracks, these integers can be used in other methods
     *
     * @pre this object must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "Station was not properly or not initialized before calling getSporen")
     *
     * @post this method must return a vector of integers,
     *       an ENSURE is unnecessary due to the consistency of integers in the compiler
     */
    std::vector<int> getSporen();

    /**
     * @brief this method needs no ENSURE or REQUIRE, it checks if the object is properly initialized by checking if the
     *        'this' pointer still points to the same object as the _propInt member
     *
     * @return this method returns a boolean that indicates if the object is still properly initialized
     */
    bool properlyInitialized() const;

    /**
     * @brief : this method sets _Volgende to the param volgende
     *
     * @param volgende : a pointer to a station
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling setVolgende")
     *
     * @post : _Volgende should be volgende
     *      ENSURE(getVolgende()==volgende, "_Volgende should be equal to param volgende")
     */
    void setVolgende(int x, Station *volgende);

    /**
     * @brief : this method sets _Vorige to the param vorige
     *
     * @param vorige : a pointer to a station
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling setVorige")
     *
     * @post : _Volgende should be volgende
     *      ENSURE(getVorige()==vorige, "_Vorige should be equal to param vorige")
     */
    void setVorige(int x, Station *vorige);

    /**
     * @brief : this method sets _Sporen to the param sporen
     *
     * @param sporen : a vector of ints
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling setSporen")
     *
     * @post : _Volgende should be volgende
     *      ENSURE(getSporen()==sporen, "_Sporen should be equal to param sporen")
     */
    void setSporen(const std::vector<int> &sporen);

    /**
     * @brief : this method adds param spoor to the _Sporen vector
     *
     * @param spoor: int representing a spoor
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling setSporen")
     *
     * @post : param spoor should be in _Sporen
     *      --> ENSURE(findInVector(spoor,_Sporen), "param spoor should be in _Sporen after calling addSpoor")
     */
    void addSpoor(int spoor);

    /**
     * @brief this method returns type from this station
     *
     * @return a string indicates the type of station
     *
     * @pre the object must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "Station was not properly or not initialized before calling getSpoor")
     *
     * @post this method must return a valid station type
     *      --> ENSURE(is_valid_station_type(output), "_Type must be a valid station type")
     */
    const std::string &getType() const;

    /**
     * @brief : this method sets the member _Type
     *
     * @param type: the string which is to be the type
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getStartStation")
     *
     * @pre : param type should be a valid station type
     *      --> REQUIRE(is_valid_station_type(type), "the param type should be a valid station type")
     *
     * @post member _Type should be equal to param type
     *      --> ENSURE(getType()==type, "member _Type should be equal to param type after calling setType")
     */
    void setType(const std::string &type);

    /**
     * brief: this method removes the param tram out of the vector of trampointers _Trams
     *
     * @param tram: a trampointer
     *
     * @return bool: if this tram wasn't in the station this bool will be false
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getStartStation")
     *
     * @post: the param tram should not be in _Trams
     *  --> ENSURE(!findTram(tram), "param tram should not be in _Trams after calling removeTrams")
     */
    bool removeTram(Tram* tram);

    /**
     * @brief : this method adds param tram to the _Trams vector
     *
     * @param tram: trampointer
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling addTram")
     *
     * @post : param tram should be in _Trams
     *      --> ENSURE(findTram(tram), "param tram should be in _Trams after calling addTram")
     */
    void addTram(Tram* tram);

    /**
     * @brief: this method will check whether the param tram is in _Trams, meaning that the tram is in the station
     *
     * @param tram : trampointer
     *
     * @return : true if tram is in _Trams, false if else
     *
     *  @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling addTram")
     */
    bool findTram(Tram* tram);

    /**
     * @brief: this method will check whether the a tram on track a is in the station
     *
     * @param tram : int representing a track
     *
     * @return : true if a tram on track a is in _Trams, false if else
     *
     *  @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling addTram")
     */
    bool findTram(int a);

    /**
     * @brief : this method adds a signaal on a track to the station
     *
     * @param spoor: the track on which the signal should be added
     *
     * @param signaal: a pointer to the signal that should be added
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Station was not properly or not initialized before calling addTram")
     *
     * @post : param signaal should be in _Signalen on track spoor
     *      --> ENSURE(getSignaal(spoor)==signaal, "param signaal should be in _Signalen on track spoor after calling addSignaal")
     */
    void addSignaal(int spoor, Signaal* signaal);

    /**
     * @brief returning a signaalpointer, which points to the signal on track spoor
     *
     * @return a signaalpointer
     *
     * @pre the object must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "Station was not properly or not initialized before calling getSignal")
     *
     */
    Signaal* getSignaal(int spoor) const;

protected:
    /**
     * @brief this method ensures that all members but one, _Sporen, are valid according the given specifications
     *        it is called within the properlyInitialized so it needs no REQUIRE
     *
     * @post this method ensures that _Naam is correct according to the specification that a name only consists of
     *       a-z, A-Z characters
     *       --> ENSURE(is_valid_String(_Naam), "A station has to have a name consisting of a-z, A-Z")
     */
    void validStationMembers();


private:
    std::string _Naam;
    std::map<int,Station *> _Volgende;
    std::map<int,Station *> _Vorige;
    std::vector<int> _Sporen;
    std::string _Type;
    std::vector<Tram*> _Trams;
    std::map<int, Signaal*> _Signalen;

private:

    Station * _propInit;
};


#endif //PSE_STATION_H
