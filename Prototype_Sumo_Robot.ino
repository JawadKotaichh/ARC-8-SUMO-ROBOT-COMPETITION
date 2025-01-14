#include <xmotion.h>

const int SensorFR = ;
const int SensorFL = ;    //Black and White Sensors pins
const int SensorBR = ;
const int SensorBL = ;
int SensorFRVal;
int SensorFLVal;        // Black and White sensors Values
int SensorBRVal;
int SensorBLVal;

const int LeftObstacle = ;     //Obstacle Avoidance Sensors pinout
const int RightObstacle = ;
const int MiddleObstacle = ;
int LeftObstacleVal;              // Obsatcle Sensors Values
int RightObstacleVal;
int MiddleObstacleVal;

XMotion xmotion;   // Set up XMotion instance
int speed = 70;
int search_distance = 100;

void setup() {
    pinMode(SensorFR,INPUT);
    pinMode(SensorFL,INPUT);
    pinMode(SensorBR,INPUT);
    pinMode(SensorBL,INPUT);
    pinMode(LeftObstacle,INPUT);
    pinMode(RightObstacle,INPUT);
    pinMode(MiddleObstacle,INPUT);

    xmotion.StopMotors();
    delay(5000);
}

void loop() {
//    SensorFRVal=digitalRead(SensorFR);
//    SensorFLVal=digitalRead(SensorFL);
//    SensorBRVal=digitalRead(SensorBR);   //Read the value of each sensor
//    SensorBLVal=digitalRead(SensorBL);
//    LeftObstacleVal=digitalRead(LeftObstacle);              // Obsatcle Sensors Values
//    RightObstacleVal=digitalRead(RightObstacle);
//    MiddleObstacleVal;=digitalRead(MiddleObstacle);

    StartTimer=millis();
    Timer=1500;//Change to edit the movement time 
    while(millis() - StartTimer < Timer && is_in_ring() && is_not_detected() )//Move Forward oblique for 1500 ms while not detecting enemy and inside ring
    xmotion.Forward(100,1);

    if(digitalRead(SensorFL)) {  //If white detected at top left move back then rotate 
      xmotion.Backward(100,1);
      delay(500);
      xmotion.Right0(100,1);
      delay(500);
    }
    else if(digitalRead(SensorFR)) //If white detected at top right move back then rotate 
    {
      xmotion.Backward(100,1);
      delay(500);
      xmotion.Left(100,1);
      delay(500);
    }
    else if(digitalRead(SensorBL)) //If white detected at bottom left move forward then rotate 
    {
      xmotion.Forward(100,1);
      delay(500);
      xmotion.Right0(100,1);
      delay(500);
    }
    else if(digitalRead(SensorBR)) //If white detected at bottom right move forward then rotate
    {
      xmotion.Forward(100,1);
      delay(500);
      xmotion.Left0(100,1);
      delay(500);
    }
    else
    {
        Attack();   //if the robot is inside the ring and one of the Obstacle sensors detected the enemy, Launch attack!
    }
  }
  
bool is_in_ring()
{
  //returns true if the 4 light sensors read black, i.e inside the ring
  return (!digitalRead(SensorBR)&& !digitalRead(SensorBL) && !digitalRead(SensorFR) && !digitalRead(SensorFL));
}
  
bool is_not_detected()
{
  //returns true if the 3 obstacle sensors did not detect an object 
  return (!digitalRead(LeftObstacle) && !digitalRead(MiddleObstacle) && !digitalRead(RightObstacle)); 
}

void Attack()
  {
    if(digitalRead(LeftObstacle)&& !digitalRead(MiddleObstacle) && !digitalRead(RightObstacle) )        //If only Top Left sensor detects the enemy
    {xmotion.Right0(100,1);}
    
    else if(digitalRead(LeftObstacle)&& digitalRead(MiddleObstacle) && !digitalRead(RightObstacle))    //If Top Left and Middle sensor detects the enemy
    {xmotion.Left0(100,1);}
    
    else if(digitalRead(LeftObstacle)&& digitalRead(MiddleObstacle) && digitalRead(RightObstacle))          //if Top left and Right and Middle sensor detects the enemy
    {xmotion.Forward(100,1);}
    
    else if(!digitalRead(LeftObstacle)&& !digitalRead(MiddleObstacle) && digitalRead(RightObstacle))          //if only Top Right sensor detects the enemy
    {xmotion.Right0(100,1);}
    
    else if(!digitalRead(LeftObstacle)&& digitalRead(MiddleObstacle) && digitalRead(RightObstacle))          //if Top Right and Middle sensor detects the enemy
    {xmotion.Right0(100,1);}
    
    else if(!is_not_detected())          //If none sensor detects the enemy
    {star_search();}
    
  }
}

// This is a search function that let the robot move based on the star pattern to detect the enemy
void star_search() {
  for (int i = 0; i < 5; i++) {
    xmotion.forward(speed, search_distance);  // Move forward
    delay(1000);                              // Pause for 1 second to allow robot to stop
    xmotion.turn(144);                        // Turn 144 degrees (one-fifth of 360 degrees)
  }
}
