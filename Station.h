//
// Created by lotte on 27.02.20.
//

#ifndef PSE_STATION_H
#define PSE_STATION_H

#include "string"

class Station {
private:
    std::string fNaam;
    std::string fVolgende;
    std::string fVorige;
    int fSpoor;

public:
    Station();

    const std::string &getFNaam() const;

    void setFNaam(const std::string &fNaam);

    const std::string &getFVolgende() const;

    void setFVolgende(const std::string &fVolgende);

    const std::string &getFVorige() const;

    void setFVorige(const std::string &fVorige);

    int getFSpoor() const;

    void setFSpoor(int fSpoor);

};


#endif //PSE_STATION_H
