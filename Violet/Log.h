
/*
    Logger.h
*/

#pragma once
#include <iostream>
#include <string>

#define Vi Vi
namespace Vi {

    class Log {
    public:
        static void error(std::string message = "") {
            std::cerr << "\033[31mError\033[0m: ";
            std::cerr << message << "\n";
        }
    };
}

