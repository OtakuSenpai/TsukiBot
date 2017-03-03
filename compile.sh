#!/usr/bin/bash

echo "Compiling ZenIRC...."

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -c ./include/constants.cpp -I ./src

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -c ./include/ircmessage.cpp -I ./src

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -lSDL2_net -lSDL2 -c ./include/ircconnector.cpp -I ./src 

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -lsdl2 -lsdl2_net -c ./include/ZenIRC.cpp -I ./src

echo "Done compiling ZenIRC.Now compiling main...."

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -lsdl2 -lsdl2_net -c ./main.cpp -I ./src

echo "Done compiling main.Now linking..."

g++ -o Kikyosama -lstdc++ -lSDL2_net -lSDL2 main.o ZenIRC.o ircconnector.o ircmessage.o constants.o

rm *.o

echo "Done compiling..."
