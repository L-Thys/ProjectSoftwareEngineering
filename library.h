//
// Created by bas on 27/02/2020.
//

#ifndef PSE_LIBRARY_H
#define PSE_LIBRARY_H

// all libraries that are probably going to be used in every file in this project
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "OurExceptions.h"
#include "gtest/include/gtest/gtest.h"
#include "DesignByContract.h"
#include "gtest/include/gtest/gtest.h"
#include <fstream>


/**
 * @brief checks if string s is a valid string, according to the specification:
 *        String = Letter { Letter } and Letter = "a" ... "z" | "A" ... "Z"
 *
 * @param s is a string
 *
 * @return true if s is valid, false if not
 */
bool is_valid_String(const std::string& s);

/**
 * @brief checks if string s represents an integer
 *
 * @param s is a string
 *
 * @return true if s represents an integer, false if not
 */
bool is_Integer(const std::string& s);

/**
 * @brief checks if string s represents a valid stationType ("Halte" or "Metrostation")
 *
 * @param s is a string
 *
 * @return true if s represents an valid stationType, false if not
 */
bool is_valid_station_type(const std::string& s);

/**
 * @brief checks if string s represents a valid tramType ("PCC" or "Albatros")
 *
 * @param s is a string
 *
 * @return true if s represents an valid tramType, false if not
 */
bool is_valid_tram_type(const std::string& s);

/**
 * @brief checks if string s represents a valid signaalType ("STOP" or "SNELHEID")
 *
 * @param s is a string
 *
 * @return true if s represents an valid signaalType, false if not
 */
bool is_valid_signaal_type(const std::string & s);

/**
 * @brief Searches a string in a vector of strings
 * @param s a string
 * @param gos a set of strings
 * @return a boolean, true if the string is found
 */
bool findInVector (std::string s, std::vector<std::string>& gos);

/**
 * @brief Searches a integer in a vector of integers
 * @param i an integer
 * @param goi a set of integers
 * @return a boolean, true if the integer is present
 */
bool findInVector (int i, const std::vector<int>& goi);



#endif //PSE_LIBRARY_H
