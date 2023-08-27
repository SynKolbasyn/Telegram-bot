# Telegram-bot

## This is a C++ library for [Telegram Bot API](https://core.telegram.org/bots/api)

### Description
Telegram bot library written on C++

### Instructions for develop
- Fork this repository
- Clone your forked repository
- Add your scripts
- Commit and push
- Create a pull request
- Star this repository
- Wait for pull request to merge

### Instructions for use
- Clone this repository
- Copy the contents of the src folder to the following path: "PATH_TO_YOUR_PROJECT/bot/" (cp -r src/ PATH_TO_YOUR_PROJECT/bot/)

#### Using library in code

```C++
...
#include "bot/bot.hpp"
...
void message_proc(sk::Message msg) {
    msg.reply(msg.text);
}
...
int main(int argc, char* argv[]) {
    ...
    sk::Bot bot("123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11");
    ...
    bot.start_polling(message_proc);
    ...
    return 0;
}

```
