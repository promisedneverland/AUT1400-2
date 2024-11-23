#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
        BST bst{};
    bst.add_node(5);
    bst.add_node(10);
    bst.add_node(50);
    BST copy{bst};
    using namespace std;
    // cout << bst << endl;
    // cout << copy << endl;
    EXPECT_EQ(bst.length(), copy.length());
    EXPECT_EQ(bst.get_root()->right->value, copy.get_root()->right->value);
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