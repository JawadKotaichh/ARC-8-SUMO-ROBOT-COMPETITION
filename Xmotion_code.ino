#include <xmotion.h>
//************************//
int LeftSensor = 1; // Opponent Sensors D1, D2, D4, A4, A5  
int LefttDiagonalSensor = 2;                               
int MiddleSensor = 4;                                       
int RightDiagonalSensor = A4;                               
int RightSensor = A5;                                       
//************************//
int LeftLineSensor = 0; // Line Sensors D0 & A1             
int RightLineSensor = A1;                                   
//************************//
int Remember=5; // Remember Variable (NOT PIN NUMBER!)      
//************************//
int led1 = 8; // User Led D8                                
//************************//                                
int switch1 = 5; // Dipswitches (D5, D6, D7)                    
int switch2 = 6;                                            
int switch3 = 7;                                            
//************************//
int start = 10; // Microstart Input D10 (Left Corner I/O shares with the Start button) 
//************************//
void setup() {
  xmotion.StopMotors(100);                     
  xmotion.ToggleLeds(100);                    
  pinMode(led1, OUTPUT);                       
  pinMode(LeftSensor, INPUT);                   
  pinMode(LefttDiagonalSensor, INPUT);          
  pinMode(MiddleSensor, INPUT);                  
  pinMode(RightDiagonalSensor, INPUT);          
  pinMode(RightSensor, INPUT);                   
  pinMode(RightLineSensor, INPUT);              
  pinMode(LeftLineSensor, INPUT);                 
  pinMode(switch1, INPUT);                     
  pinMode(switch2, INPUT);                       
  pinMode(switch3, INPUT);                          
  digitalWrite(switch1, HIGH);                     
  digitalWrite(switch2, HIGH);                      
  digitalWrite(switch3, HIGH);                       
  digitalWrite(LefttDiagonalSensor, HIGH);           
  digitalWrite(MiddleSensor, HIGH);                 
  digitalWrite(RightDiagonalSensor, HIGH);         
  Serial.begin(3600);                              

}
void NoSensorRead() {
  while (digitalRead(start) == 1)
{
    if (digitalRead(MiddleSensor) == 1) 
    {
      xmotion.Forward(100, 1); 
       Remember = 0;           
 
    } 
    else if (digitalRead(LeftSensor) == 1) 
    {
      xmotion.Left0(50, 1);        
       Remember = 2;               

    } 
    else if (digitalRead(RightSensor) == 1)   
    {
      xmotion.Right0(50, 1);           
       Remember = 1;                   
    }
    else if (digitalRead(LefttDiagonalSensor) == 1)         
    {
       xmotion.ArcTurn(10, 70, 1);                          
       Remember = 2;                                       
    }
    else if (digitalRead(RightDiagonalSensor) == 1)         
    {
       xmotion.ArcTurn(70, 10, 1);                       
       Remember = 1;                                       
    }

    else if (digitalRead(LeftLineSensor) == 0 && digitalRead(RightLineSensor) == 1) 
    {
        xmotion.Left0(50, 30); 
        xmotion.Forward(70, 10);
    }
    
    else if (digitalRead(RightLineSensor) == 0 && digitalRead(LeftLineSensor) == 1)  
    {
        xmotion.Right0(50, 30); 
        xmotion.Forward(70.10);
    }

    else if (digitalRead(RightLineSensor) == 0 && digitalRead(LeftLineSensor) == 0)
    {
       xmotion.Backward(80, 50); 
        xmotion.Left0(50, 80); 
    }
    
    if (Remember == 0)
    {
       xmotion.Forward(100,1);
       
    }
    if (Remember == 1)
    {
       xmotion.Right0(50, 1);
     
    }
    if (Remember == 2)
    {
       xmotion.Left0(50, 1);
    }
    
    else if (digitalRead(RightSensor) == 0 || digitalRead(RightDiagonalSensor) == 0 || digitalRead(MiddleSensor) == 0 || digitalRead(LefttDiagonalSensor) == 0 || digitalRead(LeftSensor) == 0) 
    {
      xmotion.Left0(70,5);

    }
  }
  while (digitalRead(start) == 0) 
  {
    xmotion.StopMotors(1);
  }
}
