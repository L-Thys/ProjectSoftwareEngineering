//
// Created by lotte on 27.02.20.
//

#ifndef PSE_STATION_H
#define PSE_STATION_H

#include "string"

class Station {
private:
    std::string fNaam;
    Station* fVolgende;
    Station* fVorige;
    int fSpoor;

public:
    Station();

    const std::string &getFNaam() const;

    void setFNaam(const std::string &fNaam);

    Station *getFVolgende() const;

    void setFVolgende(Station *fVolgende);

    Station *getFVorige() const;

    void setFVorige(Station *fVorige);

    int getFSpoor() const;

    void setFSpoor(int fSpoor);

};


#endif //PSE_STATION_H
