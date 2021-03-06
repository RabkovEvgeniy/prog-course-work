clean:
	rm *.o

main.o:sourses/main.cpp
	g++ -c sourses/main.cpp

app.out:main.o
	g++ main.o -o app.out -lsfml-graphics -lsfml-window -lsfml-system
