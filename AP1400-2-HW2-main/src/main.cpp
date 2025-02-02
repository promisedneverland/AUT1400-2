
#include <iostream>
#include <gtest/gtest.h>
#include "client.h"
#include "server.h"

extern std::vector<std::string> pending_trxs;

void show_pending_transactions()
{
    std::cout << std::string(20, '*') << std::endl;
    for (const auto &trx : pending_trxs)
        std::cout << trx << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}
std::string generateRandomNumber(int n);
int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
        std::cout << generateRandomNumber(10);


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