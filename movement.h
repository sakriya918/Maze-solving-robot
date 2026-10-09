#pragma once 
#include "Arduino.h"
#include "flood_fill.hpp"
#include "NewPing.h"
// #define left 5   //deprecated shit for ir sensor
// #define front 6 
// #define right 4
//#define UTB(num)  sonar##num.ping_cm() < 5 ? EXIST : DE//ultrasonic data to binary 
//for sonar 1 front
#define TRIGGER_PIN_1 7
#define ECHO_PIN_1 6
//for sonar 2 left
#define TRIGGER_PIN_2 11
#define ECHO_PIN_2 10
//for sonar 3 right
#define TRIGGER_PIN_3 8 
#define ECHO_PIN_3 9

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400	
#define TH_USG 8

// NewPing setup of pins and maximum distance.

extern NewPing sonar1;

extern NewPing sonar2;

extern NewPing sonar3;


enum wall_state{ 
  EXIST = 0b1, 
  DE = 0b0,
};
extern wall_state wall_state_front; 
extern wall_state wall_state_left; 
extern wall_state wall_state_right; 
void wall_array_change(const mouse_state& m1);
void move (mouse_state &m1);

