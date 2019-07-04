#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/position_sensor.h>
#include <webots/distance_sensor.h>
#include <webots/keyboard.h>

#include <stdio.h>
#include <math.h>


/*
 * Macros
 */
#define TIME_STEP 64
#define PI 3.14159

#define OBSTACLE_DISTANCE 40.0


/*
 * Global variables
 */


 //variable
   int counter=0;
   int count=1;
   
   int counter_left=0;
/*
 * Auxiliar functions
 */
 float velocity = 3;
 float angle;
 float angle2;


//Motion of the robot

void goRobot(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], -velocity);
  wb_motor_set_velocity(wheels[1], velocity);
  wb_motor_set_velocity(wheels[2], 0);
}

void stopRobot(WbDeviceTag *wheels) {
  wb_motor_set_velocity(wheels[0], 0);
  wb_motor_set_velocity(wheels[1], 0);
  wb_motor_set_velocity(wheels[2], 0);
}

void turnRight(WbDeviceTag *wheels) {

  wb_motor_set_velocity(wheels[0], 3);
  wb_motor_set_velocity(wheels[1], 3);
  wb_motor_set_velocity(wheels[2], 3);
}
void turnLeft(WbDeviceTag *wheels) {
  
  wb_motor_set_velocity(wheels[0], -3);
  wb_motor_set_velocity(wheels[1], -3);
  wb_motor_set_velocity(wheels[2], -3);
}
void turnDown(WbDeviceTag *wheels) {
  
  wb_motor_set_velocity(wheels[0], 3);
  wb_motor_set_velocity(wheels[1], -3);
   wb_motor_set_velocity(wheels[2], 0);
}



/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv)
{
  /* necessary to initialize webots stuff */
  wb_robot_init();

  //robot1_init()

  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
   
  // Motor devices
   WbDeviceTag wheel_left = wb_robot_get_device("wheel1");
   WbDeviceTag wheel_right = wb_robot_get_device("wheel2");
   WbDeviceTag wheel_front = wb_robot_get_device("wheel3");
   
   WbDeviceTag wheels[3];
   wheels[0] = wheel_right;
   wheels[1] = wheel_left;
   wheels[2] = wheel_front;

   wb_motor_set_position(wheel_right, INFINITY);
   wb_motor_set_position(wheel_left, INFINITY);
   wb_motor_set_position(wheel_front, INFINITY);
   
   
   //sensor devices
   
   WbDeviceTag dist_sensor_right = wb_robot_get_device("distance_sensor_right");
   WbDeviceTag dist_sensor_left = wb_robot_get_device("distance_sensor_left");
   
   wb_distance_sensor_enable(dist_sensor_right, TIME_STEP);
   wb_distance_sensor_enable(dist_sensor_left, TIME_STEP);
   
   double ds_value_right;
   double ds_value_left;
   
   //Sensor position devices
  WbDeviceTag encoder = wb_robot_get_device("encoder_left");
  wb_position_sensor_enable(encoder, TIME_STEP);
  
  WbDeviceTag encoder2 = wb_robot_get_device("encoder_right");
  wb_position_sensor_enable(encoder2, TIME_STEP);
   //Keyboard enable
   wb_keyboard_enable(TIME_STEP); //milliseconds
   int pressed_key;
   
   /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
   
  while (wb_robot_step(TIME_STEP) != -1) {
  
    //Distance sensor, Left anD Right
    ds_value_right =wb_distance_sensor_get_value(dist_sensor_right);
    printf("Distance sensor right: %lf\n", ds_value_right);
    
    ds_value_left =wb_distance_sensor_get_value(dist_sensor_left);
    printf("Distance sensor left: %lf\n", ds_value_left);
    
    
    angle = wb_position_sensor_get_value(encoder);
    angle2 = wb_position_sensor_get_value(encoder2);
    
    
    //Keyboard Variable
    pressed_key = wb_keyboard_get_key();
    
    //defult state of the rrobot
    stopRobot(wheels);
    
   
    
    // Case of movment with the keyboard
    switch (pressed_key) {
      case 'W': {
      
          counter=1;
          counter_left=0;
          count=0;
          break;
          }
      
      case 'G':{
       
           count = 1;
           break;
          }
          
      case 'S':{
          counter=2;
          break;
          
          }
      
      case 'A':{
          counter=3;
          break;
        
          }
      
      }
     
      //Logic of the Manual mode
      
      if (counter==1){
        
   
        if(pressed_key == WB_KEYBOARD_UP){
        
          goRobot(wheels);
          }
          
         else if(pressed_key == WB_KEYBOARD_DOWN){
         
          turnDown(wheels);
          }
          
         else if(pressed_key == WB_KEYBOARD_RIGHT){
         
          turnRight(wheels);
    
          }
          else if(pressed_key == WB_KEYBOARD_LEFT){
          
          turnLeft(wheels);
          }
    
          else {
          
          stopRobot(wheels);
          }
          
        }
        
        //Logic of the automatic mode
        
        if (count == 1){
        
        velocity = 4;
        goRobot(wheels);
          
          //sensor right
          if (ds_value_right <= 250){
          
          stopRobot(wheels);
          counter_left = 1;
          
             if(counter_left == 1){
             
              turnLeft(wheels);
              counter_left = 0;
              }
              
              else{
              
              goRobot(wheels);
              }
            }
            
            //sensor left
          if (ds_value_left<=250){
          
               stopRobot(wheels);
               counter_left=1;
          
            if(counter_left==1){
            
               turnRight(wheels);
               counter_left=0;
               }
              
            else {
            
              goRobot(wheels);
              }
            }
         }  
        
        
        //45 degrees left
        
        
    if(counter == 2){
    
      turnLeft(wheels);
        
         if (angle <= 14.5){
         
         stopRobot(wheels);
         }
      }
        //45 degree right
        
    if(counter == 3){
    
      turnRight(wheels);
        
         if (angle2 >= 19.5){
         
             stopRobot(wheels);
             }
      }
          
        
          
            
            
         
        

    
  }

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}