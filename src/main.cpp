#include <Arduino.h>
#include <L298NX2.h>

#define motorA1 2
#define motorA2 3
#define motorB1 4
#define motorB2 5
#define motorA_EN 6
#define motorB_EN 7

short ls[6][2];

L298NX2 robot(motorA_EN, motorA1, motorA2, motorB_EN, motorB1, motorB2);


void readLine(){
    for(int i = 1; i <= 5; i++){
        ls[i][1] = digitalRead(ls[i][0]);
    }
}

void steer(int speedA, int SpeedB){
    robot.setSpeedA(speedA);
    robot.setSpeedB(SpeedB);
}

void followLine(){
    readLine();
    if (ls[1][1]==0 && ls[2][1]==0 && ls[3][1]==1 && ls[4][1]==0 && ls[5][1]==0){ 
        Serial.println("00100");
        robot.setSpeed(255);
        robot.forward();
    }
    else if (ls[1][1]==0 && ls[2][1]==1 && ls[3][1]==1 && ls[4][1]==1 && ls[5][1]==0){ 
        Serial.println("00100");
        robot.forward();
    }
    else if (ls[1][1]==0 && ls[2][1]==1 && ls[3][1]==1 && ls[4][1]==0 && ls[5][1]==0){ 
        Serial.println("01100");
        steer(192, 256);
    }
    else if (ls[1][1]==0 && ls[2][1]==1 && ls[3][1]==0 && ls[4][1]==0 && ls[5][1]==0){ 
        Serial.println("01000");
        steer(128, 256);
    }
    else if (ls[1][1]==1 && ls[2][1]==1 && ls[3][1]==0 && ls[4][1]==0 && ls[5][1]==0){ 
        Serial.println("11000");
        steer(64, 256);
    }
    else if (ls[1][1]==1 && ls[2][1]==0 && ls[3][1]==0 && ls[4][1]==0 && ls[5][1]==0){ 
        Serial.println("10000");
        steer(0, 256);
    }
    else if (ls[1][1]==0 && ls[2][1]==0 && ls[3][1]==1 && ls[4][1]==1 && ls[5][1]==0){ 
        Serial.println("00110");
        steer(256, 192);
    }
    else if (ls[1][1]==0 && ls[2][1]==0 && ls[3][1]==0 && ls[4][1]==1 && ls[5][1]==0){ 
        Serial.println("00010");
        steer(256, 128);
    }
    else if (ls[1][1]==0 && ls[2][1]==0 && ls[3][1]==0 && ls[4][1]==0 && ls[5][1]==1){ 
        Serial.println("00011");
        steer(256, 64);
    }
    else if (ls[1][1]==0 && ls[2][1]==0 && ls[3][1]==0 && ls[4][1]==0 && ls[5][1]==1){ 
        Serial.println("00001");
        steer(256, 0);
    }
    else{
      Serial.println("ERROR");
    }
}

void setup(){
    Serial.begin(9600);
    robot.setSpeed(255);
    robot.stop();
    for(int i = 1; i <= 5; i++){
        ls[i][0] = 21 + i;
        pinMode(ls[i][0], INPUT);
    }
}

void loop(){
    followLine();
}