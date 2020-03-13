//
// Created by lotte on 27.02.20.
//

#ifndef PSE_STATION_H
#define PSE_STATION_H

#include "library.h"

class Station {
public:
    /**
     * @brief : constructor of a station, this constructor takes 4 parameters and initialises the whole object at once
     *          all the members that are initialised are strings, those are given in the constructor, only the track
     *          that is given as member _Spoor is an integer
     *
     * @param _Naam : a string that will be the name of our Station
     * @param _Volgende : a string that is going to be the next station when a tram passes through, this string can be
     *                    used in the findStation method of Metronet to find the corresponding station
     * @param _Vorige : a string, which is the name of the previous station, that will be useful in the findStation
     *                  method of Metronet
     * @param _Spoor : this is an integer that represents the track (Spoor) that runs through
     * */
    Station(const std::string &_Naam, const std::string &_Volgende, const std::string &_Vorige, int _Spoor);

    /**
     * @brief : this method returns the Name of the station for purposes like finding the station inside Metronet
     *
     * @return : this returns a constant string in reference, this string is the name and may not be changed
     */
    const std::string &getNaam() const;

    /**
     * @brief : this method return the next station on the line
     *
     * @return : this returns a string, also to be used in the findStation method
     */
    const std::string &getVolgende() const;

    /**
     * @brief : returning a string, which is the name of the next station, to be used as input for the findStation in Metronet
     *
     * @return : a string probably used as input
     */
    const std::string &getVorige() const;

    /**
     * @brief : this method returns Spoor from this station, the member _Spoor consists momentarily only of 1 Spoor
     *          the return is thus the first, and only, Spoor in the vector of integers
     *
     * @return :  this returns the integer that indicates which Spoor we use in this station
     */
    int getSpoor() const;

    bool operator==(const Station &rhs) const;

    bool operator!=(const Station &rhs) const;

    std::vector<int> getSporen();

private:
    std::string _Naam;
    std::string _Volgende;
    std::string _Vorige;
    std::vector<int> _Sporen;
};


#endif //PSE_STATION_H
