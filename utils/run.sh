echo "=========================Start building========================="
time ./build.sh
echo -e "\n========================Starting program========================\n"
../build/Telegram-bot
echo -e "\n=========================End of program========================="
