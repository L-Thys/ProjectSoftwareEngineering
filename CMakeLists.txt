cmake_minimum_required(VERSION 3.6)
project(PSE)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# set SFML
link_directories(SFML/lib)
include_directories(SFML/include)
set(SFML_DIR "SFML/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

# set general source files for all targets
set(GENERAL_SOURCE_FILES tinyXML/tinyxmlparser.cpp tinyXML/tinyxmlerror.cpp tinyXML/tinyxml.h tinyXML/tinyxml.cpp
        tinyXML/tinystr.h tinyXML/tinystr.cpp Station.cpp Station.h Tram.cpp Tram.h library.h Metronet.cpp Metronet.h
        OurExceptions.cpp OurExceptions.h Spoor.cpp Spoor.h library.cpp Signaal.cpp Signaal.h)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES main.cpp )

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES main_test.cpp)

# Create RELEASE target
add_executable(PSE ${RELEASE_SOURCE_FILES} ${GENERAL_SOURCE_FILES})

# Create DEBUG target
add_executable(PSE_debug ${DEBUG_SOURCE_FILES} ${GENERAL_SOURCE_FILES})

# Link library
target_link_libraries(PSE_debug gtest sfml-graphics sfml-window sfml-system)
target_link_libraries(PSE gtest sfml-graphics sfml-window sfml-system)