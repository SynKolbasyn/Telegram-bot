#include <string>
#include <fstream>
#include <thread>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "bot.hpp"
#include "logging.hpp"
#include "exceptions.hpp"

using std::string;
using std::to_string;
using std::fstream;
using std::thread;

using nlohmann::json;

namespace sk {

size_t write_callback(void* ptr, size_t size, size_t nmemb, void* userdata) {
    ((string*)userdata)->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

Bot::Bot(const string& token) {
    if ((token.find("/") == string::npos) && (token.find("\\") == string::npos)) {
        this->token = token;
    }
    else {
        fstream file(token);
        if (!file.is_open()) throw Exception("Can't open file");
        getline(file, this->token);
    }
    logger = Logging("../bot_data/logs.log", LOGGING_TO_CONSOLE | LOGGING_TO_FILE | LOGGING_TIME, FILE_MODE_APPEND);
    logger.info("Bot created\n");
}

Bot::Bot(fstream file) {
    if (!file.is_open()) throw Exception("Can't open file");
    getline(file, token);
    logger = Logging("../bot_data/logs.log", LOGGING_TO_CONSOLE | LOGGING_TO_FILE | LOGGING_TIME, FILE_MODE_APPEND);
    logger.info("Bot created\n");
}

Bot::~Bot() {
    logger.info("Bot terminated\n");
}

void Bot::get_messages(json data) {
    messages.clear();
    for (json message : data) messages.push_back(Message(message["message"], token));
}

bool Bot::get_updates(CURL* handle) {
    string url = "https://api.telegram.org/bot" + token + "/getUpdates";
    string fields = "timeout=10";
    string data;
    curl_easy_reset(handle);
    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
    if (offset != 0) {
        fields.append("&offset=" + to_string(offset));
        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, fields.c_str());
    }
    curl_easy_perform(handle);
    if (json::parse(data)["result"][0].is_null()) return false;
    get_messages(json::parse(data)["result"]);
    offset = (uint64_t)json::parse(data)["result"][0]["update_id"] + 1;
    return true;
}

void Bot::start_polling(void(*message_proc)(Message msg)) {
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* handle = curl_easy_init();
    while (true) {
        if (!get_updates(handle)) continue;
        for (Message message : messages) {
            logger.info("ID: " + to_string(message.from.id) + "\t| Username: " + message.from.username + "\t| Name" + message.from.full_name + "\t| Text: " + message.text + "\n");
            thread(message_proc, message).detach();
        }
    }
    curl_easy_cleanup(handle);
    curl_global_cleanup();
}

} // namespace sk
