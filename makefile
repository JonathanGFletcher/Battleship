output: main.o Battleship.o Player.o Ship.o Position.o Grid.o HelperFunctions.o
	g++ -std=c++11 main.o Battleship.o Player.o Ship.o Position.o Grid.o HelperFunctions.o -o battleship

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Battleship.o: Battleship.cpp Battleship.h
	g++ -std=c++11 -c Battleship.cpp

Player.o: Player.cpp Player.h
	g++ -std=c++11 -c Player.cpp

Ship.o: Ship.cpp Ship.h
	g++ -std=c++11 -c Ship.cpp

Position.o: Position.cpp Position.h
	g++ -std=c++11 -c Position.cpp

Grid.o: Grid.cpp Grid.h
	g++ -std=c++11 -c Grid.cpp

HelperFunctions.o: HelperFunctions.cpp HelperFunctions.h
	g++ -std=c++11 -c HelperFunctions.cpp

clean:
	rm battleship main.o Battleship.o Player.o Ship.o Position.o Grid.o HelperFunctions.o