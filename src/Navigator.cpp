#include <Navigator.h>

int Navigator::MapNode::evristic_distance(Coord exit, Coord it){
    return sqrt(pow(exit.first-it.first,2)+pow(exit.second-it.second,2))*10;
}

int Navigator::MapNode::distance(MapNode& parent_node, Coord parent, Coord it){ //TODO Найти причину не срезания углов.
    return (abs(parent.first-it.first)+abs(parent.second-it.second))==2?14:10;
}

Navigator::Navigator(Coord size_of_map)
{    
    map = new MapNode*[size_of_map.first];
    
    for (int i = 0; i < size_of_map.first; i++)
    {
        map[i] = new MapNode[size_of_map.second];
    }

    for (int i = 0; i < size.first; i++)
    {
        for (int j = 0; j < size.second; j++)
        {
            map[i][j].F = -1;
            map[i][j].G = 0;
            map[i][j].H = 0;
            map[i][j].parent_coord = Coord(0,0);
        }
    }
    
    size = size_of_map;
}

void Navigator::update_map(Maze& maze)
{
    for (int i = 0; i < size.first; i++)
    {
        for (int j = 0; j < size.second; j++)
        {
            if(maze[sf::Vector2i(i,j)].get_is_block())
                map[i][j].F = -1;
            else map[i][j].F = 0;
        }
    }
    road.clear();
}

void Navigator::A_star(Coord enter,Coord exit)
{
    Coord temp;

    int temp_G,temp_F;
    
    list<Coord> CL; //список закрытых клеток
    list<Coord> OL; //список открытых клеток
    
    list<Coord>::iterator min_it;
    list<Coord>::iterator active;

    bool exit_in_CL=0;
    bool OL_is_empty=0;
    
    OL.push_front(enter); //добавляю стартовую клетку в открытый список
    map[enter.first][enter.second].G=0;
    map[enter.first][enter.second].H=Navigator::MapNode::evristic_distance(exit,enter);
    map[enter.first][enter.second].F=map[enter.first][enter.second].G+map[enter.first][enter.second].H;

    do{

        min_it = OL.begin(); //нахожу минимальную по F клетку из OL
        for (auto it = OL.begin(); it != OL.end(); ++it)
        {
            if(map[(*it).first][(*it).second].F< map[(*min_it).first][(*min_it).second].F)
                min_it = it;
        }
        
        CL.push_front(*min_it); //перенос найденного элемента в CL
        OL.erase(min_it);

        active=CL.begin();

        temp = *active; //обработка смежных клеток
        
        temp.second--;
        if(this->is_map_coord(temp)&&map[temp.first][temp.second].F != -1)
        {
            if (std::find(CL.begin(),CL.end(),temp) == CL.end())
            {
                if(std::find(OL.begin(),OL.end(),temp) == OL.end())
                {
                    OL.push_front(temp);
                    map[temp.first][temp.second].parent_coord=*active;
                    map[temp.first][temp.second].G=Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
                    map[temp.first][temp.second].H=Navigator::MapNode::evristic_distance(exit,temp);
                    map[temp.first][temp.second].F=map[temp.first][temp.second].G+map[temp.first][temp.second].H;
                }
                else
                {
                    temp_G = Navigator::MapNode::distance(map[(*active).first][(*active).second],*active,temp);
                    temp_F = temp_G + map[temp.first][temp.second].H;
                    if (map[temp.first][temp.second].G>temp_G)
                    {
                        map[temp.first][temp.second].parent_coord = *active;
                        map[temp.first][temp.second].G = temp_G;
                        map[temp.first][temp.second].F = temp_F;
                    }
                }
            }
        }
        temp = *active;

        // temp.first--;
        // temp.second--;
        // if(this->is_map_coord(temp)&&map[temp.first][temp.second].F != -1)
        // {
        //     if (std::find(CL.begin(),CL.end(),temp) == CL.end())
        //     {
        //         if(std::find(OL.begin(),OL.end(),temp) == OL.end())
        //         {
        //             OL.push_front(temp);
        //             map[temp.first][temp.second].parent_coord=*active;
        //             map[temp.first][temp.second].G=Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
        //             map[temp.first][temp.second].H=Navigator::MapNode::evristic_distance(exit,temp);
        //             map[temp.first][temp.second].F=map[temp.first][temp.second].G+map[temp.first][temp.second].H;
        //         }
        //         else
        //         {
        //             temp_G = Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
        //             temp_F = temp_G + map[temp.first][temp.second].H;
        //             if (map[temp.first][temp.second].G>temp_G)
        //             {
        //                 map[temp.first][temp.second].parent_coord = *active;
        //                 map[temp.first][temp.second].G = temp_G;
        //                 map[temp.first][temp.second].F = temp_F;
        //             }
        //         }
        //     }
        // }
        // temp = *active;

        temp.first--;
        if(this->is_map_coord(temp)&&map[temp.first][temp.second].F != -1)
        {
            if (std::find(CL.begin(),CL.end(),temp) == CL.end())
            {
                if(std::find(OL.begin(),OL.end(),temp) == OL.end())
                {
                    OL.push_front(temp);
                    map[temp.first][temp.second].parent_coord=*active;
                    map[temp.first][temp.second].G=Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
                    map[temp.first][temp.second].H=Navigator::MapNode::evristic_distance(exit,temp);
                    map[temp.first][temp.second].F=map[temp.first][temp.second].G+map[temp.first][temp.second].H;
                }
                else
                {
                    temp_G = Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
                    temp_F = temp_G + map[temp.first][temp.second].H;
                    if (map[temp.first][temp.second].G>temp_G)
                    {
                        map[temp.first][temp.second].parent_coord = *active;
                        map[temp.first][temp.second].G = temp_G;
                        map[temp.first][temp.second].F = temp_F;
                    }
                }
            }
        }
        temp = *active;

        // temp.first--;
        // temp.second++;
        // if(this->is_map_coord(temp)&&map[temp.first][temp.second].F != -1)
        // {
        //     if (std::find(CL.begin(),CL.end(),temp) == CL.end())
        //     {
        //         if(std::find(OL.begin(),OL.end(),temp) == OL.end())
        //         {
        //             OL.push_front(temp);
        //             map[temp.first][temp.second].parent_coord=*active;
        //             map[temp.first][temp.second].G=Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
        //             map[temp.first][temp.second].H=Navigator::MapNode::evristic_distance(exit,temp);
        //             map[temp.first][temp.second].F=map[temp.first][temp.second].G+map[temp.first][temp.second].H;
        //         }
        //         else
        //         {
        //             temp_G = Navigator::MapNode::distance(map[(*active).first][(*active).second],*active,temp);
        //             temp_F = temp_G + map[temp.first][temp.second].H;
        //             if (map[temp.first][temp.second].G>temp_G)
        //             {
        //                 map[temp.first][temp.second].parent_coord = *active;
        //                 map[temp.first][temp.second].G = temp_G;
        //                 map[temp.first][temp.second].F = temp_F;
        //             }
        //         }
        //     }
        // }
        // temp = *active;

        temp.second++;
        if(this->is_map_coord(temp)&&map[temp.first][temp.second].F != -1)
        {
            if (std::find(CL.begin(),CL.end(),temp) == CL.end())
            {
                if(std::find(OL.begin(),OL.end(),temp) == OL.end())
                {
                    OL.push_front(temp);
                    map[temp.first][temp.second].parent_coord=*active;
                    map[temp.first][temp.second].G=Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
                    map[temp.first][temp.second].H=Navigator::MapNode::evristic_distance(exit,temp);
                    map[temp.first][temp.second].F=map[temp.first][temp.second].G+map[temp.first][temp.second].H;
                }
                else
                {
                    temp_G = Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
                    temp_F = temp_G + map[temp.first][temp.second].H;
                    if (map[temp.first][temp.second].G>temp_G)
                    {
                        map[temp.first][temp.second].parent_coord = *active;
                        map[temp.first][temp.second].G = temp_G;
                        map[temp.first][temp.second].F = temp_F;
                    }
                }
            }
        }
        temp = *active;

        // temp.first++;
        // temp.second++;
        // if(this->is_map_coord(temp)&&map[temp.first][temp.second].F != -1)
        // {
        //     if (std::find(CL.begin(),CL.end(),temp) == CL.end())
        //     {
        //         if(std::find(OL.begin(),OL.end(),temp) == OL.end())
        //         {
        //             OL.push_front(temp);
        //             map[temp.first][temp.second].parent_coord=*active;
        //             map[temp.first][temp.second].G=Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
        //             map[temp.first][temp.second].H=Navigator::MapNode::evristic_distance(exit,temp);
        //             map[temp.first][temp.second].F=map[temp.first][temp.second].G+map[temp.first][temp.second].H;
        //         }
        //         else
        //         {
        //             temp_G = Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
        //             temp_F = temp_G + map[temp.first][temp.second].H;
        //             if (map[temp.first][temp.second].G>temp_G)
        //             {
        //                 map[temp.first][temp.second].parent_coord = *active;
        //                 map[temp.first][temp.second].G = temp_G;
        //                 map[temp.first][temp.second].F = temp_F;
        //             }
        //         }
        //     }
        // }
        // temp = *active;

        temp.first++;
        if(this->is_map_coord(temp)&&map[temp.first][temp.second].F != -1)
        {
            if (std::find(CL.begin(),CL.end(),temp) == CL.end())
            {
                if(std::find(OL.begin(),OL.end(),temp) == OL.end())
                {
                    OL.push_front(temp);
                    map[temp.first][temp.second].parent_coord=*active;
                    map[temp.first][temp.second].G=Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
                    map[temp.first][temp.second].H=Navigator::MapNode::evristic_distance(exit,temp);
                    map[temp.first][temp.second].F=map[temp.first][temp.second].G+map[temp.first][temp.second].H;
                }
                else
                {
                    temp_G = Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
                    temp_F = temp_G + map[temp.first][temp.second].H;
                    if (map[temp.first][temp.second].G>temp_G)
                    {
                        map[temp.first][temp.second].parent_coord = *active;
                        map[temp.first][temp.second].G = temp_G;
                        map[temp.first][temp.second].F = temp_F;
                    }
                }
            }
        }
        temp = *active;

        // temp.first++;
        // temp.second--;
        // if(this->is_map_coord(temp)&&map[temp.first][temp.second].F != -1)
        // {
        //     if (std::find(CL.begin(),CL.end(),temp) == CL.end())
        //     {
        //         if(std::find(OL.begin(),OL.end(),temp) == OL.end())
        //         {
        //             OL.push_front(temp);
        //             map[temp.first][temp.second].parent_coord=*active;
        //             map[temp.first][temp.second].G=Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
        //             map[temp.first][temp.second].H=Navigator::MapNode::evristic_distance(exit,temp);
        //             map[temp.first][temp.second].F=map[temp.first][temp.second].G+map[temp.first][temp.second].H;
        //         }
        //         else
        //         {
        //             temp_G = Navigator::MapNode::distance(map[(*active).first][(*active).second], *active,temp);
        //             temp_F = temp_G + map[temp.first][temp.second].H;
        //             if (map[temp.first][temp.second].G>temp_G)
        //             {
        //                 map[temp.first][temp.second].parent_coord = *active;
        //                 map[temp.first][temp.second].G = temp_G;
        //                 map[temp.first][temp.second].F = temp_F;
        //             }
        //         }
        //     }
        // }
        // temp = *active;

        exit_in_CL = (std::find(CL.begin(),CL.end(),exit) != CL.end());
        OL_is_empty = OL.size() == 0;

    }while(!(OL_is_empty||exit_in_CL));
    
    if(exit_in_CL)
    {
        dist = map[exit.first][exit.second].G;
        road.clear();
        temp = map[exit.first][exit.second].parent_coord;
        while (temp!=enter)
        {
            road.push_front(temp);
            temp = map[temp.first][temp.second].parent_coord;
        }
    }
}

bool Navigator::is_map_coord(Coord it){
    return (it.first >= 0 && it.first < size.first) && (it.second >= 0 && it.second < size.second);
}

Navigator::~Navigator()
{
    for (int i = 0; i < size.first; i++)
    {
        delete[] map[i];
    }

    delete[] map;
}