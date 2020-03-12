//
// Created by lotte on 12.03.20.
//

//
// Created by lotte on 27.02.20.
//

#include "tinyXML/tinyxml.h"
#include "Metronet.h"
#include "gtest/include/gtest/gtest.h"
#include "systeem.h"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// tests function is_valid_String()
TEST (validstringTest, ValidString) {
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


// tests function is_Integer()
TEST(validInteger, validInt){
    EXPECT_TRUE(is_Integer("348"));
}
TEST(validInteger, NonValidString){
    EXPECT_FALSE(is_Integer("a23"));
    EXPECT_FALSE(is_Integer("#"));
    EXPECT_FALSE(is_Integer("2A"));
    EXPECT_FALSE(is_Integer(" "));
    EXPECT_FALSE(is_Integer(""));
}

// tests readFromXml()
TEST(readFromXml, input){
    Metronet* metronet = readFromXml("test.xml");
    int size = metronet->getStations().size();
    EXPECT_EQ(3,size);
    size = metronet->getTrams().size();
    EXPECT_EQ(1,size);
}
TEST(readFromXml, wronginput){
    // todo for lotte: something is going wrong here in ReadFromXml()
//    readFromXml("wrongInput1.xml");
}

// tests isConsistent() in metronet
TEST(Consistence, consistentMetro){
    Metronet* metronet = readFromXml("test.xml");
    EXPECT_TRUE(metronet->isConsistent());
}
TEST(Consistence, inconsistenMetro){
    // foutetest1: fout beginstation
    Metronet* metronet = readFromXml("foutetest1.xml");
    EXPECT_FALSE(metronet->isConsistent());
}