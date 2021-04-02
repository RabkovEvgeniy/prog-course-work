#include <iostream>
#include <Maze.h>
#include <SFML/Graphics.hpp>

using namespace std;

int main() {
  
  Maze maze(sf::Vector2i(13,7));
  sf::Texture road,block,focus,enter,exit,active;
  sf::Sprite node;
  sf::Vector2i mouse_position,focus_node;

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
                mouse_position = sf::Mouse::getPosition(window);
                  focus_node = maze.get_indexes_focus_node(mouse_position);
                  maze[focus_node].switch_is_block();
              }
            }
        }

        

        window.clear(sf::Color(0,10,19));
        
        for (int i = 0; i < 13; i++)
        {
          for (int j = 0; j < 7; j++)
          {
            node.setPosition(91 + i * 55 , 61 + j * 55);
            node.setTexture(maze[sf::Vector2i(i,j)].get_is_block()?block:road);
            window.draw(node);
          }
        }
        
        window.display();
    }
  return 0;
}


