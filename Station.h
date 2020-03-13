// ------------------------------------------------------------------------------------------------------------------ //
// Date: 27.02.20.
//

#ifndef PSE_STATION_H
#define PSE_STATION_H

#include "library.h"

// TODO : all ENSURE bij getters, de operators ook

class Station {
public:
    /**
     * @brief constructor of a station, this constructor takes 4 parameters and initialises the whole object at once
     *        all the members that are initialised are strings, those are given in the constructor, only the track
     *        that is given as member _Spoor is an integer
     *
     * @param _Naam a string that will be the name of our Station
     * @param _Volgende a string that is going to be the next station when a tram passes through, this string can be
     *                  used in the findStation method of Metronet to find the corresponding station
     * @param _Vorige a string, which is the name of the previous station, that will be useful in the findStation
     *                method of Metronet
     * @param _Spoor this is an integer that represents the track (Spoor) that runs through
     *
     * @post This constructor will make sure the object is properly initialized
     *       --> ENSURE (properlyInitialized(), "A constructor must end in a properlyInitialized state")
     * */
    Station(const std::string &_Naam, const std::string &_Volgende, const std::string &_Vorige, int _Spoor);

    /**
     * @brief this method returns the Name of the station for purposes like finding the station inside Metronet
     *
     * @return this returns a constant string in reference, this string is the name and may not be changed
     *
     * @pre the object must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "The Station is not properly or not initialized")
     *
     * @post the return value must be a valid name (string)
     *       --> ENSURE(is_valid_String(_Naam), "getNaam must return a valid string")
     */
    const std::string & getNaam();

    /**
     * @brief this method return the next station on the line
     *
     * @return this returns a string, also to be used in the findStation method
     *
     * @pre the object must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "Station was not initialized when calling getVolgende()")
     *
     * @post the method must return a valid name (string)
     *       --> ENSURE(is_valid_String(_Volgende), "getVolgende must return a valid string")
     */
    const std::string &getVolgende();

    /**
     * @brief returning a string, which is the name of the next station, to be used as input for the findStation in Metronet
     *
     * @return a string probably used as input
     *
     * @pre the oject must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "Station was not initialized when calling getVorige()")
     *
     * @post this method must return a valid name (string)
     *       --> ENSURE(is_valid_String(_Vorige), "getVorige must return a valid string")
     */
    const std::string &getVorige();

    /**
     * @brief this method returns Spoor from this station, the member _Spoor consists momentarily only of 1 Spoor
     *          the return is thus the first, and only, Spoor in the vector of integers
     *
     * @return this returns the integer that indicates which Spoor we use in this station
     *
     * @pre the object must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "Station was not initialized when calling getSpoor()")
     *
     * @post this method must return a valid integer,
     *       but it is unnecessary to make an ENSURE because the compiler already made sure this was the case
     */
    int getSpoor();

    bool operator==(const Station &rhs) const;

    bool operator!=(const Station &rhs) const;

    /**
     * @brief this method gives the full vector of tracks of the station, this is at the moment from a maximum length of 1
     *
     * @return a vector of integers that represent the tracks, these integers can be used in other methods
     *
     * @pre this object must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "Station was not initialized when calling getSporen()")
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
    bool properlyInitialized();

protected:
    /**
     * @brief this method ensures that all members but one, _Sporen, are valid according the given specifications
     *        it is called within the properlyInitialized so it needs no REQUIRE
     *
     * @post this method ensures that _Naam is correct according to the specification that a name only consists of
     *       a-z, A-Z characters
     *       --> ENSURE(is_valid_String(_Naam), "A station has to have a name consisting of a-z, A-Z")
     * @post this method ensures that _Volgende is a valid name of a station, so this can be used in other methods
     *       --> ENSURE(is_valid_String(_Volgende), "A station's next station should be a valid name")
     * @post this method ensures that _Vorige is a valid name of a station, so it could be used in other methods
     *       --> ENSURE(is_valid_String(_Vorige), "A station's previous station should be a valid name")
     */
    void validStationMembers();

private:
    std::string _Naam;
    std::string _Volgende;
    std::string _Vorige;
    std::vector<int> _Sporen;

    Station * _propInit;
};


#endif //PSE_STATION_H
