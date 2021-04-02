#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Maze{
public:

    class Node{
        double evristic_distance; //Расстояние до выхода
        
        double distance; //Кратчайшая известная длинна пути от входа до ноды

        bool is_block; //Является ли нода преградой?

        sf::Vector2i previous_node_indexes;//индексы ноды, из которой идет кратчайший известный маршрут до ноды 
    public:
        Node();

        void set_evristic_distance(double distance); //Установить значение эвристического расстояния
        
        void set_distance(double distance); //Установить значение расстояния от входа до ноды

        void set_is_block(bool is_block); //Установить

        double get_evristic_distance();
        
        double get_distance();

        bool get_is_block();

        void switch_is_block();

        void set_previos_node_indexes(sf::Vector2i previous_node_indexes);
    };

    Maze(sf::Vector2i);

    Node& operator[](sf::Vector2i indexes); //Возвращает ссылку на ноду по индексам

    void set_exit_node_indexes(sf::Vector2i node);

    sf::Vector2i get_exit_node_indexes(); 

    void set_enter_node(sf::Vector2i node);

    sf::Vector2i get_enter_node_indexes();

    sf::Vector2i get_indexes_focus_node(sf::Vector2i pos);

    ~Maze();
private:
    
    Node** maze;

    sf::Vector2i enter_node_indexes;

    sf::Vector2i exit_node_indexes;

    sf::Vector2i active_node_indexes;

    sf::Vector2i focus_node_indexes;

    sf::Vector2i size;
};