echo "Compiling TsukiIRC...."

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -c -g3 ./src/constants.cpp -I ./include

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -c -g3 ./src/ircmessage.cpp -I ./include

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -c -lSDL2_net -lSDL2 -g3 ./src/ircconnector.cpp -I ./include 

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -c -lSDL2 -lSDL2_net -g3 ./src/TsukiIRC.cpp -I ./include

echo "Done compiling TsukiIRC.Now compiling main...."

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -lSDL2 -lSDL2_net -g3 -c ./main.cpp -I ./include

echo "Done compiling main.Now linking..."

g++ -lstdc++ -lSDL2_net -lSDL2 main.o TsukiIRC.o ircconnector.o ircmessage.o constants.o

rm *.o

echo "Done compiling..."
