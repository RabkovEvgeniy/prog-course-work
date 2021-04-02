#include <Maze.h>

Maze::Node::Node(){is_block = false;}

void Maze::Node::set_evristic_distance(double distance){this->evristic_distance = distance;}

void Maze::Node::set_distance(double distance) {this->distance = distance;}

double Maze::Node::get_distance() {return this->distance;}

void Maze::Node::set_is_block(bool is_block){this->is_block=is_block;}

void Maze::Node::switch_is_block(){this->is_block=!is_block;}

bool Maze::Node::get_is_block(){return this->is_block;}

double Maze::Node::get_evristic_distance(){return this->evristic_distance;}

Maze::Maze(sf::Vector2i size){
    this->size = size;

    maze = new Node*[size.x];
    for (int i = 0; i < size.x; i++)
    {
        maze[i] = new Node[size.y];
    }  
}

Maze::Node& Maze::operator[](sf::Vector2i indexes){return maze[indexes.x][indexes.y];}

void Maze::set_exit_node_indexes(sf::Vector2i exit_node){this->exit_node_indexes = exit_node_indexes;}

sf::Vector2i Maze::get_exit_node_indexes(){return exit_node_indexes;}

void Maze::set_enter_node(sf::Vector2i enter_node_indexes){this->enter_node_indexes = enter_node_indexes;}

sf::Vector2i Maze::get_enter_node_indexes(){return this->enter_node_indexes;}

void Maze::Node::set_previos_node_indexes(sf::Vector2i previous_node_indexes){this->previous_node_indexes = previous_node_indexes;}

Maze::~Maze(){ 
    for (int i = 0; i < size.x; i++)
    {
        delete[] maze[i];
    }
    delete[] maze;
}

sf::Vector2i Maze::get_indexes_focus_node(sf::Vector2i pos){
  int i,j;
  pos.x-=90;
  pos.y-=60;
  for (i = 0; i <= size.x; i++)
  {
    pos.x-=55;
    if (pos.x<0) break;
  }
  for (j = 0; j <= size.y; j++)
  {
    pos.y-=55;
    if (pos.y<0) break;
  }
  if(i==size.x||j==size.y) return sf::Vector2i(0,0);
  return sf::Vector2i(i,j);
}