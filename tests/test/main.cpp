#include <stdio.h>
#include <stdlib.h>


#include "gtest/gtest.h"

int main(int argc, char ** argv) {
    
    int  count = 1;
    if (argc == 2) {
        count = atoi(argv[1]);
    }
    ::testing::FLAGS_gtest_repeat = count;

    ::testing::InitGoogleTest(&argc, argv);

    //::testing::FLAGS_gtest_filter = "VERTIFYCODETEST*";
    //REGISTERUSERTEST
    //::testing::FLAGS_gtest_filter = "SERVER_VERTIFYCODE*";

    return RUN_ALL_TESTS();

}
