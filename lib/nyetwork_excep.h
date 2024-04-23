//
// Created by zsotroav on 2024-04-19.
//

#ifndef LANPLAYER_EXCEP_H
#define LANPLAYER_EXCEP_H

#include <exception>
#include <sstream>
#include <string>

using namespace std;

namespace nyetwork {
    class ConnectionFailed final : public std::exception {
        std::string message;

    public:
        explicit ConnectionFailed(const char * msg) : message(msg) {}
        explicit ConnectionFailed(string msg) : message(std::move(msg)) {}
        explicit ConnectionFailed(const int code) {
            std::stringstream ss;
            ss << "Connection error: " << code;
            message = ss.str();
        }
        ConnectionFailed() : message("Connection failed!") {}

        [[nodiscard]] const char* what() const noexcept override
        { return message.c_str(); }
    };

    class ConnectionIncompatible final : public std::exception {
        std::string message;

    public:
        explicit ConnectionIncompatible(const char * msg) : message(msg) {}
        explicit ConnectionIncompatible(string msg) : message(std::move(msg)) {}
        ConnectionIncompatible() : message("Connection failed!") {}

        [[nodiscard]] const char* what() const noexcept override
        { return message.c_str(); }
    };

    class InvalidConnection final : public std::exception {
        std::string message;

    public:
        explicit InvalidConnection(const char * msg) : message(msg) {}
        explicit InvalidConnection(string msg) : message(std::move(msg)) {}
        InvalidConnection() : message("Connection in invalid state!") {}

        [[nodiscard]] const char* what() const noexcept override
        { return message.c_str(); }
    };
}

#endif //LANPLAYER_EXCEP_H
