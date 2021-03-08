#ifndef MAZE_NODE
#define MAZE_NODE

//Развилка, поворот, узел на который опираются пути лабиринта.
class MazeNode {
    int x;
    int y;

public:
    MazeNode(int x, int y);

    int get_x();
    int get_y();
};

#endif
