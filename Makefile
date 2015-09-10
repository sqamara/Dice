all:
	g++ -o game dice.cpp
	g++ -o analyzer roll_analyzer.cpp

analyzer:
	g++ -o analyzer roll_analyzer.cpp
	./analyzer

game:
	g++ -o game dice.cpp
	./game

clean:
	rm game analyzer
