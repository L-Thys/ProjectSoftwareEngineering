//
// Created by bas on 27/02/2020.
//

#ifndef PSE_TRAM_H
#define PSE_TRAM_H
#include "library.h"

class Station;

class Tram {
public:

    /**
     * @brief : the constructor of an object of type Tram, this constructor takes 4 parameters to initialise the object
     *          all members will be initialised by at least one of these parameters
     *
     * @param _Lijn : an integer which indicates on which line this Tram rides
     * @param _Seats : an integer that represents the amount of people that could use this tram
     * @param _Speed : an integer that indicates the maximum speed of the Tram
     * @param _StartStation : a string which is the name of the station where the Tram begins its trajectory
     *
     * @post This constructor will make sure the object is properly initialized
     *       --> ENSURE (properlyInitialized(), "A constructor must end in a properlyInitialized state");
     *       --> ENSURE (validTramMembers(),"The parameter _StartStation must be a valid string");
     * */
    Tram(int _Lijn, int _Seats, int _Speed, std::string _StartStation);

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
    const int getLijn();

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
    const int getSeats();

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
    const int getSpeed();

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
    const std::string &getStartStation();

    bool operator==(const Tram &rhs) const;

    bool operator!=(const Tram &rhs) const;

    /**
     * @brief this method needs no ENSURE or REQUIRE, it checks if the object is properly initialized by checking if the
     *        'this' pointer still points to the same object as the _propInt member
     *
     * @return this method returns a boolean that indicates if the object is still properly initialized
     */
    bool properlyInitialized();

    /**
     * @brief this method checks that _Startstation is valid according the given specifications
     *
     * @return this method returns a boolean that indicates if _Startstation is valid
     */
    bool validTramMembers();

    const std::string &getCurrentStation() const;

    void setCurrentStation(const std::string &currentStation);

private:
    int _Lijn;
    int _Seats;
    int _Speed;
    std::string _StartStation;
    std::string _CurrentStation;

    Tram* _propInit;
};


#endif //PSE_TRAM_H
