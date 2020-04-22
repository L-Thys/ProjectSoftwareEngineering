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

// TODO : desing by contract

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

bool is_valid_station_type(const std::string& s);

bool is_valid_tram_type(const std::string& s);

#endif //PSE_LIBRARY_H
