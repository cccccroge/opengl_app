CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin

SRC		:= src
RENDER  := src/render
SCENE   := src/scene
EVENT	:= src/event
INTERNAL_DATA := src/internal_data

INCLUDE	:= include
LIB     := lib

LIBRARIES	:= -lglut -lGLEW -lGL -lX11 -lXi -lXxf86vm -lassimp -lz
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(RENDER)/*.cpp $(SCENE)/*.cpp $(EVENT)/*.cpp $(INTERNAL_DATA)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
