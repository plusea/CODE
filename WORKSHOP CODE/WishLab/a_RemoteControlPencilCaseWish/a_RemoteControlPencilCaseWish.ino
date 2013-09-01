#include "Servo8Bit.h"
 
int main()
{
    Servo8Bit myServo;  //create a servo object.
                        //a maximum of five servo objects can be created 
 
    myServo.attach(1);  //attach the servo to pin PB1
 
    //sweep the servo
    while(1)
    {
        for(int pos = 0; pos < 180; pos++)  // goes from 0 degrees to 180 degrees
        {                                   // in steps of 1 degree
            myServo.write(pos);             // tell servo to go to position in variable 'pos'
            delay(15);                      // waits 15ms for the servo to reach the position
        }
 
        for(int pos = 180; pos > 1; pos--)  // goes from 180 degrees to 0 degrees
        {
            myServo.write(pos);             // tell servo to go to position in variable 'pos'
            delay(15);                      // waits 15ms for the servo to reach the position
        }
    }
}
