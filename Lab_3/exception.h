#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

class errorFile: public std::exception {
public:
    const char* what() const noexcept override { return "File error."; }
};

#endif // EXCEPTION_H
