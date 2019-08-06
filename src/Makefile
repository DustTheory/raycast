SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system 
all:
	@echo "** Building the game"
	g++ -c "Map.cpp" -o Map.o
	g++ -c "Game.cpp" -o Game.o
	g++ -o GAME Game.o Map.o $(SFML_LIBS)

clean:
	@echo "Removing compiled files"
	rm GAME


