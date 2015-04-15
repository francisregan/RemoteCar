#include <NewPing.h>

#define TRIGGER_PIN  18
#define ECHO_PIN     19
#define MAX_DISTANCE 200
#define light 7

NewPing DistanceSensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
    pinMode(light,OUTPUT);
    
    pinMode(12, OUTPUT); //Initiates Motor Channel A pin
    pinMode(9, OUTPUT); //Initiates Brake Channel A pin

    //Setup Channel B
    pinMode(13, OUTPUT); //Initiates Motor Channel A pin
    pinMode(8, OUTPUT);  //Initiates Brake Channel A pin*
  
    Serial.begin(9600);
}

void loop()
{
  
  if (Serial.available())  
  {
    char ch = Serial.read();
    Serial.print("Received: ");
    Serial.println(ch);
    digitalWrite(light, HIGH);
    int res = ch - '0';
    checkCommand(res);
  }
}

void checkCommand(int n){
  
  switch (n) {
  case 0:    // Berserk mode
    goBerserk();
    break;
  case 1:    // Going ahead
    goAhead();
    Serial.println("ok#");
    break;
  case 2:    // Going back
    goBack();
    Serial.println("ok#");
    break;
 case 3:    // Going top left
    goTopLeft();
    Serial.println("ok#");
    break;
  case 4:   
    goTopRight();
    Serial.println("ok#");
    break;
  case 5:   
    goBottomRight();
    Serial.println("ok#");
    break;
  case 6:    
    goBottomLeft();
    Serial.println("ok#");
    break;
 case 7: 
    hitBrake();
    Serial.println("ok#");
    break;
  }
  digitalWrite(light, LOW);
}



void goAhead()
{
   digitalWrite(9, LOW);   //Disengage the Brake for Channel A
   digitalWrite(8, LOW);   //Disengage the Brake for Channel B
   
   analogWrite(3, 150);
   analogWrite(11, 255);
     
   digitalWrite(12, LOW); //Establishes forward direction of Channel A
   digitalWrite(13, LOW);  //Establishes forward direction of Channel B
  }
   

void hitBrake(){
  digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
  digitalWrite(8, HIGH);   //Disengage the Brake for Channel B
}

void goBack(){
  
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
   
    analogWrite(3, 150);
    analogWrite(11, 255);
     
    digitalWrite(12, HIGH); //Establishes backward direction of Channel A
    digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
     
}

void goTopRight(){
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  digitalWrite(8, HIGH);   //Disengage the Brake for Channel B
   
  analogWrite(3, 150);
  //analogWrite(11, 130);
   
  digitalWrite(12, LOW); //Establishes backward direction of Channel A
  //digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
}

void goTopLeft(){
  digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
   
  //analogWrite(3, 255);
  analogWrite(11, 255);
   
  //digitalWrite(12, HIGH); //Establishes backward direction of Channel A
  digitalWrite(13, LOW);  //Establishes backward direction of Channel B
}

void goBottomRight(){
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  digitalWrite(8, HIGH);   //Disengage the Brake for Channel B
  
  analogWrite(3, 150);
  analogWrite(11, 230);
    
  digitalWrite(12, HIGH); //Establishes backward direction of Channel A
  digitalWrite(13, LOW); //Establishes forward direction of Channel B
}

void goBottomLeft(){
  digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  
  analogWrite(3, 150);
  analogWrite(11, 230);
    
  digitalWrite(12, LOW); //Establishes forward direction of Channel A
  digitalWrite(13, HIGH); //Establishes forward direction of Channel B
}

void goBerserk(){
  
  unsigned int cm = DistanceSensor.ping_cm();
    Serial.print("Distance: ");
    Serial.print(cm);
    Serial.println("cm");
    
    if(cm > 20) 
    {
      digitalWrite(12, LOW); //Establishes forward direction of Channel A
      digitalWrite(9, LOW);   //Disengage the Brake for Channel A
      analogWrite(3, 255);   //Spins the motor on Channel A at full speed

    //Motor B backward @ half speed
      digitalWrite(13, LOW);  //Establishes backward direction of Channel B
      digitalWrite(8, LOW);   //Disengage the Brake for Channel B
      analogWrite(11, 255); 
    }
    else
    {
      digitalWrite(9, HIGH);
      digitalWrite(8, HIGH);
      
      digitalWrite(12, HIGH); //Establishes forward direction of Channel A
      digitalWrite(9, LOW);   //Disengage the Brake for Channel A
      analogWrite(3, 255);   //Spins the motor on Channel A at full speed
      
      //digitalWrite(8, HIGH);
  
      //Motor B backward @ half speed
      //digitalWrite(13, LOW);  //Establishes backward direction of Channel B
      //digitalWrite(8, LOW);   //Disengage the Brake for Channel B
      //analogWrite(11, random(100, 255));
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
    }
    //delay(1000);
  
}
