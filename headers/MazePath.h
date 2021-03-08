#include "MazeNode.h"

#ifndef MAZEPATH
#define MAZEPATH
class MazePath {
    MazeNode* first_maze_node;
    MazeNode* second_maze_node;

public:
    MazePath(const MazeNode* first_maze_node, const MazeNode* second_maze_node);

    MazeNode get_first_maze_node();

    MazeNode get_second_maze_node();

    bool is_based_on(const MazeNode* MazeNode);

    double get_lenth();
};

#endif
