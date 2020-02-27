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
     * @brief Constructor of Tram, the given parameters are set as members
     *
     * @param fLijn : an integer that indicates the line this Tram rides
     * @param fSeats : an integer that indicates the amount of passengers are allowed on the Tram
     * @param fSpeed : an integer that indicates the max speed of the Tram
     * @param fStartStation : a string that is the name of the home station of this Tram
     * */
    Tram(int fLijn, int fSeats, int fSpeed, std::string fStartStation);

private:
    int fLijn;
    int fSeats;
    int fSpeed;
    std::string fStartStation;
};


#endif //PSE_TRAM_H
