clean:
	rm -f objectfile/*.o
	rm -f headers/*.gch

main.o:sourses/main.cpp
	g++ -c sourses/main.cpp -o objectfile/main.o

app.out:main.o
	g++ objectfile/main.o -o app.out -lsfml-graphics -lsfml-window -lsfml-system

MazeNode.o:sourses/MazeNode.cpp
	g++ -c sourses/MazeNode.cpp -o objectfile/MazeNode.o
