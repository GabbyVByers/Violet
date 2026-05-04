
/*
    Log.h
*/

#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include <utility> // Needed for std::forward

#define Vi Vi
namespace Vi {

    class Log {
    public:
        Log() = delete;
        Log(const Log&) = delete;
        Log(Log&&) = delete;

        static void error() {
            std::cerr << "\033[31mError\033[0m\n";
            assert(false);
        }

        static void warning() {
            std::cerr << "\033[33mWarning\033[0m\n";
        }

        static void info() {
            std::cerr << "\033[32mInfo\033[0m\n";
        }

        template<typename... Args>
        static void error(std::ostream& os, Args&&... args) {
            os << "\033[31mError:\033[0m ";
            if constexpr (sizeof...(Args) > 0) {
                (os << ... << std::forward<Args>(args));
            }
            os << "\n";
            assert(false);
        }

        template<typename... Args>
        static void warning(std::ostream& os, Args&&... args) {
            os << "\033[33mWarning:\033[0m ";
            if constexpr (sizeof...(Args) > 0) {
                (os << ... << std::forward<Args>(args));
            }
            os << "\n";
        }

        template<typename... Args>
        static void info(std::ostream& os, Args&&... args) {
            os << "\033[32mInfo:\033[0m ";
            if constexpr (sizeof...(Args) > 0) {
                (os << ... << std::forward<Args>(args));
            }
            os << "\n";
        }

        template<typename... Args>
        static void error(Args&&... args) {
            error(std::cerr, std::forward<Args>(args)...);
        }
        
        template<typename... Args>
        static void warning(Args&&... args) {
            warning(std::cerr, std::forward<Args>(args)...);
        }
        
        template<typename... Args>
        static void info(Args&&... args) {
            info(std::cerr, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void print(std::ostream& os, Args&&... args) {
            if constexpr (sizeof...(Args) > 0) {
                (os << ... << std::forward<Args>(args));
            }
        }

        template<typename... Args>
        static void print(Args&&... args) {
            print(std::cout, std::forward<Args>(args)...);
        }
    };
}

