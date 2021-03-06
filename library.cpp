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

bool is_valid_station_type(const std::string &s) {
    return (s=="Metrostation" || s == "Halte");
}

bool is_valid_tram_type(const std::string &s) {
    return (s=="PCC" || s=="Albatros");
}

bool is_valid_signaal_type(const std::string &s) {
    return (s=="STOP" || s=="SNELHEID");
}

bool findInVector (std::string s, std::vector<std::string>& gos) {
    for (std::vector<std::string>::iterator it = gos.begin(); it != gos.end(); ++it){
        if (s == *it) return true;              // return true if the string is found
    }
    return false;
}

bool findInVector (int i, const std::vector<int>& goi) {
    for (std::vector<int>::const_iterator it = goi.begin(); it != goi.end(); ++it){
        if (i == *it) return true;              // return true if the integer is found
    }
    return false;
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

TEST(validStationType,valid){
    EXPECT_TRUE(is_valid_station_type("Halte"));
    EXPECT_TRUE(is_valid_station_type("Metrostation"));
}
TEST(validStationType,notValid){
    EXPECT_FALSE(is_valid_station_type("halte"));
    EXPECT_FALSE(is_valid_station_type("Halte3"));
    EXPECT_FALSE(is_valid_station_type("Metro"));
}

TEST(validTramType,valid){
    EXPECT_TRUE(is_valid_tram_type("PCC"));
    EXPECT_TRUE(is_valid_tram_type("Albatros"));
}
TEST(validTramType,notValid){
    EXPECT_FALSE(is_valid_tram_type("Alatros"));
    EXPECT_FALSE(is_valid_tram_type("\"PCC\""));
    EXPECT_FALSE(is_valid_tram_type("Metro"));
}

TEST(validSignalType,valid){
    EXPECT_TRUE(is_valid_signaal_type("STOP"));
    EXPECT_TRUE(is_valid_signaal_type("SNELHEID"));
}
TEST(validSignalType,notValid){
    EXPECT_FALSE(is_valid_signaal_type("stop"));
    EXPECT_FALSE(is_valid_signaal_type("STOP3"));
    EXPECT_FALSE(is_valid_signaal_type("\"stop\""));
}

TEST(findInVector, IntgersValid){
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(4);
    vec.push_back(6);
    vec.push_back(78);
    vec.push_back(99);

    EXPECT_TRUE(findInVector(1, vec));
    EXPECT_TRUE(findInVector(2, vec));
    EXPECT_TRUE(findInVector(4, vec));
    EXPECT_TRUE(findInVector(6, vec));
    EXPECT_TRUE(findInVector(78, vec));
    EXPECT_TRUE(findInVector(99, vec));
}

TEST(findInVector, IntgersNotValid){
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(4);
    vec.push_back(6);
    vec.push_back(78);
    vec.push_back(99);

    EXPECT_FALSE(findInVector(3, vec));
    EXPECT_FALSE(findInVector(5, vec));
    EXPECT_FALSE(findInVector(7, vec));
    EXPECT_FALSE(findInVector(8, vec));
    EXPECT_FALSE(findInVector(33, vec));
    EXPECT_FALSE(findInVector(47, vec));
    EXPECT_FALSE(findInVector(69, vec));
}