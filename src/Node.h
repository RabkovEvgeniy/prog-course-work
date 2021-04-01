class Node{
    double evristic_distance;
    double distance;
    bool is_wall; 
public:
    void set_evristic_distance(double distance);
    
    void set_distance(double distance);

    void set_is_wall(bool is_wall);

    double get_evristic_distance();
    
    double get_distance();

    bool set_is_wall();


};