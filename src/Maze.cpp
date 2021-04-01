#include <Maze.h>

void Maze::Node::set_evristic_distance(double distance){
    this->evristic_distance = distance;
}

bool Maze::Pair::operator==(Maze::Pair node){
    return (this->i == node.i) && (this->j==node.j);
}

void Maze::Node::set_distance(double distance) {
    this->distance = distance;
}

void Maze::Node::set_is_wall(bool is_wall){
    this->is_wall=!is_wall;
}

double Maze::Node::get_evristic_distance(){
    return evristic_distance;
}

double Maze::Node::get_distance() {
    return distance;
}

bool Maze::Node::set_is_wall(){
    return is_wall;
}

Maze::Maze(int line, int column){
    maze = new Node*[column];
    for (int i = 0; i < column; i++)
    {
        maze[i] = new Node;
    }
}

Maze::Node* Maze::operator[](int i){
    return maze[i];
}

void Maze::set_exit_node(Maze::Pair node){
    exit_node = node;
}

bool Maze::is_exit_node(Maze::Pair node){
    return exit_node == node;
}

void Maze::set_enter_node(Maze::Pair node){
    enter_node = node;
};

bool Maze::is_enter_node(Maze::Pair node){
    return (enter_node == node);
}

void Maze::Node::set_previos(Maze::Pair previous){
    this-> Previous_node = previous;
}