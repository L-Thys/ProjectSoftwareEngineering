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
     *       --> ENSURE(validTramMembers(),"The parameter _StartStation must be a valid string");
     * */
    Tram(int _Lijn, int _Seats, int _Speed, std::string _StartStation);

    /**
     * @brief : this method is used to see on which trajectory this Tram is used
     *
     * @return : the return is of type integer which indicates the 'Lijn'
     */
    const int getLijn() const;

    /**
     * @brief : this method is a getter of the Seats
     *          this is useful to know how many people can be seated inside the Tram
     *
     * @return : an integer that is the exact amount of seats on the Tram
     */
    const int getSeats() const;

    /**
     * @brief : this method is the getter to retrieve the speed of this vehicle, this is always constant
     *
     * @return : a constant integer which is the exact speed
     */
    const int getSpeed() const;

    /**
     * @brief : this method is the getter of the Start Station which is the input to use in the findStation method
     *
     * @return : the string which is the name of this trams start station
     */
    const std::string &getStartStation() const;

    bool operator==(const Tram &rhs) const;

    bool operator!=(const Tram &rhs) const;

    bool properlyInitialized();

    bool validTramMembers();

private:
    int _Lijn;
    int _Seats;
    int _Speed;
    std::string _StartStation;

    Tram* _propInit;
};


#endif //PSE_TRAM_H
