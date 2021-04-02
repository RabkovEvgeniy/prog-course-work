#pragma once

#include<Maze.h>

#include<cmath>
#include<algorithm>
#include<list>

typedef pair<int,int> Coord; 

class Navigator{

    struct MapNode
    {
        int F; //полный приоритет
        int G; //путь от начала
        int H; //эвристическое приближение оставшегося пути
        Coord parent_coord; //родительский узел

        static int evristic_distance(Coord exit, Coord it); //считает эвристическое приближение

        static int distance(MapNode& parent_node,Coord parent, Coord it); //считает путь
    };

    MapNode** map;

    Coord size;

public:
    list<Coord> road;
    
    int dist;
    
    Navigator(pair<int,int> size_of_map); //создает и инициализирует карту
    
    void update_map(Maze& maze); //обновляет карту лабиринта

    void A_star(Coord enter,Coord exit); //Находит оптимальный путь от входа до выхода и сохраняет в экземляр координаты пути.

    bool is_map_coord(Coord it);

    ~Navigator(); //очищает память  
};