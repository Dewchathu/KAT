#include <Servo.h>   //servo library

Servo servo;        
int servoPin1 = 34;//cap
int servoPin2 = 35;//back door
int M_A1 = 25; //motor a = + 
int M_A2 = 24; //motor a = - 
int M_B1 = 23; //motor b = - 
int M_B2 = 22; //motor b = +
int S_B = 3 ; //speed motor b
int S_A = 2 ;//speed motor a
int R_S = A2; //sincer R 
int S_S = A1; //sincer S 
int L_S = A0; //sincer L 
int S_F_T1 =27; //sonar front down trig
int S_F_E1 =26; //sonar front down eco
int S_F_T2 =28; //sonar front up trig
int S_F_E2 =29; //sonar front up eco
int On = 36;//sonar on
int S_F_T3 =30; //sonar cap trig
int S_F_E3 =31; //sonar cap eco
int M_I1 = 32; //motor a = + 
int M_I2 = 33; //motor a = - 
int S_I = 4 ; //speed motor b
int buzzer = 11; //Buzzer
long duration, dist, average, t, d, dista, durati;  
long aver[3];   //array for average
int num=0;
int mark=0;
int ReadServo;
unsigned long prevTime = millis();

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(S_F_T2, OUTPUT);  
    pinMode(S_F_E2, INPUT); 
    servo.attach(servoPin1);  
    servo.write(141);         //close cap on power on
    delay(100);
    servo.detach();
    servo.attach(servoPin2);   
    servo.write(175);         //close door power on
    delay(1000);
    servo.detach();
    pinMode(M_B1, OUTPUT); 
    pinMode(M_B2, OUTPUT); 
    pinMode(M_A1, OUTPUT); 
    pinMode(M_A2, OUTPUT);
    pinMode(S_B, OUTPUT);
    pinMode(S_A, OUTPUT);
    pinMode(L_S, INPUT); 
    pinMode(S_S, INPUT); 
    pinMode(R_S, INPUT);
    pinMode(S_F_T1, OUTPUT);
    pinMode(S_F_E1, INPUT);
    pinMode(S_F_T3, OUTPUT);
    pinMode(S_F_E3, INPUT); 
    pinMode(S_F_T3, OUTPUT);
    pinMode(S_F_E3, INPUT);
    pinMode(On,OUTPUT);
    pinMode(buzzer,OUTPUT);
}
   
void measure() {  
  digitalWrite(S_F_T2, LOW);
  delayMicroseconds(5);
  digitalWrite(S_F_T2, HIGH);
  delayMicroseconds(15);
  digitalWrite(S_F_T2, LOW);
  pinMode(S_F_E2, INPUT);
  duration = pulseIn(S_F_E2, HIGH);
  dist = (duration/2) / 29.1;    //obtain distance
}
void Measure() {  
  digitalWrite(S_F_T3, LOW);
  delayMicroseconds(5);
  digitalWrite(S_F_T3, HIGH);
  delayMicroseconds(15);
  digitalWrite(S_F_T3, LOW);
  pinMode(S_F_E3, INPUT);
  durati = pulseIn(S_F_E3, HIGH);
  dista = (durati/2) / 29.1;    //obtain distance
}

void caps(){
  
for (int y=0;y<=2;y++){    //average distance
  Measure();
  aver[y]=dista;
  delay(100);              //delay between measurements
  }
  dista=(aver[0]+aver[1]+aver[2])/3; 
if(dista<10 ){
  delay(5);
  {Dump();}}
  else if(dista>10)
  {stay();}
  }
void forward(){ 
analogWrite(S_A, 80);
analogWrite(S_B, 80);
digitalWrite(M_A1, LOW); 
digitalWrite(M_A2, HIGH);
 digitalWrite(M_B1, HIGH);
 digitalWrite(M_B2, LOW); 
}

 void turnRight(){
  
digitalWrite(M_A1, LOW); 
digitalWrite(M_A2, LOW); 
digitalWrite(M_B1, HIGH); 
digitalWrite(M_B2, LOW); 
} 

void turnLeft(){

 digitalWrite(M_A1, LOW);
 digitalWrite(M_A2, HIGH);
 digitalWrite(M_B1, LOW); 
digitalWrite(M_B2, LOW); 
}
void turnLeftD(){
   digitalWrite(M_A1, LOW);
   digitalWrite(M_A2, HIGH);
   digitalWrite(M_B1, LOW); 
   digitalWrite(M_B2, HIGH); 
  }
void backward(){
  digitalWrite(M_A1, HIGH);
   digitalWrite(M_A2, LOW);
   digitalWrite(M_B1, LOW); 
   digitalWrite(M_B2, HIGH);
  }
void Stop(){
 
digitalWrite(M_A1, LOW); 
digitalWrite(M_A2, LOW); 
digitalWrite(M_B1, LOW); 
digitalWrite(M_B2, LOW);
tone(buzzer, 1000);
delay(1000);
noTone(buzzer);     // Stop sound...
delay(1000);        // ...for 1sec
}
void StopPerment(){
 
digitalWrite(M_A1, LOW); 
digitalWrite(M_A2, LOW); 
digitalWrite(M_B1, LOW); 
digitalWrite(M_B2, LOW);
}

void Dump(){
  StopPerment();
  delay(500);
  analogWrite(S_A, 100);
  analogWrite(S_B, 100);
  turnLeftD();
  delay(2550);
  StopPerment();
  delay(5000);
  backward();
  delay(900);
  StopPerment();
  delay(5000);
  dooron();
  IntDR();
  dooroff();
  num++;
} 
 void IntDR(){     
 baron();
 baroff();
 baron();
 baroff();
 barshut(); 
  }
void stay(){
  mark=0;
  StopPerment();
  delay(500);
  analogWrite(S_A, 100);
  analogWrite(S_B, 100);
  turnLeftD();
  delay(2550);
  StopPerment();
  delay(5000);
  backward();
  delay(900);
  StopPerment();
  delay(5000);
  servo.detach();
  }
void dooron(){
  tone(buzzer, 440); // Send 440Hz sound signal...
  delay(1000);
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec// ...for 1 sec
  servo.attach(servoPin2);
  delay(1);       
 servo.write(60);
 delay(1000); 
  }
void dooroff(){
  tone(buzzer, 440); // Send 440Hz sound signal...
  delay(1000);  
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec// ...for 1 sec
  servo.attach(servoPin2);
  delay(1);
  servo.write(175);  
 delay(3000);       
  }
 void baron(){
  digitalWrite(M_I1,LOW);
  digitalWrite(M_I2,LOW);
 delay(500);
 digitalWrite(M_I2,HIGH);
 digitalWrite(M_I1,LOW);
 delay(18000);
  }
  void baroff(){
  digitalWrite(M_I2,LOW);
  digitalWrite(M_I1,LOW);
 delay(500);
 digitalWrite(M_I1,HIGH);
 digitalWrite(M_I2,LOW);
 delay(18000);
  }
  void barshut(){
    digitalWrite(M_I1,LOW);
    digitalWrite(M_I2,LOW);
    delay(500);
    }
 
  void loop() {
  // put your main code here, to run repeatedly:
  
 digitalWrite(On,HIGH);
 for (int i=0;i<=2;i++) {   //average distance
    measure();               
  }  

if ( dist<70 && mark==0 ) {
//Change distance as per your need
 ReadServo = servo.read();
 if(ReadServo > 100 && ReadServo < 180){
  servo.attach(servoPin1);
  delay(1);
  servo.write(50); 
  delay(100); 
  }
  else if(ReadServo > 0 && ReadServo < 90){

          servo.attach(servoPin1);
          delay(1);
          servo.write(141);  
          delay(1000);
          servo.detach();

  }
  
  /*else if(TimeCount()== 60){
      servo.attach(servoPin1);
      delay(1);
      servo.write(141);  
      delay(1000);
      servo.detach();  
    } */
  }
    unsigned long currentTime = millis();
    Serial.println(currentTime - prevTime);
     if (currentTime - prevTime > 30000 && ReadServo > 0 && ReadServo < 90){
    
          servo.attach(servoPin1);
          delay(1);
          servo.write(141);  
          delay(1000);
          servo.detach();
          prevTime = currentTime ;
    } 
    
Serial.println(dist);

for (int x=0;x<=2;x++){    //average distance
  Measure();
  aver[x]=dista;
  delay(100);              //delay between measurements
  }
  dista=(aver[0]+aver[1]+aver[2])/3; 
ReadServo = servo.read();
if(dista<15  && num==0 && ReadServo > 100 && ReadServo < 180){
  digitalWrite(S_F_T3, LOW);
  dista = 9;
  mark++;
 
  digitalWrite(S_F_T1, LOW);
  delayMicroseconds(2);
  digitalWrite(S_F_T1, HIGH);
  delayMicroseconds(10);
  t = pulseIn(S_F_E1, HIGH);
  d = (t / 2) / 29.1;
  Serial.println(d);
  delay(100);
  if(d<=15)
 {
  Stop();
 }
 else{
 analogWrite(S_A, 50);
 analogWrite(S_B, 50);
 
 if ((digitalRead(L_S) == 0)&&
(digitalRead(S_S) == 1)&&
(digitalRead(R_S) == 0))
{forward();}


 if ((digitalRead(L_S) == 1)&&
(digitalRead(S_S) == 1)&&
(digitalRead(R_S) == 0))
{turnLeft();}

 if ((digitalRead(L_S) == 1)&&
(digitalRead(S_S) ==0)&&
(digitalRead(R_S) == 0)) 
{turnLeft();} 

if ((digitalRead(L_S) == 0)&&
(digitalRead(S_S) == 1)&&
(digitalRead(R_S) == 1))
{turnRight();}

 if ((digitalRead(L_S) == 0)&&
(digitalRead(S_S) == 0)&&
(digitalRead(R_S) == 1))
{turnRight();}

if ((digitalRead(L_S) == 1)&&
(digitalRead(S_S) == 0)&&
(digitalRead(R_S) == 1))
{stay();}
 if ((digitalRead(L_S) == 1)&&
(digitalRead(S_S) == 1)&&
(digitalRead(R_S) == 1))
{caps();}
}
  digitalWrite(S_F_T3, HIGH);
  delayMicroseconds(15);
}
if(dista>15 && num>0){
  delay(5);
  Serial.println(dista);
  mark++;
  digitalWrite(S_F_T1, LOW);
  delayMicroseconds(2);
  digitalWrite(S_F_T1, HIGH);
  delayMicroseconds(10);
  t = pulseIn(S_F_E1, HIGH);
  d = (t / 2) / 29.1;
  Serial.println(d);
  delay(100);
  if(d<=15)
 {Stop();}
 else{
 analogWrite(S_A, 50);
 analogWrite(S_B, 50);
 if ((digitalRead(L_S) == 0)&&
(digitalRead(S_S) == 1)&&
(digitalRead(R_S) == 0))
{forward();}


 if ((digitalRead(L_S) == 1)&&
(digitalRead(S_S) == 1)&&
(digitalRead(R_S) == 0))
{turnLeft();}

 if ((digitalRead(L_S) == 1)&&
(digitalRead(S_S) ==0)&&
(digitalRead(R_S) == 0)) 
{turnLeft();} 

if ((digitalRead(L_S) == 0)&&
(digitalRead(S_S) == 1)&&
(digitalRead(R_S) == 1))
{turnRight();}

 if ((digitalRead(L_S) == 0)&&
(digitalRead(S_S) == 0)&&
(digitalRead(R_S) == 1))
{turnRight();}

if ((digitalRead(L_S) == 1)&&
(digitalRead(S_S) == 1)&&
(digitalRead(R_S) == 1))
{stay();
num=0;
}
}
}
}
