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
// tests function is_valid_String()
TEST (validstringTest, ValidString) {
    EXPECT_TRUE(is_valid_String("a"));
    EXPECT_TRUE(is_valid_String("abc"));
    EXPECT_TRUE(is_valid_String("Abc"));
}
TEST(validstringTest, NonValidString){
    EXPECT_FALSE(is_valid_String("a1"));
    EXPECT_FALSE(is_valid_String("a b"));
    EXPECT_FALSE(is_valid_String(" "));
    EXPECT_FALSE(is_valid_String(""));
    EXPECT_FALSE(is_valid_String("#"));
    EXPECT_FALSE(is_valid_String("3"));
}

/**
 * @brief checks if string s represents an integer
 *
 * @param s is a string
 *
 * @return true if s represents an integer, false if not
 */
bool is_Integer(const std::string& s);

#endif //PSE_LIBRARY_H
