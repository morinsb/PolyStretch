/*
 Stepper Motor Control - speed control

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.
 A potentiometer is connected to analog input 0.

 The motor will rotate in a clockwise direction. The higher the potentiometer value,
 the faster the motor speed. Because setSpeed() sets the delay between steps,
 you may notice the motor is less responsive to changes in the sensor value at
 low speeds.

 Created 30 Nov. 2009
 Modified 28 Oct 2010
 by Tom Igoe

 */

#include <LiquidCrystal.h>


// initialize the stepper library on pins 8 through 11:

int stepCount = 0;  // number of steps the motor has taken
int stepArrayIndex = 4;
int stepCycleArray[] = {-100, -10, -5, -1, 1, 5, 10, 50, 100, 500, 1000, 10000};


#define ENA 8
#define ENB 9

#define black 10  // In1
#define brown 11  // In2
#define orange 12  // In3
#define yellow 13  // In4

#define triggerButton 4
#define resetButton 5
#define upButton 6
#define downButton 7

LiquidCrystal lcd(47, 48, 49, 50, 51, 52);

void setup() {
  DDRB = 0x3f;
  PORTB = 0x00;
  pinMode(triggerButton, INPUT);
  pinMode(resetButton, INPUT);
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);

  lcd.begin(16,2);
}

void loop() {
  if(digitalRead(downButton) == 1){
    stepArrayIndex--;
    if(stepArrayIndex < 0) {
      stepArrayIndex = 11;  
    }
    refreshLCD();
  }
  if(digitalRead(upButton) == 1){
    stepArrayIndex++;
    if(stepArrayIndex > 11){
      stepArrayIndex = 0;  
    }
    refreshLCD();
  }
  if(digitalRead(resetButton) == 1){
    stepMotor(-stepCount);  
    refreshLCD();
  }
  else if(digitalRead(triggerButton) == 1){
      stepMotor(stepCycleArray[stepArrayIndex]);
      refreshLCD();
  }
  
}

void stepMotor(int i){
   if(i > 0){
    stepCount += i;
   }
   digitalWrite(ENA, HIGH);
   digitalWrite(ENB, HIGH);
  while(true){
    digitalWrite(black, 1);
    digitalWrite(brown, 0);
    digitalWrite(orange, 1);
    digitalWrite(yellow, 0);
    delay(10);
    i--;
    if (i < 1) break; 



    digitalWrite(black, 1);
    digitalWrite(brown, 0);
    digitalWrite(orange, 0);
    digitalWrite(yellow, 1);
    delay(10);  
    i--;
    if (i < 1) break;

    digitalWrite(black, 0);
    digitalWrite(brown, 1);
    digitalWrite(orange, 0);
    digitalWrite(yellow, 1);
    delay(10);
    i--;
    if (i < 1) break;

    digitalWrite(black, 0);
    digitalWrite(brown, 1);
    digitalWrite(orange, 1);
    digitalWrite(yellow, 0);
    delay(10);  
    i--;
    if (i < 1) break;
    
  }
  

  // all outputs to stepper off
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);


  }

  void refreshLCD(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write(stepCycleArray[stepArrayIndex]);
    lcd.setCursor(0, 1);
    lcd.write(stepCount);
  }

