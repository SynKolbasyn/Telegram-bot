#pragma once
#ifndef _BOT_HPP_
#define _BOT_HPP_

#include <string>
#include <fstream>

#include "logging.hpp"

using std::string;
using std::fstream;

namespace sk { 

class Bot {
public:
    Bot(const string& token);
    Bot(fstream file);
    ~Bot();

private:
    string token;
    Logging logger;
};

} // namespace sk

#endif
