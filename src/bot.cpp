#include <string>
#include <fstream>

#include "bot.hpp"
#include "logging.hpp"
#include "exceptions.hpp"

using std::string;
using std::fstream;

namespace sk {

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

} // namespace sk
