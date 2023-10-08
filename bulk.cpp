#include "bulk_class.h"
#include <iostream>

int main(int argc, char* argv[])
{
    int N = 1;
    if (argc == 1)
        std::cout << "Default bulk lenth: " << N << "\n";
    else {
        N = std::stoi(argv[1]);
        std::cout << "Bulk lenth: " << N << "\n";
    }

    Bulk bulk(N);
    std::string cmd;

    while (true)
    {
        std::cin >> cmd;
        bulk.setCmd(cmd);
    }
}