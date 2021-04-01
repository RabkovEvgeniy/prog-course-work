#include <iostream>
#include <Maze.h>
#include <SFML/Graphics.hpp>

using namespace std;

sf::Vector2i coord_to_i_j(sf::Vector2i pos);

int main() {
  
  sf::Vector2i active;
  Maze maze(7,13);
  sf::Texture road,block;
  sf::Sprite node;

  road.loadFromFile("img/road.png");
  block.loadFromFile("img/block.png");

  node.setTexture(road);
  
  sf::RenderWindow window(sf::VideoMode(900, 600), "Maze", sf::Style::Titlebar|sf::Style::Close);
  window.setVerticalSyncEnabled(true);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonReleased)
            {
              if(event.mouseButton.button == sf::Mouse::Left){
                active = sf::Mouse::getPosition(window);
                if(active.x > 90 && active.x < 856 && active.y > 60 && active.y < 495){
                  active = coord_to_i_j(active);
                  maze[active.x][active.y].set_is_wall(!maze[active.x][active.y].get_is_wall());
                }
              }
            }
        }

        

        window.clear(sf::Color(0,10,19));
        
        for (int i = 0; i < 7; i++)
        {
          for (int j = 0; j < 13; j++)
          {
            node.setPosition(91+j*55,61 + i*55);
            node.setTexture(maze[i][j].get_is_wall()?block:road);
            window.draw(node);
          }
        }
        
        window.display();
    }
  return 0;
}

sf::Vector2i coord_to_i_j(sf::Vector2i pos){
  int i,j;
  pos.x-=90;
  pos.y-=60;
  for (i = 0; i < 13; i++)
  {
    pos.x-=55;
    if (pos.x<0) break;
  }
  for (j = 0; j < 7; j++)
  {
    pos.y-=55;
    if (pos.y<0) break;
  }
  return sf::Vector2i(j,i);
}
