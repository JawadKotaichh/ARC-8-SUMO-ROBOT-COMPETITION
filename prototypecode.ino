
#include <xmotion.h>
const int Sensor=4;
int SensorVal;
void setup() {
pinMode(Sensor,INPUT);
xmotion.StopMotors(100);
}

void loop() {

  SensorVal=digitalRead(Sensor);
  if(SensorVal==1){
    xmotion.Forward(100,1);
    }
  else{
    xmotion.StopMotors(100);
    }
   
  
  
}
