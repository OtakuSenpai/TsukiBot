echo "Compiling ZenIRC...."

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -c -g3 ./include/constants.cpp -I ./src

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -c -g3 ./include/ircmessage.cpp -I ./src

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -c -lSDL2_net -lSDL2 -g3 ./include/ircconnector.cpp -I ./src 

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -c -lSDL2 -lSDL2_net -g3 ./include/ZenIRC.cpp -I ./src

echo "Done compiling ZenIRC.Now compiling main...."

g++ -mtune=native -std=c++14 -fmessage-length=30 -fdiagnostics-color=always -Wall -Wextra -pedantic -lstdc++ -lSDL2 -lSDL2_net -g3 -c ./main.cpp -I ./src

echo "Done compiling main.Now linking..."

g++ -lstdc++ -lSDL2_net -lSDL2 main.o ZenIRC.o ircconnector.o ircmessage.o constants.o

rm *.o

echo "Done compiling..."
