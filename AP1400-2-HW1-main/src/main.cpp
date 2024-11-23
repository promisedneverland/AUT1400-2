
#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"
using namespace std;
using namespace algebra;

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    // if (true) // make false to run unit-tests
    {
        // debug section
        Matrix m0 = algebra::ones(3, 5);
        Matrix mult = multiply(m0, 5);

        show(m0);
        cout << endl;
        auto er = minor(m0, 1, 1);
        show(er);
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}

