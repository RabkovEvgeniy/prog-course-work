class Maze{
public:
    struct Pair
    {
        int i;
        int j;

        bool operator==(Pair node);
    };

    class Node{
        double evristic_distance;
        
        double distance;

        bool is_wall; 

        Pair Previous_node;
    public:
        void set_evristic_distance(double distance);
        
        void set_distance(double distance);

        void set_is_wall(bool is_wall);

        double get_evristic_distance();
        
        double get_distance();

        bool set_is_wall();

        void set_previos(Pair previos);
    };

    Maze(int line, int column);

    Node* operator[](int i);

    void set_exit_node(Pair node);

    bool is_exit_node(Pair node);

    void set_enter_node(Pair node);

    bool is_enter_node(Pair node);

    ~Maze();
private:
    
    Node** maze;

    Pair enter_node;

    Pair exit_node;

    Pair active_node;
};