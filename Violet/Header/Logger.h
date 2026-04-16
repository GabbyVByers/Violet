
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
        static std::string error_message(std::string message = "") {
            return "\033[31mCatastrophic Error\033[0m: " + message + "\n";
        }
    };
}

