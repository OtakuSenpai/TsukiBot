#!/usr/bin/sh

echo "Compiling TsukiIRC...."

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -c ./src/constants.cpp -I ./include

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -c ./src/ircmessage.cpp -I ./include

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -lSDL2_net -lSDL2 -c ./src/ircconnector.cpp -I ./include 

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -lsdl2 -lsdl2_net -c ./src/TsukiIRC.cpp -I ./include

echo "Done compiling TsukiIRC.Now compiling main...."

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -lsdl2 -lsdl2_net -c ./main.cpp -I ./include

echo "Done compiling main.Now linking..."

g++ -o Kikyosama -lstdc++ -lSDL2_net -lSDL2 main.o TsukiIRC.o ircconnector.o ircmessage.o constants.o

rm *.o

echo "Done compiling..."
