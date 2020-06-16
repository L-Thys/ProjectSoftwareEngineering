//
// this file is only used for the PSE_debug executable
//

#include "gtest/include/gtest/gtest.h"

// the main function runs all google tests if
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}