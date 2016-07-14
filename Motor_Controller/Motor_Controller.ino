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
int currentStepperPosition = 0;


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
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(black, OUTPUT);
  pinMode(brown, OUTPUT);
  pinMode(orange, OUTPUT);
  pinMode(yellow, OUTPUT);

  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(black, LOW);
  digitalWrite(brown, LOW);
  digitalWrite(orange, LOW);
  digitalWrite(yellow, LOW);
  
  pinMode(triggerButton, INPUT);
  pinMode(resetButton, INPUT);
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);

  lcd.begin(16,2);
  lcd.write("Hello, world!");
}

void loop() {
  if(digitalRead(downButton) == HIGH){
    stepArrayIndex--;
    if(stepArrayIndex < 0) {
      stepArrayIndex = 11;  
    }
    refreshLCD();
  }
  if(digitalRead(upButton) == HIGH){
    stepArrayIndex++;
    if(stepArrayIndex > 11){
      stepArrayIndex = 0;  
    }
    refreshLCD();
  }
  if(digitalRead(resetButton) == HIGH){
    stepMotorForward(-stepCount, currentStepperPosition);  
    refreshLCD();
  }
  else if(digitalRead(triggerButton) == HIGH){
      stepMotorForward(stepCycleArray[stepArrayIndex], currentStepperPosition);
      refreshLCD();
  }
  
}

void stepMotorForward(int i, int curPos){
   if(i > 0){
    stepCount += i;
   }
   digitalWrite(ENA, HIGH);
   digitalWrite(ENB, HIGH);
  while(true){
    if(! curPos > 0){
      digitalWrite(black, 1);
      digitalWrite(brown, 0);
      digitalWrite(orange, 1);
      digitalWrite(yellow, 0);
      delay(1000);
      i--;
      currentStepperPosition = 0;
    } else{
      curPos--;  
    }
    if (i < 1) break; 


    if(! curPos > 0){
      digitalWrite(black, 1);
      digitalWrite(brown, 0);
      digitalWrite(orange, 0);
      digitalWrite(yellow, 1);
      delay(1000);  
      i--;
      currentStepperPosition = 1;
    } else {
      curPos--;  
    }
    
    if (i < 1) break;

    if(! curPos > 0){
      digitalWrite(black, 0);
      digitalWrite(brown, 1);
      digitalWrite(orange, 0);
      digitalWrite(yellow, 1);
      delay(1000);
      i--;
      currentStepperPosition = 2;
    }
    if (i < 1) break;

    digitalWrite(black, 0);
    digitalWrite(brown, 1);
    digitalWrite(orange, 1);
    digitalWrite(yellow, 0);
    delay(1000);  
    i--;
    currentStepperPosition = 3;
    if (i < 1) break;
    
  }
  

  // all outputs to stepper off
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);


  }

  void refreshLCD(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write(" Selected: " + stepCycleArray[stepArrayIndex]);
    lcd.setCursor(0, 1);
    lcd.write("Total: " + stepCount);
  }

