#pragma once
#ifndef _BOT_HPP_
#define _BOT_HPP_

#include <string>
#include <vector>
#include <fstream>

#include <curl/curl.h>

#include "message.hpp"
#include "logging.hpp"

using std::string;
using std::vector;
using std::fstream;

namespace sk { 

size_t write_callback(void* ptr, size_t size, size_t nmemb, void* userdata);

class Bot {
public:
    Bot(const string& token);
    Bot(fstream file);
    ~Bot();
    void start_polling(void(*message_proc)(Message msg));

private:
    u64 offset = 0;
    string token;
    vector<Message> messages;
    Logging logger;
    void get_messages(json data);
    bool get_updates(CURL* handle);
};

} // namespace sk

#endif
