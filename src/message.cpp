#include <string>

#include <curl/curl.h>

#include "message.hpp"

using std::string;
using std::to_string;

namespace sk {

Message::Message(json message_data, const string token) {
    this->token = token;
    id = message_data["message_id"];
    text = message_data["text"];
    from = User {
        .added_to_attachment_menu = !message_data["from"]["added_to_attachment_menu"].is_null(),
        .id = message_data["from"]["id"],
        .first_name = message_data["from"]["first_name"],
        .last_name = message_data["from"]["last_name"].is_null()?"":message_data["from"]["last_name"],
        .username = message_data["from"]["username"]
    };
}

void Message::reply(string text) {
    string url = "https://api.telegram.org/bot" + token + "/sendMessage";
    CURL* handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    string data = "chat_id=" + to_string(from.id) + "&text=" + text + "&reply_to_message_id=" + to_string(id);
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, data.c_str());
    FILE* devnull = fopen("/dev/null", "w+");
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, devnull);
    curl_easy_perform(handle);
    fclose(devnull);
}

} // namespace sk
