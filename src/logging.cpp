#include <iostream>
#include <format>
#include <chrono>

#include "logging.hpp"

using std::clog;
using std::format;
using std::chrono::current_zone;
using std::chrono::system_clock;
using std::chrono::zoned_time;

namespace sk {

Logging::Logging() {
    logging_mode = LOGGING_TO_CONSOLE;
    file_mode = FILE_MODE_DISCARD;
}

Logging::Logging(const string file_path, u16 logging_mode /*= LOGGING_TO_CONSOLE | LOGGING_TO_FILE*/, open_mode file_mode /*= FILE_MODE_DISCARD*/) {
    this->file_path = file_path;
    this->logging_mode = logging_mode;
    this->file_mode = file_mode;
}

Logging::~Logging() {

}

void Logging::info(const string& text) {
    if (logging_mode == LOGGING_OFF) return;
    string data = "[INFO] | ";
    if (logging_mode & LOGGING_TIME) {
        const zoned_time current_time{current_zone(), system_clock::now()};
        data.append(format("{} | ", current_time));
    }
    data.append(format("[MESSAGE] -> {}", text));
    if (logging_mode & LOGGING_TO_FILE) {
        fstream file(file_path, file_mode);
        if (file.is_open()) {
            file << data;
            file.close();
        }
    }
    clog << data;
}

void Logging::error(const string& text) {
    if (logging_mode == LOGGING_OFF) return;
    string data = "[ERROR] | ";
    if (logging_mode & LOGGING_TIME) {
        const zoned_time current_time{current_zone(), system_clock::now()};
        data.append(format("{} | ", current_time));
    }
    data.append(format("[MESSAGE] -> {}", text));
    if (logging_mode & LOGGING_TO_FILE) {
        fstream file(file_path, file_mode);
        if (file.is_open()) {
            file << data;
            file.close();
        }
    }
    clog << data;
}

void Logging::set_logging_mode(const u16 logging_mode, string file_path /*= DEFAULT_LOGGING_PATH*/) {
    if (file_path.empty()) this->file_path = file_path;
    if (file_path.compare(DEFAULT_LOGGING_PATH)) this->file_path = file_path;
    this->logging_mode = logging_mode;
}

} // namespace sk
