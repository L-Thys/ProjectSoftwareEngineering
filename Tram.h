//
// Created by bas on 27/02/2020.
//

#ifndef PSE_TRAM_H
#define PSE_TRAM_H
#include "library.h"

class Station;
enum TramType  {_Albatros,_PCC };

class Tram {
public:

    /**
     * @brief : the constructor of an object of type Tram, this constructor takes 3 parameters to initialise the object
     *          all members will be initialised by at least one of these parameters
     *          _Seats and _Speed will be initialised according to the type of tram
     *
     * @param lijn : an integer which indicates on which line this Tram rides
     * @param startStation : a pointer to the station where the Tram begins its trajectory
     * @param type : a string that denotes the type of tram (must be a valid tram type)
     *
     * @pre : this constructor requires that type is a valid tram type
     *      --> REQUIRE(is_valid_tram_type(type),"the variable \"type\" has to be a valid tram type")
     *
     * @post This constructor will make sure the object is properly initialized
     *       --> ENSURE (properlyInitialized(), "A constructor must end in a properlyInitialized state")
     * */
    Tram(int lijn, Station *startStation);

    virtual ~Tram();

    /**
     * @brief : this method is used to see on which trajectory this Tram is used
     *
     * @return : the return is of type integer which indicates the 'Lijn'
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getLijn")
     *
     * @post this method must return a valid integer,
     *       but it is unnecessary to make an ENSURE because the compiler already made sure this was the case
     */
    const int getLijn() const;

    /**
     * @brief : this method is a getter of the Seats
     *          this is useful to know how many people can be seated inside the Tram
     *
     * @return : an integer that is the exact amount of seats on the Tram
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getSeats")
     *
     * @post this method must return a valid integer,
     *       but it is unnecessary to make an ENSURE because the compiler already made sure this was the case
     */
    const int getSeats() const;

    /**
     * @brief : this method is the getter to retrieve the speed of this vehicle, this is always constant
     *
     * @return : a constant integer which is the exact speed
     *
     *  @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getSpeed")
     *
     * @post this method must return a valid integer,
     *       but it is unnecessary to make an ENSURE because the compiler already made sure this was the case
     */
    const int getSpeed() const;

    /**
     * @brief : this method is the getter of the Start Station which is the input to use in the findStation method
     *
     * @return : the string which is the name of this trams start station
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getStartStation")
     *
     * @post the return value must be a valid StartStation (string)
     *       --> ENSURE(is_valid_String(_Naam), "getNaam must return a valid string")
     */
    Station* getStartStation() const;

    /**
     * @brief this method needs no ENSURE or REQUIRE, it checks if the object is properly initialized by checking if the
     *        'this' pointer still points to the same object as the _propInt member
     *
     * @return this method returns a boolean that indicates if the object is still properly initialized
     */
    bool properlyInitialized() const;


    /**
     * @brief : this method is the getter of the current station
     *
     * @return : Stationpointer to the current station
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getStartStation")
     *
     * @post the return value cannot be a nullpointer
     *      --> ENSURE(_CurrentStation!=NULL, "the current station of a tram cannot be NULL")
     */
    const Station* getCurrentStation() const;

    /**
     * @brief : this method sets _CurrentStation to the variable currentStation
     *
     * @param currentStation : a pointer to a station
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling setCurrentStation")
     *
     * @post : the _CurrentStation should be currentStation
     *      --> ENSURE(getCurrentStation()==currentStation, "the _CurrentStation should be currentStation")
     * */
    void setCurrentStation(Station* currentStation);

    /**
     * @brief this method moves, if possible, the Tram which is located in the given station
     *        to the next station.
     *
     * @pre the object must be properly initialized
     *      --> REQUIRE(properlyInitialized(), "Tram was not properly or no initialized before calling drive")
     *
     *
     * @post _TijdTotVerandering should change during this function
     *      --> ENSURE(previousTijdTotVerandering != _TijdTotVerandering, "drive was unsuccessful, time until next movement change hasn't changed");
     *
     * @param station this is the station from where we move the tram, this isn't necessarily the right one
     *
     * @return this method returns a boolean that indicates if the move is successfully executed
     */
    virtual bool drive(std::string & resultstring) = 0;

    /**
     * @brief : this method is the getter of the member voertuignr
     *
     * @return : int: het voertuignr
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getStartStation")
     *
     */
    int getVoertuigNr() const;

    /**
     * @brief : this method is the setter of the member voertuignr
     *
     * @param voertuigNr : an int which is to be the voertuignr
     *
     * @pre : the object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Tram was not properly or not initialized before calling getStartStation")
     *
     * @post member _VoertuigNr should be equal to param voertuigNr
     *       --> ENSURE(getVoertuigNr()==voertuigNr, "member _VoertuigNr should be equal to param voertuigNr after calling setVoertuigNr");
     */
    void setVoertuigNr(int voertuigNr);

    int getPassengers() const;

    int getOpbrengst() const;

    void setOpbrengst(int opbrengst);

    /**
     * @brief this method check whether the tram is on its way/in-between Stations or not
     *
     * @pre this object must be properly initialized
     *      --> REQUIRE (properlyInitialized(), "The Metronet was not properly or not initialized before calling isConsistent")
     *
     * @return whether the train is in-between stations (true), or at a station (false)
     */
    bool isOnderweg() const;

protected:
    int _Lijn;
    int _Seats;
    int _Passengers;
    int _Speed;
    int _VoertuigNr;
    int _Opbrengst;
    Station* _StartStation;
    Station* _CurrentStation;
    TramType _Type;
    bool _Onderweg;
    bool _AtStop;
    int _TijdTotVerandering;


    Tram* _propInit;
};

class Albatros: public Tram{
public:
    Albatros(int lijn, Station *startStation);

    virtual ~Albatros();

    virtual bool drive(std::string& resultstring);
};

class PCC: public Tram{
public:
    PCC(int lijn, Station *startStation);

    virtual ~PCC();

    virtual bool drive(std::string& resultstring);
};

#endif //PSE_TRAM_H
