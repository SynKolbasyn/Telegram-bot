#pragma once
#ifndef _LOGGING_HPP_
#define _LOGGING_HPP_

#include <string>
#include <fstream>

#include "types.hpp"

using std::string;
using std::fstream;

namespace sk {

const open_mode FILE_MODE_DISCARD  = fstream::trunc;
const open_mode FILE_MODE_APPEND   = fstream::app;

const u16       LOGGING_OFF        = 0x0000000000000000;
const u16       LOGGING_TO_CONSOLE = 0x0000000000000001;
const u16       LOGGING_TO_FILE    = 0x0000000000000010;
const u16       LOGGING_TIME       = 0x0000000000000100;

const string    DEFAULT_LOGGING_PATH       = "logs.log";

class Logging {
public:
    Logging();
    Logging(const string file_path, u16 logging_mode = LOGGING_TO_CONSOLE | LOGGING_TO_FILE, open_mode file_mode = FILE_MODE_DISCARD);
    ~Logging();
    void info(const string& text);
    void error(const string& text);
    void set_logging_mode(const u16 logging_mode, string file_path = DEFAULT_LOGGING_PATH);

private:
    string file_path;
    u16 logging_mode;
    open_mode file_mode;
};

} // namespace sk

#endif
