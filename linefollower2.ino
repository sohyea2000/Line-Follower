int leftMotorBackward = D1;                           /* (D1) -> IN1 */
int leftMotorForward =  D2;                           /* (D2) ->IN2  */
int rightMotorForward = D3;                           /* (D3) -> IN3 */
int rightMotorBackward = D4;                          /* (D4) -> IN4 */


 /* define IR pins */
#define lir D5
#define rir D6

int right_IR_reading;                                /*Initialize as integer variables.*/
int left_IR_reading;                                 /*white surface gives reading as 0 & black surface gives reading as 1.*/

void setup() {
  
// initialize motor control pins as output //
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);   
  pinMode(rightMotorBackward, OUTPUT);

// initialize ir pins as input //
  pinMode(lir,INPUT);
  pinMode(rir,INPUT);
  
  Serial.begin(115200);
  }

void loop() {
  
  check();
  while(left_IR_reading==0&&right_IR_reading==0)    /*both IR is on white surface.*/
  {
    forward();
    check();
  }
  
  while(left_IR_reading==1&&right_IR_reading==0)    /*left IR is on black line while right IR is on white surface.*/
  { 
    check();
    while(left_IR_reading==1)                       /*Move left till black IR comes on white surface.*/
    {
      left();
      check();
    }
  }
  
  while(left_IR_reading==0&&right_IR_reading==1)    /*right IR is on black line while left IR is on white surface.*/
  {
    check();
    while(right_IR_reading==1)                      /*Move right till black IR comes on black surface.*/
    {
      right();
      check();
    }
  }
  
  while(left_IR_reading==1&&right_IR_reading==1)    /*both IR is on black line.*/
  {
    stop();
    check();   
  }
  

}

void check()
{ 
  right_IR_reading=digitalRead(rir);
  left_IR_reading=digitalRead(lir);
  Serial.print("left_IR_reading=");
  Serial.println(left_IR_reading);
  Serial.print("right_IR_reading=");
  Serial.println(right_IR_reading);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////  ---------------   MOTOR FUNCTIONS  ------------------ ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************* FORWARD *****************************************************/
void forward()   
{
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
   Serial.print("Forward//////");
}

/********************************************* TURN SHARPLEFT *****************************************************/
void left()   
{
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorForward,LOW);
  Serial.print("Left//////");
}

/********************************************* TURN SHARPRIGHT *****************************************************/
void right()   
{
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  Serial.print("Right//////");
}
/********************************************* STOP *****************************************************/
void stop()   
{
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
  Serial.print("Stop//////");
}
