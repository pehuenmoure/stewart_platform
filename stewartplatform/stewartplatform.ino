#include <Wire.h>
#include <EEPROM.h>
#include "wiinunchuck.h"


int loop_count = 0;
int led = 14;

// Define Motor Constants
#define relay1 A5   // motor 1
#define relay2 3
#define relay3 4   // motor 2
#define relay4 5
#define relay5 6   // motor 3
#define relay6 7
#define relay7 8   // motor 4
#define relay8 9
#define relay9 10  // motor 5
#define relay10 11 
#define relay11 12 // motor 6
#define relay12 13

void setup() {
  // Initialize motor and led pins
  pinMode(led, OUTPUT);
  pinMode(relay12, OUTPUT);
  pinMode(relay11, OUTPUT);
  pinMode(relay10, OUTPUT);
  pinMode(relay9, OUTPUT);
  pinMode(relay8, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay1, OUTPUT);
  
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  digitalWrite(relay8, LOW);
  digitalWrite(relay9, LOW);
  digitalWrite(relay10, LOW);
  digitalWrite(relay11, LOW);
  digitalWrite(relay12, LOW); 

  //Initialize serial ports and nunchuk
  Serial.begin(19200);
  
  nunchuk_setpowerpins();    // set power pins for Wii Nunchuk
  nunchuk_init();            // initilization for the Wii Nunchuk
  delay(250);
  
  while(!nunchuk_get_data()){ // loop until Wii Nunchuk is connected to Nunchucky
    Serial.println("Stuck in loop");
    nunchuk_init();
    delay(250);
    nunchuk_get_data();
    digitalWrite(led, HIGH); 
    delay(250);
    digitalWrite(led, LOW); 
    delay(500);
  }

//  nunchuk_calibrate_joy();
  
  digitalWrite(led, HIGH);  // let user know they can select mode within (5 seconds)
  delay(5000);
  
  Serial.print("WiiChuck ready\n");
  
}

void loop() {
  // put your main code here, to run repeatedly:
   if( loop_count > 100 ) { // every 10 msecs get new data
        loop_count = 0;

        if(nunchuk_get_data()){
          
          int zbutton = nunchuk_zbutton();
          int cbutton = nunchuk_cbutton();
          int joyx = nunchuk_joy_x();
          int joyy = nunchuk_joy_y();
          int calib_joyx = nunchuk_cjoy_x();
          int calib_joyy = nunchuk_cjoy_y();
          Serial.print("zbutton: "); 
          Serial.print(zbutton);
          Serial.print("\tcbutton: ");
          Serial.print(cbutton);
          Serial.print("\tjoy x: "); 
          Serial.print(joyx);
          Serial.print("\tjoy y: ");
          Serial.print(joyy);
          Serial.print("\tCalibrated joy x: "); 
          Serial.print(calib_joyx);
          Serial.print("\tCalibrated joy y: ");
          Serial.println(calib_joyy);
          move_motors(cbutton, zbutton, joyx, joyy);
        }else{
          Serial.println("Data not ready");
        }
            
    }
    loop_count++;
    delay(1);
  
}

void move_motors(int c, int z, int x, int y){
  if (c == 1 && z == 1){
    Serial.println("twist");
    twist();
  }else if (c == 1){
    Serial.println("up");
    move_up();
  }else if (z ==1){
    Serial.println("down");
    move_down();
  } 
  else if (y > 160){
    if (y > 238){
    Serial.println("tilt forward");
    tilt_forward();
    }
    else if (x > 139){
      Serial.println("tilt forward + right");
      tilt_fRight();
    }  
    else if (x < 121){
      Serial.println("tilt forward + left");
      tilt_fLeft();
    }
   }
   else if (y < 95){
    if (y < 17){
    Serial.println("tilt backward");
    tilt_backward();
    }
    else if (x > 139){
      Serial.println("tilt backward + right");
      tilt_bRight();
    }  
    else if (x < 121){
      Serial.println("tilt backward + left");
      tilt_bLeft();
    }
   }else if (x < 53){
     Serial.println("tilt left");
      tilt_left(); 
  } else if (x > 207){
     Serial.println("tilt right");
      tilt_right();
  } 
  else if (c==0 && z == 0){
    Serial.println("stop");
    stop_moving();
  }
}





void move_up(){
  digitalWrite(relay1, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay7, HIGH);
  digitalWrite(relay9, HIGH);
  digitalWrite(relay11, HIGH);

  digitalWrite(relay2, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay8, LOW);
  digitalWrite(relay10, LOW);
  digitalWrite(relay12, LOW);
}

void move_down(){
  digitalWrite(relay2, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay8, HIGH);
  digitalWrite(relay10, HIGH);
  digitalWrite(relay12, HIGH);
  
  digitalWrite(relay1, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay7, LOW);
  digitalWrite(relay9, LOW);
  digitalWrite(relay11, LOW);
  
}

void twist(){
  digitalWrite(relay1, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay9, HIGH);

  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  digitalWrite(relay8, LOW);
  digitalWrite(relay10, LOW);
  digitalWrite(relay11, LOW);
  digitalWrite(relay12, LOW); 
}

void stop_moving(){
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  digitalWrite(relay8, LOW);
  digitalWrite(relay9, LOW);
  digitalWrite(relay10, LOW);
  digitalWrite(relay11, LOW);
  digitalWrite(relay12, LOW); 
}

void tilt_forward(){
  digitalWrite(relay1, LOW);  // motor 1
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);  // motor 2
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);  // motor 3
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH); // motor 4
  digitalWrite(relay8, LOW);  
  digitalWrite(relay9, LOW); // motor 5
  digitalWrite(relay10, LOW);
  digitalWrite(relay11, LOW); // motor 6
  digitalWrite(relay12, HIGH);   
}

void tilt_backward(){
 digitalWrite(relay1, HIGH);  // motor 1
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);  // motor 2
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);  // motor 3
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW); // motor 4
  digitalWrite(relay8, HIGH);  
  digitalWrite(relay9, LOW); // motor 5
  digitalWrite(relay10, LOW);
  digitalWrite(relay11, HIGH); // motor 6
  digitalWrite(relay12, LOW); 
}

void tilt_left(){
  digitalWrite(relay1, HIGH);  // motor 1
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);  // motor 2
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);  // motor 3
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW); // motor 4
  digitalWrite(relay8, HIGH);  
  digitalWrite(relay9, LOW); // motor 5
  digitalWrite(relay10, HIGH);
  digitalWrite(relay11, LOW); // motor 6
  digitalWrite(relay12, HIGH); 
}

void tilt_right(){
  digitalWrite(relay1, LOW);  // motor 1
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);  // motor 2
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);  // motor 3
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH); // motor 4
  digitalWrite(relay8, LOW);  
  digitalWrite(relay9, HIGH); // motor 5
  digitalWrite(relay10, LOW);
  digitalWrite(relay11, HIGH); // motor 6
  digitalWrite(relay12, LOW); 
}

void tilt_fRight(){
  digitalWrite(relay1, LOW);  // motor 1
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);  // motor 2
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);  // motor 3
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH); // motor 4
  digitalWrite(relay8, LOW);  
  digitalWrite(relay9, HIGH); // motor 5
  digitalWrite(relay10, LOW);
  digitalWrite(relay11, LOW); // motor 6
  digitalWrite(relay12, LOW); 
}


void tilt_bRight(){
  digitalWrite(relay1, LOW);  // motor 1
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);  // motor 2
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);  // motor 3
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW); // motor 4
  digitalWrite(relay8, LOW);  
  digitalWrite(relay9, HIGH); // motor 5
  digitalWrite(relay10, LOW);
  digitalWrite(relay11, HIGH); // motor 6
  digitalWrite(relay12, LOW); 
}


void tilt_fLeft(){
  digitalWrite(relay1, LOW);  // motor 1
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);  // motor 2
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);  // motor 3
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW); // motor 4
  digitalWrite(relay8, LOW);  
  digitalWrite(relay9, LOW); // motor 5
  digitalWrite(relay10, HIGH);
  digitalWrite(relay11, LOW); // motor 6
  digitalWrite(relay12, HIGH); 
}

void tilt_bLeft(){
  digitalWrite(relay1, HIGH);  // motor 1
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);  // motor 2
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);  // motor 3
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW); // motor 4
  digitalWrite(relay8, HIGH);  
  digitalWrite(relay9, LOW); // motor 5
  digitalWrite(relay10, HIGH);
  digitalWrite(relay11, LOW); // motor 6
  digitalWrite(relay12, LOW); 

}




