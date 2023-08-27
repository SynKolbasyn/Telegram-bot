#pragma once
#ifndef _EXCEPTIONS_HPP_
#define _EXCEPTIONS_HPP_

#include <string>
#include <exception>

using std::string;
using std::exception;

namespace sk {

class Exception : public exception {
public:
    Exception(const string& message);
    string what();

private:
    string message;
};

} // namespace sk

#endif
