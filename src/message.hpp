#pragma once
#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include <string>

#include <nlohmann/json.hpp>

#include "types.hpp"

using std::string;

using nlohmann::json;

namespace sk {

struct User {
    bool added_to_attachment_menu;
    u64 id;
    string first_name;
    string last_name;
    string full_name = first_name + " " + last_name;
    string username;
};

class Message {
public:
    u64 id;
    u64 update_id;
    string text;
    User from;
    Message(json message_data, string token);
    void reply(string text);
private:
    string token;
    json parsed_data;
};

} // namespace sk

#endif
