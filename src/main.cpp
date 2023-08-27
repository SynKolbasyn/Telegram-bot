#include "bot.hpp"

using sk::Bot;
using sk::Message;

void message_proc(Message msg) {
    msg.reply(msg.text);
}

int main(int argc, char* argv[]) {
    Bot bot("../bot_data/token");
    bot.start_polling(message_proc);
    return 0;
}
