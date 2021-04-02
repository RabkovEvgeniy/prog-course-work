#pragma once

#include <SFML/Graphics.hpp>

#include <string>

using namespace std;

class Maze{
public:

    class Node{

        bool is_block; //является ли нода преградой?

        bool is_road; //является ли нода оптимальным путем?

    public:
        Node();

        void set_is_block(bool is_block); //уставливает, является ли нода преградой

        bool get_is_block(); //узнает, является ли нода преградой

        void switch_is_block(); //переключает состояние преграда\проход на противоположное
        
        void set_is_road(bool is_road);  //устанавливает, является ли нода оптимальным путем

        bool get_is_road(); //узнает, является ли нода оптимальным путем
    };

    Maze(sf::Vector2i); // конструктор, создающий массив нод x на y

    void clear();

    Node& operator[](sf::Vector2i indexes); //возвращает ссылку на ноду по индексам

    void set_exit_node_indexes(sf::Vector2i node); //устанавливает координаты выхода

    sf::Vector2i get_exit_node_indexes();  //возвращает координаты выхода

    void set_enter_node_indexes(sf::Vector2i node); //устанавливает координаты входа

    sf::Vector2i get_enter_node_indexes(); //возвращает координаты входы  

    void set_focus_node_indexes(sf::Vector2i indexes); //устанавливает координаты фокусной ноды

    sf::Vector2i get_focus_node_indexes(); //возвращает координаты фокусной ноды

    sf::Vector2i get_size(); //возвращает размер

    sf::Vector2i transform_coord_to_indexes_of_node(sf::Vector2i pos); //преобразует координаты в индексы нод

    ~Maze(); //очищает память

private:
    
    Node** maze; //указатель на двумерный дин. массив

    sf::Vector2i enter_node_indexes; //индексы ноды входа

    sf::Vector2i exit_node_indexes; //индексы ноды выхода

    sf::Vector2i focus_node_indexes; //индексы фокусной ноды

    sf::Vector2i size; //размер лабиринта
};