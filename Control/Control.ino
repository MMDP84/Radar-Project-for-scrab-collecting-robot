// MMDP project coding
                                                                                                // Includes the Servo library
#include <Servo.h>. 
//%%%%%% Introducing the motor %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//#define EN  3                                                                                   // Arduino PWM output connected to the ENABLE pin of the driver
const int IN1=5, IN2=6;                                                                         // Arduino GPIO pins connected to the L293D driver inputs
char dir = 'F';                                                                                 // direction of rotation of the dc motor (F/R)
int sp=2, dutyc, dig = 1;                                                                       // speed level = 1 (min) <-> 5 (max);
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//%%%%%% Defines Tirg and Echo pins of the Ultrasonic Sensor %%%%%%%%%%%%%%%%%%%%%%%%%%
const int trigPin = 10;
const int echoPin = 11;
                                                                                                // Variables for the duration and the distance
long duration;
int distance;
Servo myServo;                                                                                  // Creates a servo object for controlling the servo motor
void setup() {
  pinMode(trigPin, OUTPUT);                                                                     // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);                                                                      // Sets the echoPin as an Input
  Serial.begin(9600);
  myServo.attach(12);                                                                           // Defines on which pin is the servo motor attached
  //%%%%%%% taein pin-haye motor %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  pinMode(IN1,OUTPUT);                                                                          // configuration of high level GPIO pin for one rotation direction
  pinMode(IN2,OUTPUT);                                                                          // configuration of high level GPIO pin for the opposite direction
  pinMode(EN,OUTPUT);                                                                           // GPIO pin connected to the ENABLE pin of the driver
  pinMode(7, INPUT_PULLUP);                                                                     // set button pin as Input with 20k pull-up resistance
  delay(100);
}
void loop() {
                                                                                                // rotates the servo motor from 15 to 165 degrees
  for(int i=15;i<=165;i++){  
  myServo.write(i);
  delay(50); 
  distance = calculateDistance();                                                               // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  Serial.print(i);                                                                              // Sends the current degree into the Serial Port
  Serial.print(",");                                                                            // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance);                                                                       // Sends the distance value into the Serial Port
  Serial.print(".");                                                                            // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
                                                                                                // Repeats the previous lines from 165 to 15 degrees
  for(int i=165;i>15;i--){  
  myServo.write(i);
  delay(50);
  distance = calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
  
  //%%%%%%% Baraye control dor motor (F or R) aghab va jolo kardan robot %%%%%%%%%%%%%%%
  dig=digitalRead(8);
  if (dig==0){
     if (dir=='F')
        dir='R';
     else if (dir=='R')
        dir='F';
  }
  //int j=90-i
  
//%%%%%%% baraye ferestadan dastoor rooshan va khamoosh shodan motor va %%%%%%%%%%%%%%%%%%%
//%%%%%%% harkat be samte jolo ya aghab %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
  for(int d=distance;d>2;d--){
  sp = analogRead(0);
  dutyc = map(sp,0,1023,0,255);                       // mapping of digital voltage into PWM duty-cycle (0255)
  analogWrite(EN,dutyc);                              // activation of PWM output on the ENABLE input to set speed
  if (dir=='F'){                                      // if TRUE, set forward rotation direction
    digitalWrite(IN1, HIGH);                          // 5V
    digitalWrite(IN2, LOW);}                          // Gnd
  else if(dir=='R'){                                  // if TRUE set reverse rotation direction
    digitalWrite(IN2, HIGH);                          // 5V
    digitalWrite(IN1, LOW);}                          // Gnd
    delay(100);}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
}
                                                                                                // Function for calculating the distance measured by the Ultrasonic sensor
  int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
                                                                                               // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);                                                           // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}
