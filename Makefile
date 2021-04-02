CC = g++
PH = src
CFlag = -Wall -I $(PH) $(SFML) -MMD
PObj = obj/
PSrc = src/
PBin = bin/
Exec = out
SFML = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all clean

all: $(PBin)app.$(Exec)

$(PBin)app.$(Exec):$(PObj)main.o $(PObj)Maze.o 
	$(CC) $^ -o $@ $(SFML)

$(PObj)%.o:$(PSrc)%.cpp
	$(CC) -c $< -o $@ $(CFlag)

clean:
	rm -rf obj/*
	rm -rf bin/*

-include $(PObj)main.d $(PObj)Maze.d
