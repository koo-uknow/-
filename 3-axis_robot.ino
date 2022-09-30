#include <AccelStepper.h>
#include<ezButton.h>
#include<MultiStepper.h>
#define Limit_Switch1 33
#define Limit_Switch2 35
#define Limit_Switch3 37
#define Limit_Switch4 39
#define Limit_Switch5 41
#define Limit_Switch6 43

//Toggle Switch mode ( Auto & Manual)
#define Toggle_Switch1 20 //( Manul Mode == Controll by button)
#define Toggle_Switch2 21 // ( Auto Mode )



// Define pin connections motor1
const int dirPin1 = 2;
const int stepPin1 = 3;
const int ENPin1 = 4;
const int stepsPerRevolution = 200;

// Define pin connections motor2
const int dirPin2 = 8;
const int stepPin2 = 9;
const int ENPin2 = 10;

// Define pin connections motor3
const int dirPin3 = 16;
const int stepPin3 = 15;
const int ENPin3 = 14;

const int left_btn = 22;
const int right_btn = 24;
const int up_btn = 26;
const int down_btn = 28;
const int forward_btn = 30;
const int backward_btn = 32;

long initial_homing = -1;

//bool isStopped = false;
const int User_Button = 32;

const int relaypin =53;
const int relaypin1 = A8;
const int relaypin2 = A9;


// Define motor interface type
#define motorInterfaceType1 1
#define motorInterfaceType2 1
#define motorInterfaceType3 1
// Creates an instance
AccelStepper Stepper1(motorInterfaceType1, stepPin1, dirPin1);
AccelStepper Stepper2(motorInterfaceType2, stepPin2, dirPin2);
AccelStepper Stepper3(motorInterfaceType3, stepPin3, dirPin3);

MultiStepper Steppers; // create instance of MultiStepper


void setup() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(ENPin1, OUTPUT);
  
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(ENPin2, OUTPUT);

  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(ENPin3, OUTPUT);
  
  

  //Limit Switch
  pinMode(Limit_Switch1,INPUT_PULLUP);
  pinMode(Limit_Switch2, INPUT_PULLUP);
  pinMode(Limit_Switch3, INPUT_PULLUP);

  //Toggle Switch
  pinMode(Toggle_Switch1, INPUT_PULLUP);
  pinMode(Toggle_Switch2, INPUT_PULLUP);

  //Button
  pinMode(left_btn, INPUT_PULLUP);
  pinMode(right_btn, INPUT_PULLUP);
  pinMode(up_btn, INPUT_PULLUP);
  pinMode(down_btn, INPUT_PULLUP);
  pinMode(forward_btn, INPUT_PULLUP);
  pinMode(backward_btn, INPUT_PULLUP);
  
  pinMode(relaypin,OUTPUT);
  pinMode(relaypin1,OUTPUT);
  pinMode(relaypin2,OUTPUT);

  pinMode(User_Button, INPUT_PULLUP);
  Stepper1.setMaxSpeed(2000);
  Stepper1.setAcceleration(2000.0);
  Stepper1.setSpeed(1000);
  
  Stepper2.setMaxSpeed(2000);
  Stepper2.setAcceleration(2000.0);
  Stepper2.setSpeed(2000);

  Stepper3.setMaxSpeed(2000);
  Stepper3.setAcceleration(300.0);
  Stepper3.setSpeed(2000);
  
  Serial.begin(9600);
  Steppers.addStepper(Stepper1);
  Steppers.addStepper(Stepper2);
  Steppers.addStepper(Stepper3);

  resethoming();
  digitalWrite(relaypin1,HIGH);
  digitalWrite(relaypin2,HIGH);
  while(!Serial);
  Serial.println("Input number 1,2,3,4,5,6,7,8 to control each Box");
}  
void resethoming(){
  // Set Homing
  
  Serial.println("Homing.....");
  delay(1000);
  // X Axis homing
  while (digitalRead(Limit_Switch1)){ // Make the stepper move unitle the swtich is activated
    Stepper1.moveTo(initial_homing);
    initial_homing++;
    Stepper1.run();
    delay(10);
  
  }

  Stepper1.setCurrentPosition(0); // Set the current position as zero for now
  initial_homing = 1;

  while(!digitalRead(Limit_Switch1)){
    Stepper1.moveTo(initial_homing);
    Stepper1.run();
    initial_homing--;
    delay(10);
    Stepper1.setCurrentPosition(0);
    
  }
  
  // Y Axis Homing
  
  while (digitalRead(Limit_Switch2)){ // Make the stepper move unitle the swtich is activated
    Stepper2.moveTo(initial_homing);
    initial_homing++;
    Stepper2.run();
    delay(10);
    
  }

  Stepper2.setCurrentPosition(0); // Set the current position as zero for now
  initial_homing = 1;

  while(!digitalRead(Limit_Switch2)){
    Stepper2.moveTo(initial_homing);
    Stepper2.run();
    initial_homing--;
    delay(10);
    Stepper2.setCurrentPosition(0);
    
  }
  
  
  // Z Axis Homing
  while (digitalRead(Limit_Switch3)){ // Make the stepper move unitle the swtich is activated
    Stepper3.moveTo(initial_homing);
    initial_homing++;
    Stepper3.run();
    delay(10);
    
  }

  Stepper3.setCurrentPosition(0); // Set the current position as zero for now
  initial_homing = 1;

  while(!digitalRead(Limit_Switch3)){
    Stepper3.moveTo(initial_homing);
    Stepper3.run();
    initial_homing--;
    delay(10);
    Stepper3.setCurrentPosition(0);
    
  }

  Serial.println("X axis homing Completed");
  Serial.println("Y axis homing Completed");
  Serial.println("Z axis homing Completed");
  

}

void left(int pos1){  //motor1
  
  Stepper1.moveTo(pos1);

  Stepper1.runToPosition();

  delay(100);
  
}

void right(int pos2){ // motor1
  if(digitalRead(Limit_Switch1)==LOW){
    Stepper1.setSpeed(0);
    Stepper1.stop();
  }else{
   Stepper1.moveTo(pos2);
   Stepper1.runToPosition();
   delay(100);
   }
  
}

void up(int pos3){       //motor2

  Stepper2.moveTo(-pos3);

  Stepper2.runToPosition();

  delay(100);
}
void down(int pos4){   //motor2
  if(digitalRead(Limit_Switch2)==LOW){
    Stepper2.setSpeed(0);
    Stepper2.stop();
  }
  else{
    Stepper2.moveTo(-pos4);
    Stepper2.runToPosition();
    delay(100);
  }
}
void forward(int pos5){ //motor3
  
  digitalWrite(ENPin3,LOW);
  digitalWrite(dirPin3,LOW);

  for(int x = 0; x < pos5; x++)
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(800);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(800);
  }
  
 
}
void backward(int pos6){    // motor3
  if(digitalRead(Limit_Switch3)==LOW){
    Stepper3.setSpeed(0);
    Stepper3.stop();
  }
  else{
   digitalWrite(ENPin3,LOW);
   digitalWrite(dirPin3,HIGH);
   for(int x = 0; x < pos6; x++)
   {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(800);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(800);
   }
  }  
}
void pickup(int pos7){
  digitalWrite(ENPin2,LOW);
  digitalWrite(dirPin2,LOW);

  for(int x = 0; x < pos7; x++)
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(1200);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(1200);
  }
}
void pickdown(int pos9){
  digitalWrite(ENPin2,LOW);
  digitalWrite(dirPin2,HIGH);

  for(int x = 0; x < pos9; x++)
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(1200);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(1200);
  }
}
void stop(){
  Stepper1.setSpeed(0);
  Stepper2.setSpeed(0);
  Stepper3.setSpeed(0);
  Stepper1.stop();
  Stepper2.stop();
  Stepper3.stop();
  
}
void buttonControl(){
    int val = digitalRead(left_btn);
    if(val==HIGH)
   {
    digitalWrite(ENPin1,LOW);
    digitalWrite(dirPin1,LOW);

    for(int x = 0; x < 200; x++)
    {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(800);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(800);
    }

   }
   
   if(digitalRead(right_btn) == HIGH)
   {
     digitalWrite(ENPin1,LOW);
    digitalWrite(dirPin1,HIGH);

    for(int x = 0; x < 200; x++)
    {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(800);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(800);
    }

   }

   if(digitalRead(up_btn) == HIGH)
   {
     digitalWrite(ENPin2,LOW);
    digitalWrite(dirPin2,HIGH);

    for(int x = 0; x < 200; x++)
    {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(800);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(800);
    }

   }
   
   if(digitalRead(down_btn) == HIGH)
   {
     digitalWrite(ENPin2,LOW);
    digitalWrite(dirPin2,LOW);

    for(int x = 0; x < 200; x++)
    {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(800);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(800);
    }
   }
   
   if(digitalRead(forward_btn)== HIGH)
   {
     digitalWrite(ENPin3,LOW);
    digitalWrite(dirPin3,HIGH);

    for(int x = 0; x < 200; x++)
    {
      digitalWrite(stepPin3, HIGH);
      delayMicroseconds(800);
      digitalWrite(stepPin3, LOW);
      delayMicroseconds(800);
    }
   }
   
   if(digitalRead(backward_btn)== HIGH)
   {
     digitalWrite(ENPin3,LOW);
    digitalWrite(dirPin3,LOW);

    for(int x = 0; x < 200; x++)
    {
      digitalWrite(stepPin3, HIGH);
      delayMicroseconds(800);
      digitalWrite(stepPin3, LOW);
      delayMicroseconds(800);
    }
   }
   
}
void userbutton(){
  if(digitalRead(User_Button)==HIGH){
    backward(2500);
    delay(1000);
    down(-100);
    delay(1000);
    forward(2500);
    delay(1000);
    backward(2500);
    delay(100);
    down(300);
    stop();
  }
}

void Box1(){
  int userstate1=0;
  digitalWrite(relaypin1,LOW);
  digitalWrite(relaypin2,LOW);
  delay(2000);
  up(470);
  delay(1000);
  forward(2350);
  delay(1000);
  digitalWrite(relaypin,HIGH);
  delay(1000);
  pickup(400);
  delay(1000);
  backward(2350);
  delay(1000);
  up(9200);
  delay(2000);
  while(userstate1 == 0){
      if( digitalRead(User_Button) == HIGH)
      {
        Serial.println("Button pressed");
        delay(1000);
        down(400);
        delay(1000);
        up(500);
        delay(1000);
        forward(2350);
        delay(2000);
        pickdown(700);
        delay(2000);
        digitalWrite(relaypin,LOW);
        delay(2000);
        backward(2350);
        delay(100);
        down(200);
        stop();
        userstate1 = 1;
      } 
    }
    resethoming(); 
}
void Box2(){
  int userstate2=0;
  digitalWrite(relaypin1,LOW);
  digitalWrite(relaypin2,LOW);
  delay(2000);
  left(-1360);
  delay(1000);
  up(470);
  delay(1000);
  forward(2350);
  delay(1000);
  digitalWrite(relaypin,HIGH);
  delay(2000);
  pickup(300);
  delay(1000);
  backward(2350);
  delay(1000);
  right(0);
  delay(1000);
  up(9900);
  delay(1000);
  while(userstate2 == 0){
      if( digitalRead(User_Button) == HIGH)
      {
          Serial.println("Button pressed");
          delay(1000);
          down(400);
          delay(1000);
          left(-1360);
          delay(1000);
          up(600);
          delay(1000);
          forward(2350);
          delay(1000);
          pickdown(700);
          delay(1000);
          digitalWrite(relaypin,LOW);
          delay(2000);
          backward(2350);
          delay(1000);
          down(200);
          right(0);
          stop();
         userstate2 = 1;
      }
    }
     resethoming();
}
void Box3(){
  int userstate3=0;
  delay(2000);
  left(-2800);
  delay(1000);
  up(470);
  delay(1000);
  forward(2350);
  digitalWrite(relaypin,HIGH);
  delay(2000);
  pickup(300);
  delay(1000);
  backward(2350);
  delay(1000);
  right(0);
  delay(1000);
  up(9900);
  delay(1000);
  while(userstate3 == 0){
      if( digitalRead(User_Button) == HIGH)
      {
          Serial.println("Button pressed");
           delay(1000);
           down(400);
           delay(1000);
           left(-2800);
           delay(1000);
           up(600);
           delay(1000);
           forward(2350);
           delay(1000);
           pickdown(700);
           delay(2000);
           digitalWrite(relaypin,LOW);
           delay(1000);
           backward(2350);
         //delay(1000);
           down(200);
           right(0);
           stop();
           userstate3 = 1; 
      }
    }
    resethoming();
     
}
void Box4(){  
  int userstate4 =0;
  delay(1000);
  left(-4120);
  delay(1000);
  up(470);
  delay(1000);
  forward(2350);
  delay(1000);
  digitalWrite(relaypin,HIGH);
  delay(2000);
  pickup(300);
  delay(1000);
  backward(2350);
  delay(1000);
  right(0);
  delay(1000);
  up(9900);
  delay(1000);
  while(userstate4 == 0){
      if( digitalRead(User_Button) == HIGH)
      {
          Serial.println("Button pressed");
            delay(1000);
            down(400);
            delay(1000);
            left(-4120);
            delay(1000);
            up(600);
            delay(1000);
            forward(2350);
            delay(1000);
            pickdown(700);
            delay(2000);
            digitalWrite(relaypin,LOW);
            delay(1000);
            backward(2350);
            down(200);
            right(0);
            
            stop();  
            userstate4 = 1; 
      }
    }
    resethoming();
     
}
void Box5(){
  int userstate5 = 0;
  delay(2000);
  up(6400);
  delay(1000);
  forward(2350);
  delay(1000);
  digitalWrite(relaypin,HIGH);
  delay(1000);
  pickup(400);
  delay(1000);
  backward(2350);
  delay(1000);
  up(9900);
  delay(2000);
  while(userstate5 == 0){
      if( digitalRead(User_Button) == HIGH)
      {
        Serial.println("Button pressed");
        delay(1000);
        down(6500);
        delay(1000);
        forward(2350);
        delay(2000);
        pickdown(700);
        delay(1000);
        digitalWrite(relaypin,LOW);
        delay(1000);
        backward(2350);
        delay(100);
        down(370);
        stop();
        userstate5 = 1;
      }
    }
    
   resethoming();   
  
}
void Box6(){
  int userstate6 = 0; 
  delay(2000);
  left(-1360);
  delay(1000);
  up(6400);
  delay(1000);
  forward(2350);
  delay(1000);
  digitalWrite(relaypin,HIGH);
  delay(1000);
  pickup(400);
  delay(1000);
  backward(2350);
  delay(1000);
  right(0);
  delay(1000);
  up(9900);
  delay(1000);
  while(userstate6 == 0){
      if( digitalRead(User_Button) == HIGH)
      {
        Serial.println("Button pressed");
        delay(1000);
        down(6500);
        delay(1000);
        left(-1360);
        delay(1000);
        forward(2350);
        delay(1000);
        pickdown(700);
        delay(1000);
        digitalWrite(relaypin,LOW);
        delay(2000);
        backward(2350);
        delay(1000);
        down(370);
        right(0);
        stop();
        userstate6 = 1; 
      }
    }
  resethoming();
}
void Box7(){
  int userstate7 = 0;
  delay(2000);
  left(-2830);
  delay(1000);
  up(6400);
  delay(1000);
  forward(2350);
  delay(1000);
  digitalWrite(relaypin,HIGH);
  delay(1000);
  pickup(400);
  delay(1000);
  backward(2350);
  delay(1000);
  right(20);
  delay(1000);
  up(9900);
  delay(1000);
  while(userstate7 == 0){
      if( digitalRead(User_Button) == HIGH)
      {
        delay(100);
        Serial.println("Button pressed");
        delay(1000);
        down(6500);
        delay(1000);
        left(-2830);
        delay(1000);
        forward(2350);
        delay(1000);
        pickdown(700);
        delay(1000);
        digitalWrite(relaypin,LOW);
        delay(2000);
        backward(2350);
        delay(1000);
        down(370);
        right(0);
        stop();
        userstate7 = 1;
      }
    }
  resethoming();   
}
void Box8(){
  int userstate8 = 0;
  delay(2000);
  left(-4100);
  delay(1000);
  up(6400);
  delay(1000);
  forward(2350);
  delay(1000);
  digitalWrite(relaypin,HIGH);
  delay(1000);
  pickup(300);
  delay(1000);
  backward(2350);
  delay(1000);
  right(0);
  delay(1000);
  up(9900);
  delay(1000);
  while(userstate8 == 0){
      if( digitalRead(User_Button) == HIGH)
      {
         delay(100);
         Serial.println("Button pressed");
         delay(1000);
         down(6500);
         delay(1000);
         left(-4100);
         delay(1000);
         forward(2350);
         delay(1000);
         pickdown(700);
         delay(1000);
         digitalWrite(relaypin,LOW);
         delay(2000);
         backward(2350);
         delay(1000);
         down(300);
         right(0);
         stop();  
         userstate8 = 1;
      }
    }
    resethoming();
}
void loop(){
  
  // Automatic Mode
 
    while(Serial.available())
  {
    String command = Serial.readStringUntil('\n');

    if(command == "Box1")
    {
      Serial.println("Box1 working");
      Box1();
      Serial.println("Box1 completed");
    }else if(command == "Box2")
    {
      Serial.println("Box2 working");
      Box2();
      Serial.println("Box2 completed");
    }
    else if(command == "Box3")
    {
      Serial.println("Box3 working");
      Box3();
      Serial.println("Box3 completed");
    }else if(command == "Box4")
    {
      Serial.println("Box4 working");
      Box4();
      Serial.println("Box4 completed");
    }else if(command == "Box5")
    {
      Serial.println("Box5 working");
      Box5();
      Serial.println("Box5 completed");
    }else if(command == "Box6")
    {
      Serial.println("Box6 working");
      Box6();
      Serial.println("Box6 completed");
    }else if(command == "Box7")
    {
      Serial.println("Box7 working");
      Box7();
      Serial.println("Box7 completed");
    }else if(command == "Box8")
    {
      Serial.println("Box8 working");
      Box8();
      Serial.println("Box8 completed");
    }
  }
    
  //while(1);
}
