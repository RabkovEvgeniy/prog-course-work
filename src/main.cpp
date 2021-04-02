#include <iostream>
#include <Maze.h>
#include <SFML/Graphics.hpp>

using namespace std;

bool is_start_button_coord(sf::Vector2i coord); //координаты принадлежат стартовой кнопке

void right_mouse_released(Maze& maze,sf::Vector2i coord);

int main() {
  
  sf::Texture road,block,enter,exit,start_button; //инициализация текстур
  road.loadFromFile("img/road.png"); 
  block.loadFromFile("img/block.png");
  enter.loadFromFile("img/enter.png");
  exit.loadFromFile("img/exit.png");
  start_button.loadFromFile("img/start_button.png");
  
  sf::Sprite node,button; //инициализирую спрайты
  node.setTexture(road);
  button.setPosition(310,470);
  button.setTexture(start_button);

  Maze maze(sf::Vector2i(13,7)); //инициализация лабиринта

  sf::Vector2i mouse_position,focus_node; //координатные пары

  sf::RenderWindow window(sf::VideoMode(900, 550), "Maze", sf::Style::Titlebar|sf::Style::Close); // инициализация окна
  
  window.setVerticalSyncEnabled(true); //включения вертикальной синхранизации
  
    while (window.isOpen()) //жизненный цикл окна
    {
        sf::Event event; //TODO Вынести все обработчики в функции
        while (window.pollEvent(event))
        {  
          if (event.type == sf::Event::Closed) //обработчик закрытия окна
              window.close();

          if(event.type == sf::Event::MouseButtonReleased) //обработчик отпускания кнопки мыши
          {
            mouse_position = sf::Mouse::getPosition(window); //считываем положение мыши

            if(event.mouseButton.button == sf::Mouse::Left) // обработчик нажатия ЛКМ
            {
              focus_node = maze.transform_coord_to_indexes_of_node(mouse_position);
              
              if (focus_node!=sf::Vector2i(-1,-1) 
                  && focus_node!=maze.get_enter_node_indexes()
                  && focus_node!=maze.get_exit_node_indexes())
                maze[focus_node].switch_is_block();
              
              if (is_start_button_coord(mouse_position)) ; //TODO Дописать действия при нажатии на кнопку старт
            }

            if(event.mouseButton.button ==sf::Mouse::Right) //обработчик нажатия ПКМ
              right_mouse_released(maze,mouse_position);  
          }
        }

        mouse_position = sf::Mouse::getPosition(window); //устанавливаем фокус на ноду под мышью
        focus_node = maze.transform_coord_to_indexes_of_node(mouse_position);
        maze.set_focus_node_indexes(focus_node);
        
        window.clear(sf::Color(0,10,19)); //очищение экрана
        
        for (int i = 0; i < 13; i++) //отрисовка нод
        {
          for (int j = 0; j < 7; j++)
          {
            node.setColor(sf::Color::White); //задаем цвет по умолчанию
            node.setPosition(91 + i * 55 , 61 + j * 55); //установка позиции ноды

            if(maze.get_enter_node_indexes()==sf::Vector2i(i,j)) //определяем текстуру для очередной ноды
            {
              node.setTexture(enter); 
            }
            else if(maze.get_exit_node_indexes()==sf::Vector2i(i,j))
            {
              node.setTexture(exit);
            }
            else 
              node.setTexture(maze[sf::Vector2i(i,j)].get_is_block()?block:road);

            if(maze.get_focus_node_indexes() == sf::Vector2i(i,j)) //затемняем если в фокусе
              node.setColor(sf::Color(255,255,255,180));
            
            window.draw(node);
          }
        }

        button.setColor(sf::Color::White); //отрисовка кнопки старт
        if (is_start_button_coord(mouse_position))
          button.setColor(sf::Color(255,255,255,220)); //затемняем если в фокусе
        window.draw(button);
        
        window.display(); //отображаем отрисованное
    }
  return 0;
}

bool is_start_button_coord(sf::Vector2i coord)
{
  return (coord.x>=310 && coord.x<=580) && (coord.y >=475 && coord.y<=525);
}

void right_mouse_released(Maze& maze,sf::Vector2i coord)
{
  sf::Vector2i focus = maze.transform_coord_to_indexes_of_node(coord); //определяем какая нода под фокусом
  
  if(focus!=sf::Vector2i(-1,-1)) //если нода под фокусом
  {
    if(maze[focus].get_is_block()==false)//если нода не является преградой
    {
      if(focus!=maze.get_enter_node_indexes()&&focus!=maze.get_exit_node_indexes())// если нода под фокусом дорога
      {
        if(maze.get_enter_node_indexes()==sf::Vector2i(-1,-1)) //если вход еще не назаначен
        {
            maze.set_enter_node_indexes(focus);
        }
        else if(maze.get_exit_node_indexes()==sf::Vector2i(-1,-1)) //иначе, если не назначен выход
        {
          maze.set_exit_node_indexes(focus);
        }
      }
      else //если нода под фокусом занята, очистить
      {
        if(focus==maze.get_enter_node_indexes()) maze.set_enter_node_indexes(sf::Vector2i(-1,-1));
        if(focus==maze.get_exit_node_indexes()) maze.set_exit_node_indexes(sf::Vector2i(-1,-1));
      }
    }
  }
}