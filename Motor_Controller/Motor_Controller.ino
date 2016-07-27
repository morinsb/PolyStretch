
// initialize the stepper on pins 8 through 11:

float stepCount = 0;  // number of steps the motor has taken
int stepArrayIndex = 4;
int currentStepperPosition = 0;
boolean calibrationMode = false;
boolean torqueOn = false;


#define ENABLE 10

#define black 9  // In1
#define brown 8  // In2
#define orange 4  // In3
#define yellow 3  // In4

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

  //lcd.begin(16,2);
  Serial.begin(9600);
  refreshLCD();
  Serial.println("Type 'Help' to get a list of commands at any time");
}

void loop() {
  
  if(Serial.available()){
    String input = Serial.readString();
    if(input.equalsIgnoreCase("Calibration")){
      calibrationMode = !calibrationMode;
      refreshLCD();
    } 
    
   else if(input.equalsIgnoreCase("Help")){
      for(int i = 0; i < 5; i++){
        Serial.println();
        }
       Serial.println("-------------------------------------------------------------------");
       Serial.println("To reset, type 'Reset'");
       Serial.println("To enter calibration mode, type 'Calibration'");
       Serial.println("To get a list of commands, type 'Help'");
       Serial.println("To step the motor, type in a positive or negative integer");
       Serial.println("To turn the motor on, type 'Motor'");
       Serial.println("-------------------------------------------------------------------");
     }
    else if(input.equalsIgnoreCase("Reset")){
      
        //lcd.clear();
        for(int i = 0; i < 5; i++){
        Serial.println();
        }
       Serial.println("-------------------------------------------------------------------");
       Serial.println("Resetting...");
       Serial.println("-------------------------------------------------------------------");
        if(stepCount > 0){
          stepMotorForward(stepCount, currentStepperPosition); 
        }
        else{
          stepMotorForward(stepCount, currentStepperPosition);  
        } 
        stepCount = 0;
        refreshLCD();
      
    }

    else if(input.equalsIgnoreCase("Motor")){
        for(int i = 0; i < 5; i++){
        Serial.println();
        }
       if(torqueOn){
          digitalWrite(ENABLE, LOW);
         Serial.println("-------------------------------------------------------------------");
         Serial.println("Motor is now off");
         Serial.println("-------------------------------------------------------------------");
         torqueOn = !torqueOn;
       }
       else{
          digitalWrite(ENABLE, HIGH);
          Serial.println("-------------------------------------------------------------------");
         Serial.println("Motor is now on");
         Serial.println("-------------------------------------------------------------------");
         torqueOn = !torqueOn;
        }
    }
    
    else if(input.toInt() != 0){
      for(int i = 0; i <5; i++){
          Serial.println();
      }
      Serial.println("-------------------------------------------------------------------");
      if(torqueOn){
        int inputInt = input.toInt();
         Serial.println("Stepping...");
         Serial.println("-------------------------------------------------------------------");
         stepMotorForward(-inputInt, currentStepperPosition);
         refreshLCD();
      }
      else{
        Serial.println("Please turn on the motor");
        Serial.println("-------------------------------------------------------------------");
      }
     }
  }
}

void stepMotorReverse(int i, int curPos){
  
    i = -i;
    //digitalWrite(ENABLE, HIGH);
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

  //digitalWrite(ENABLE, LOW);
  delay(1000);
}

void stepMotorForward(int i, int curPos){
   if(i > 0 && !calibrationMode){
    stepCount -= i;
   }
   if(i < 0){
    stepMotorReverse(i, curPos); 

    if(!calibrationMode){
      stepCount -= i;
    }
   } 
   
   //digitalWrite(ENABLE, HIGH);
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
  //digitalWrite(ENABLE, LOW);

  //Keeps the button from triggerinng multiple times in a single press
  delay(500);
   
    }
  
  
    void refreshLCD(){
      //lcd.clear();
      for(int i = 0; i <5; i++){
        Serial.println();
       }
       Serial.println("-------------------------------------------------------------------");
      if(calibrationMode){
        Serial.println("Calibration mode...");  
      }
      else{
        String str = "Total Steps: " + String(stepCount);
        Serial.println(str);
      }
  
      Serial.println("-------------------------------------------------------------------");
    
  }

