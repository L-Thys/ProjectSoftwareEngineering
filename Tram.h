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
     * @brief Constructor van een tram, de meegegeven parameters worden members
     *
     * @param fLijn : een integer dat aanduidt welke route deze team rijdt
     * @param fSeats : een integer dat aanduidt hoeveel passagiers op het voertuig kunnen
     * @param fSpeed : een integer dat de max speed aanduidt
     * @param fStartStation : een string dat de naam van het startstation van deze tram zal zijn
     * */
    Tram(int _Lijn, int _Seats, int _Speed, std::string _StartStation);

private:
    int _Lijn;
    int _Seats;
    int _Speed;
    std::string _StartStation;
};


#endif //PSE_TRAM_H
