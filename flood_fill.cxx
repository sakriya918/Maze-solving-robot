
#include<ArduinoQueue.h>



#include "flood_fill.hpp"
//east north west south convention 
//check for the array 


//visted array : at each interation to know if the cell is already visited 
//visited array must be cleared at each iteration 
bool visted[5][5];// this visited thingy should be made 0 in the start of every iteration !!!not done !! do in .ino file

 byte maze_arr[5][5] = {0};
 byte wall_arr[5][5] = {0};
bool running = true; 



 


//actual flood fill array for the mouse in alpha version 
void set_flood_fill() {
        
        memset(visted, 0 , 5 * 5 *sizeof(visted[0][0]));
        memset(maze_arr, 0 , 5 * 5 *sizeof(maze_arr[0][0]));

        
        
        // wall_arr[4][0] = 0b1101;
        // wall_arr[3][0] = 0b0101;
        //  wall_arr[2][0] = 0b0110;
        //   wall_arr[3][1] = 0b0101;
        // wall_arr[2][1] = 0b0001;

     

        ArduinoQueue<m_point> q(20);
        m_point point(2, 2); 
        q.enqueue(point); 
        while ( !q.isEmpty()){
            m_point temp = q.dequeue();
            
            int a = temp.x , b= temp.y; 
        

            if ( !visted[a][b] && in_boundary(temp) ){// for the cell that is being processed
                visted[a][b] = 1; // if cell is processed it is visitedd
                 m_point point_arr[4] ={m_point(a, b-1, West) , m_point(a , b+1 ,East), m_point(a-1, b,North), m_point(a+1, b, South)}; //cells in 4 direction of the cell begin processed
                 for ( auto elem : point_arr){ //possible optimization ? dont know 
                    if ( in_boundary(elem) && !visted[elem.x][elem.y]){ // are the cells around the cell begin processed in boundary and not already processed 
                        if ( !((wall_arr[a][b] & elem.dir) || (wall_arr[elem.x][elem.y] & inverse_dir(elem.dir))) ) {// & and && are different things , to check if the point has walls or not to insert into the queue
                        maze_arr[elem.x][elem.y] = (maze_arr[a][b] + 1);//increment the value
                        q.enqueue(elem); // push into the queue for processing 
                           
                        }
                    }
                 } 

            }
          
        }
}
//finding the direction to which the mouse will move 
 m_point closest_neighbour_dir(mouse_state m1){
     int a = m1.x , b = m1.y ; 
     
     m_point point_arr[4] ={m_point(a, b-1, West) , m_point(a , b+1 ,East), m_point(a-1, b,North), m_point(a+1, b, South)};
     m_point point_arr1[4];
     int c = 0 ; // c is the new count for the array 
     //disqualification loop 
     for(int i = 0 ; i< 4 ; i++){ 
        
        if( (in_boundary(point_arr[i]) && !((point_arr[i].dir & wall_arr[a][b]) || (inverse_dir(point_arr[i].dir) & wall_arr[point_arr[i].x][point_arr[i].y] )))){//to only select cubes  which are inside boundary and has no wall  
            //smallest = point_arr[i]
            //the whole thing can be done in this rather than in two loops but not checked 
            //  if (  maze_arr[smallest.x][smallest.y] > maze_arr[point_arr1[i].x][point_arr1[i].y] ){ 
            // smallest = point_arr1[i]; 

            // } 

            point_arr1[c] = point_arr[i] ;
            c++;
        }
        
        
     }
     // no solution condition 
     if (c == 0 || (maze_arr[m1.x][m1.y] == 0 && m1.x != 2 && m1.y!=2)) { // no direction to move to from above loop and the value given by the flood fill is 0 in value other than (2,2)
      
      running = false; 
      Serial.print("no solution end"); 
      Serial.println(); 
      return m_point(m1.x , m1.y , m1.dir);
     }
     // for finding smallest 
     m_point smallest = point_arr1[0]; 
     for( int i = 1 ; i < c ; i ++){ 
        if (  maze_arr[smallest.x][smallest.y] > maze_arr[point_arr1[i].x][point_arr1[i].y] ){ 
            smallest = point_arr1[i]; 

        }
     }

    return smallest; 
 }
//utility functions 
// for checking if the point is inside the boundary or not 
inline bool in_boundary(m_point point ) { 
    return point.x >= 0 && point.x <= 4  &&  point.y >= 0 && point.y <= 4 ;
}


//rotate left algorithm 
direction rotate_dir(direction dir1 , int rotate_by){ 
   return (direction)((dir1 << rotate_by) | ( dir1 >> (4 - rotate_by)));

}


// to invert the direction of mouse 
direction inverse_dir(direction dir){ 
  return  rotate_dir(dir , 2 ); 
 } 
 //helper function to print direction enum
 void printDir(direction dir)
{
  switch (dir) { 
    case East:
      Serial.print("East");
      break;
    case West:
      Serial.print("West");
      break;
    case North:
      Serial.print("North");
      break;
    case South:
      Serial.print("South");
      break;
    default: 
      Serial.print("error");
  }
  
}


 //helper function for the print function 
 void printBinary(byte inByte)
{
  for (int b = 7; b >= 0; b--)
  {
    Serial.print(bitRead(inByte, b));
  }
}

// function to debug and print the array 
 void print_array(const mouse_state &m1 ){
   for(int i = 0 ; i <5 ; i++){ 
    for ( int j = 0 ; j < 5; j ++ ){ 
      printBinary(wall_arr[i][j]);
      Serial.print('\t');
      Serial.print( maze_arr[i][j]);
      Serial.print('\t');
      


    }
     Serial.print( "\n");
    }
     Serial.print(m1.x);
      Serial.print(",");
      Serial.print(m1.y);
       Serial.println();
       printDir(m1.dir);
       Serial.println();

    
   
   Serial.print("--------------------------------------------------------------");
  Serial.print( "\n");

   
}


