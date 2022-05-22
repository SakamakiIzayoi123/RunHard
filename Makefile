# This is makefile for SFML C++

path = C:\SFML-2.5.1
INCLUDE = "$(path)\include"
LIBRARY = "$(path)\lib"
CXXFLAGS =
SFMLFLAGS =
SOURCE = main
SFML_INCLUDE = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#=======================================================================================#

all: compile link
compile:
	g++ -c $(SOURCE).cpp -I $(INCLUDE)
link:
	g++ $(CXXFLAGS) $(SOURCE).o -o main -L $(LIBRARY) $(SFMLFLAGS) $(SFML_INCLUDE)