rm -rf ../build/
mkdir ../build/
g++ -o ../build/Telegram-bot -march=native -pipe -std=gnu++23 -flto=auto -Ofast ../src/*.cpp -lcurl
