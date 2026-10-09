// maze array for the mouse to know to which direction to move to 
#pragma once 
#include "Arduino.h"

extern byte maze_arr[5][5];

//wall array : to know the wall configuratoin at each cell 
extern byte wall_arr[5][5] ; 
extern bool running ;

//east north west south convention 
enum direction {
    East = 0b0001,
    North = 0b0010, 
    West = 0b0100,
    South = 0b1000 ,
  


};
struct mouse_state{ 
    int x ; 
    int y ; 
    direction dir; 
    int x_1; 
    int y_1; 
    direction dir_1;

    mouse_state(): x{4} , y{4} , dir{North} { 

    }

};


struct m_point{ //maze point since tuple not found
int x ; 
int y; 
direction  dir; 


m_point(){ 

}
 m_point(int a , int b): x{a} , y{b}{ 

 }
 m_point(int a , int b, direction d): x{a} , y{b}, dir{d}{ 

 }

};



inline bool in_boundary(m_point point );
//rotate left algorithm 
direction rotate_dir(direction dir1 , int rotate_by);


direction inverse_dir(direction dir);

 m_point closest_neighbour_dir(mouse_state m1);
 void set_flood_fill();

 void print_array(const mouse_state& m1);
 