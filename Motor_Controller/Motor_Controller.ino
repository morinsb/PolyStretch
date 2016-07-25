/*


 */

#include <LiquidCrystal.h>


// initialize the stepper library on pins 8 through 11:

float stepCount = 0;  // number of steps the motor has taken
int stepArrayIndex = 4;
int stepCycleArray[] = {-100, -10, -5, -1, 1, 5, 10, 50, 100, 500, 1000, 10000};
int currentStepperPosition = 0;
boolean calibrationMode = false;


#define ENABLE 10

#define black 9  // In1
#define brown 8  // In2
#define orange 1  // In3
#define yellow 0  // In4

#define triggerButton 11
#define resetButton 12
#define upButton 13

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  
  pinMode(ENABLE, OUTPUT);
  pinMode(black, OUTPUT);
  pinMode(brown, OUTPUT);
  pinMode(orange, OUTPUT);
  pinMode(yellow, OUTPUT);

  digitalWrite(ENABLE, LOW);
  digitalWrite(black, LOW);
  digitalWrite(brown, LOW);
  digitalWrite(orange, LOW);
  digitalWrite(yellow, LOW);
  
  pinMode(triggerButton, INPUT);
  digitalWrite(triggerButton, HIGH);
  pinMode(resetButton, INPUT);
  
  pinMode(upButton, INPUT);
  //digitalWrite(upButton, HIGH);

  lcd.begin(16,2);
  refreshLCD();
}

void loop() {
  if(digitalRead(upButton) == HIGH && digitalRead(resetButton) == HIGH){
    calibrationMode = !calibrationMode;
    refreshLCD();
    delay(2000);
  } 
  else if(digitalRead(upButton) == HIGH){
    stepArrayIndex++;
    if(stepArrayIndex > 11){
      stepArrayIndex = 0;  
    }
    refreshLCD();
    delay(500);
  }
  
  else if(digitalRead(resetButton) == HIGH){
    delay(2000);
    if( digitalRead(resetButton) == HIGH){
      lcd.clear();
      lcd.print("Resetting...");
      if(stepCount > 0){
        stepMotorReverse(-stepCount, currentStepperPosition); 
      }
      else{
        stepMotorForward(-stepCount, currentStepperPosition);  
      } 
      stepCount = 0;
      refreshLCD();
    }
  }
  else if(digitalRead(triggerButton) == HIGH){
    lcd.clear();
    lcd.print("Stepping...");
      stepMotorForward(stepCycleArray[stepArrayIndex], currentStepperPosition);
      refreshLCD();
  }
}

void stepMotorReverse(int i, int curPos){
    i = -i;
    digitalWrite(ENABLE, HIGH);
    while (true)   {
      if(curPos < 0 || curPos == 1){
        digitalWrite(black, 0);
        digitalWrite(brown, 1);
        digitalWrite(orange, 1);
        digitalWrite(yellow, 0);
        delay(10);  
        i--;
        currentStepperPosition = 0;
        curPos = -1;
      }
      if (i < 1) break;
  
      if(curPos < 0 || curPos ==  0){
        digitalWrite(black, 0);
        digitalWrite(brown, 1);
        digitalWrite(orange, 0);
        digitalWrite(yellow, 1);
        delay(10);
        i--;
        currentStepperPosition = 3;
        curPos = -1;
      }
      if (i < 1) break;
  
      if(curPos < 0 || curPos == 3){
        digitalWrite(black, 1);
        digitalWrite(brown, 0);
        digitalWrite(orange, 0);
        digitalWrite(yellow, 1);
        delay(10);  
        i--;
        currentStepperPosition = 2;
        curPos = -1;
      }
      if (i < 1) break;
  
      digitalWrite(black, 1);
      digitalWrite(brown, 0);
      digitalWrite(orange, 1);
      digitalWrite(yellow, 0);
      delay(10);
      i--;
      currentStepperPosition = 1;
      curPos = -1;
      if (i < 1) break;

  }

  digitalWrite(ENABLE, LOW);
  delay(1000);
}

void stepMotorForward(int i, int curPos){
   if(i > 0 && !calibrationMode){
    stepCount += i;
   }
   if(i < 0){
    stepMotorReverse(i, curPos); 

    if(!calibrationMode){
      stepCount += i;
    }
   } 
   
   digitalWrite(ENABLE, HIGH);
  while(true){
    if(! curPos > 0){
      digitalWrite(black, 1);
      digitalWrite(brown, 0);
      digitalWrite(orange, 1);
      digitalWrite(yellow, 0);
      delay(10);
      i--;
      currentStepperPosition = 1;
    } else{
      curPos--;  
    }
    if (i < 1) break; 


    if(! curPos > 0){
      digitalWrite(black, 1);
      digitalWrite(brown, 0);
      digitalWrite(orange, 0);
      digitalWrite(yellow, 1);
      delay(10);  
      i--;
      currentStepperPosition = 2;
    } else {
      curPos--;  
    }
    
    if (i < 1) break;

    if(! curPos > 0){
      digitalWrite(black, 0);
      digitalWrite(brown, 1);
      digitalWrite(orange, 0);
      digitalWrite(yellow, 1);
      delay(10);
      i--;
      currentStepperPosition = 3;
    }
    if (i < 1) break;

    digitalWrite(black, 0);
    digitalWrite(brown, 1);
    digitalWrite(orange, 1);
    digitalWrite(yellow, 0);
    delay(10);  
    i--;
    currentStepperPosition = 0;
    if (i < 1) break;
    
   }
 

  // enable stepper off
  digitalWrite(ENABLE, LOW);

  //Keeps the button from triggerinng multiple times in a single press
  delay(500);
  }


  void refreshLCD(){
    lcd.clear();
    lcd.setCursor(0,0);
    String str2 = "Selected: " + String(stepCycleArray[stepArrayIndex]);
    lcd.print(str2);
    
    //lcd.write(str2);
    
    lcd.setCursor(0, 1);
    if(calibrationMode){
      lcd.print("Calib mode...");  
    }
    else{
      String str = "Total: " + String(stepCount);
      lcd.print(str);
    }

    //lcd.write(str);
  }

