//
// Created by bas on 13/03/2020.
//

#include "library.h"


bool is_valid_String(const std::string& s){
    std::string::const_iterator it = s.begin();     // it is the start of the string

    // check on ascii value
    while (it != s.end() && ((*it >= 97 && *it <= 122) || (*it >= 65 && *it <= 90))) ++it;
    return !s.empty() && it == s.end();
}


bool is_Integer(const std::string& s){
    std::string::const_iterator it = s.begin();

    // we check if this char could be an integer
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

// tests function is_valid_String()
TEST (validstring, ValidString) {
    EXPECT_TRUE(is_valid_String("a"));
    EXPECT_TRUE(is_valid_String("abc"));
    EXPECT_TRUE(is_valid_String("Abc"));
}
TEST(validstring, NonValidString){
    EXPECT_FALSE(is_valid_String("a1"));
    EXPECT_FALSE(is_valid_String("a b"));
    EXPECT_FALSE(is_valid_String(" "));
    EXPECT_FALSE(is_valid_String(""));
    EXPECT_FALSE(is_valid_String("#"));
    EXPECT_FALSE(is_valid_String("3"));
}

// tests function is_Integer()
TEST(validInteger, validInt){
    EXPECT_TRUE(is_Integer("348"));
    EXPECT_TRUE(is_Integer("3"));
}
TEST(validInteger, NonValidString){
    EXPECT_FALSE(is_Integer("a23"));
    EXPECT_FALSE(is_Integer("#"));
    EXPECT_FALSE(is_Integer("2A"));
    EXPECT_FALSE(is_Integer(" "));
    EXPECT_FALSE(is_Integer(""));
}