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

class ValidMetronetTest: public ::testing::Test {
public:
    ValidMetronetTest() {
        metronet = new Metronet;
        Station* station1 = new Station("A","B","C",12);
        Station* station2 = new Station("B","C","A",12);
        Station* station3 = new Station("C","A","B",12);
        metronet->addStation(station1);
        metronet->addStation(station2);
        metronet->addStation(station3);
        stations["A"]=station1;
        stations["B"]=station2;
        stations["C"]=station3;
        Tram* tram = new Tram(12,60,60,"A");
        metronet->addTram(tram);
        trams[12]=tram;
    }

    void SetUp() {
        // code here will execute just before the test ensues
    }

    void TearDown() {
        delete metronet;
    }
    Metronet* metronet;
    std::map<std::string, Station *> stations;
    std::map<int, Tram *> trams;

};

class ValidTramTest: public ::testing::Test {
public:
    ValidTramTest() {
        tram = new Tram(12,32,60,"A");
    }

    void SetUp() {
        // code here will execute just before the test ensues
    }

    void TearDown() {
        delete tram;
    }

    Tram* tram;

};

class ValidStationTest: public ::testing::Test {
public:
    ValidStationTest() {
        station = new Station("A","B","C",12);
    }

    void SetUp() {
        // code here will execute just before the test ensues
    }

    void TearDown() {
        delete station;
    }

    Station* station;

};


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

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

// tests readFromXml()
TEST(readFromXml, input){
    Metronet* metronet = readFromXml("test.xml");
    int size = metronet->getStations().size();
    EXPECT_EQ(3,size);
    size = metronet->getTrams().size();
    EXPECT_EQ(1,size);
}
TEST(readFromXml, wronginput){
    // todo: toevoegen
    readFromXml("wrongInput1.xml");
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

// tests getter and find functions of Metronet
TEST_F(ValidMetronetTest, gettersAndFinds){
    Station* nulls = NULL;
    Tram* nullt = NULL;
    EXPECT_EQ(metronet->getStations(), stations);
    EXPECT_EQ(metronet->getTrams(), trams);
    EXPECT_EQ(*metronet->findStation("A"), *stations["A"]);
    EXPECT_EQ(metronet->findStation("q"),nulls);
    EXPECT_EQ(*metronet->findTram(12),*trams[12]);
    EXPECT_EQ(metronet->findTram(1),nullt);
}
// tests adder functions of Metronet
TEST_F(ValidMetronetTest, adders){
    Tram* tram = new Tram(1,2,3,"A");
    metronet->addTram(tram);
    EXPECT_EQ(*metronet->findTram(1),*tram);

    Station* station = new Station("Q","P","R",1);
    metronet->addStation(station);
    EXPECT_EQ(*metronet->findStation("Q"),*station);

    //try to add station and tram with name that already exists
    Station* stationA = new Station("Q","p","r",3);
    EXPECT_FALSE(metronet->addStation(stationA));
    EXPECT_EQ(*metronet->findStation("Q"),*station);

    Tram* tramA = new Tram(1,3,4,"Q");
    EXPECT_FALSE(metronet->addTram(tramA));
    EXPECT_EQ(*metronet->findTram(1),*tram);
}
// tests getter functions from Tram
TEST_F(ValidTramTest, getters){
    EXPECT_EQ(12,tram->getLijn());
    EXPECT_EQ(32,tram->getSeats());
    EXPECT_EQ(60,tram->getSpeed());
    EXPECT_EQ("A",tram->getStartStation());
}
// tests getter functions from Station
TEST_F(ValidStationTest, getters){
    EXPECT_EQ("A",station->getNaam());
    EXPECT_EQ("B",station->getVolgende());
    EXPECT_EQ("C",station->getVorige());
    EXPECT_EQ(12,station->getSpoor());
}