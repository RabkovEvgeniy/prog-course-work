#include <Maze.h>

Maze::Node::Node()
{
  is_block = false;
  is_road = false;
}

void Maze::Node::set_is_block(bool is_block)
{
  this->is_block=is_block;
}

bool Maze::Node::get_is_block()
{
  return this->is_block;
}

void Maze::Node::switch_is_block()
{
  this->is_block=!is_block;
}

void Maze::Node::set_is_road(bool is_road)
{
  this->is_road=is_road;
}

bool Maze::Node::get_is_road()
{
  return is_road;
}

Maze::Maze(sf::Vector2i size)
{
  this->size = size;

  maze = new Node*[size.x];
  for (int i = 0; i < size.x; i++)
  {
      maze[i] = new Node[size.y];
  }  

  this->focus_node_indexes = sf::Vector2i(-1,-1);
  this->exit_node_indexes = sf::Vector2i(-1,-1);
  this->enter_node_indexes = sf::Vector2i(-1,-1);
}

void Maze::clear()
{
  for (int i = 0; i < size.x; i++)
  {
    for (int j = 0; j < size.y; j++)
    {
      maze[i][j].set_is_block(false);
      maze[i][j].set_is_road(false);
    }
    
  }
  
  this->focus_node_indexes = sf::Vector2i(-1,-1);
  this->exit_node_indexes = sf::Vector2i(-1,-1);
  this->enter_node_indexes = sf::Vector2i(-1,-1);
}

Maze::Node& Maze::operator[](sf::Vector2i indexes)
{
  return maze[indexes.x][indexes.y];
}

void Maze::set_exit_node_indexes(sf::Vector2i exit_node_indexes)
{
  this->exit_node_indexes = exit_node_indexes;
}

sf::Vector2i Maze::get_exit_node_indexes()
{
  return exit_node_indexes;
}

void Maze::set_enter_node_indexes(sf::Vector2i enter_node_indexes)
{
  this->enter_node_indexes = enter_node_indexes;
}

sf::Vector2i Maze::get_enter_node_indexes()
{
  return this->enter_node_indexes;
}

void Maze::set_focus_node_indexes(sf::Vector2i indexes)
{
  this->focus_node_indexes=indexes;
}

sf::Vector2i Maze::get_focus_node_indexes()
{
  return this->focus_node_indexes;
}

sf::Vector2i Maze::get_size()
{
  return size;
}

sf::Vector2i Maze::transform_coord_to_indexes_of_node(sf::Vector2i pos)
{
  int i,j;
  pos.x-=90;
  pos.y-=60;

  if (pos.x<0||pos.y<0) return sf::Vector2i(-1,-1);

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

  if(i==size.x||j==size.y) return sf::Vector2i(-1,-1);
  return sf::Vector2i(i,j);
}

Maze::~Maze()
{ 
    for (int i = 0; i < size.x; i++)
    {
        delete[] maze[i];
    }
    delete[] maze;
}