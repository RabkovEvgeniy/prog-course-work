#include <Node.h>

void Node::set_evristic_distance(double distance){
    this->evristic_distance = distance;
}

void Node::set_distance(double distance) {
    this->distance = distance;
}

void Node::set_is_wall(bool is_wall){
    this->is_wall=!is_wall;
}

double Node::get_evristic_distance(){
    return evristic_distance;
}

double Node::get_distance() {
    return distance;
}

bool Node::set_is_wall(){
    return is_wall;
}

