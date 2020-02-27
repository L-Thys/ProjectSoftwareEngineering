//
// Created by bas on 27/02/2020.
//

#ifndef PSE_TRAM_H
#define PSE_TRAM_H
#include "library.h"

class Station;

class Tram {
public:
    Tram();

private:
    int fLijn;
    int fSeats;
    int fSpeed;
    Station* fStartStation;
};


#endif //PSE_TRAM_H
