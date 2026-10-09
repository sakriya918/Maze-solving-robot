
#include "movement.h"

NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE);






void wall_array_change(const mouse_state& m1) {
    
  delay(2500);
    //Serial.print()
    int distance_temp1 = sonar1.ping_cm();
    int distance_temp2 = sonar2.ping_cm();
    int distance_temp3 = sonar3.ping_cm();

   wall_state wall_state_front = (distance_temp1 < TH_USG? EXIST : DE); 
    wall_state wall_state_left = (distance_temp2 < TH_USG? EXIST : DE); 
    wall_state wall_state_right = (distance_temp3 < TH_USG? EXIST : DE);
  Serial.print("front:");
  Serial.print(distance_temp1);
  Serial.print("\t-----");
  Serial.print("left:");
  Serial.print(distance_temp2);
  Serial.print("\t-----");
  Serial.print("right:");
  Serial.print(distance_temp3);
  Serial.print("\t-----");
  Serial.print("\n");
  


    if (wall_state_front == EXIST){
        wall_arr[m1.x][m1.y] |= m1.dir ;
        wall_arr[m1.x][m1.y] &= 0b00001111;

    }
     if (wall_state_left  == EXIST ){
        wall_arr[m1.x][m1.y] |= rotate_dir(m1.dir, 1) ;
         wall_arr[m1.x][m1.y] &= 0b00001111;
    }
     if (wall_state_right == EXIST){
        wall_arr[m1.x][m1.y] |= rotate_dir(m1.dir, 3) ;
         wall_arr[m1.x][m1.y] &= 0b00001111;
    }

}
void move (mouse_state &m1) { 
  // for destination condition 
    if (m1.x == 2 && m1.y == 2){
      Serial.print("end");
      running = false; 
    }
    // then we get the cell to move to and the closest neighbour 
    m_point to_move= closest_neighbour_dir(m1);
    //movement shit that is not written yet 
    delay(5000);

    //change the mousetate according to the movement ? 
    
    //by this point the mouse must have already moved and changed the direction in the micromouse maze ( real world )
     m1.x = to_move.x , m1.y = to_move.y ;   
     m1.dir = to_move.dir ;
     
// mouse state ko directin xa tyo ra arko direction ie ( closesdt neightbour bata aako ) teslai compute garera new movemnt ie (turn ) nikalne 
// ani tyo direction ma 1 unit le move garne jun naya set vako xa
    

}



