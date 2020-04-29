cmake_minimum_required(VERSION 3.6)
project(PSE)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES main.cpp tinyXML/tinyxmlparser.cpp tinyXML/tinyxmlerror.cpp tinyXML/tinyxml.h tinyXML/tinyxml.cpp
        tinyXML/tinystr.h tinyXML/tinystr.cpp Station.cpp Station.h Tram.cpp Tram.h library.h Metronet.cpp Metronet.h
        OurExceptions.cpp OurExceptions.h Spoor.cpp Spoor.h library.cpp Signaal.cpp Signaal.h)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES tinyXML/tinyxmlparser.cpp tinyXML/tinyxmlerror.cpp tinyXML/tinyxml.h tinyXML/tinyxml.cpp
        tinyXML/tinystr.h tinyXML/tinystr.cpp Station.cpp Station.h Tram.cpp Tram.h library.h Metronet.cpp Metronet.h
        OurExceptions.cpp OurExceptions.h main_test.cpp library.cpp)

# Create RELEASE target
add_executable(PSE ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(PSE_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(PSE_debug gtest)