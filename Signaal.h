//
// Created by lotte on 27.04.20.
//

#ifndef PSE_SIGNAAL_H
#define PSE_SIGNAAL_H


#include "library.h"
#include "Station.h"

class Signaal {
public:

    /**
     * @brief this constructor takes a spoor, a limit, a type a previous and a next station pointer.
     *        The object will be made a limit signal that is used to reduce speed along a track given by the two pointers
     * @param spoor an integer, this must be a known track
     * @param limiet an integer that decides the speed of vehicles
     * @param type type is SNELHEID and indicates what type of signal this object is
     * @param vorige a pointer to the first end of the track where the signal holds
     * @param volgende a pointer to the end of the part where this signal is active
     *
     * @post This method makes sure the Signal object is properly initialized
     */
    Signaal(int spoor, int limiet, const std::string &type, Station *vorige, Station *volgende);

    /**
     * @brief this constructor takes a spoor a type, a previous and a next station,
     * this will make the object that will give an order to trams to stop on that track
     * @param spoor an integer that represents a track
     * @param type a string that is STOP
     * @param vorige a pointer to the start of the line where this signal active is
     * @param volgende a pointer to the end of the track
     *
     * @post This method makes sure the Signal object is properly initialized
     */
    Signaal(int spoor, const std::string &type, Station *vorige, Station *volgende);

    /**
     * @brief this method returns a integer that is the limit, only if the type is a limit
     * @return an integer
     *
     * @pre the signal must be properly initialized
     * @pre the type must be SNELHEID
     */
    int getLimiet() const;

    /**
     * @brief this method return the Type
     * @return a string
     *
     * @pre the signal must be properly initialized
     */
    const std::string &getType() const;

    /**
     * @brief this method destroys the object
     */
    virtual ~Signaal();

    /**
     * @brief this method checks if we are still in the original object
     * @return true if it's still the original
     */
    bool properlyInitialized() const;
private:
    int spoor;
    int limiet;
    std::string type;
    Station* vorige;
    Station* volgende;

    Signaal* _propInit;
};


#endif //PSE_SIGNAAL_H
