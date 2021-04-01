#include <Maze.h>
#include <SFML/Graphics.hpp>

using namespace std;

int main() {
  Maze maze(13,7);
  sf::Texture road,block;
  road.loadFromFile("img/road.png");
  block.loadFromFile("img/block.png");
  sf::Sprite node;
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
