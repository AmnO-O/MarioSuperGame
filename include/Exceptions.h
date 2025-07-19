#pragma once
#include <stdexcept>
#include <string>

class ResourceException : public std::runtime_error{
public: 
    explicit ResourceException(const std::string & message)
        : std::runtime_error(message) {};
}; 

class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& message)
        : std::runtime_error(message) {};
};