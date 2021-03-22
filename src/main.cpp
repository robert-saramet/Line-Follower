#include <Arduino.h>
#include <L298NX2.h>

#define motorA1 2
#define motorA2 3
#define motorB1 4
#define motorB2 5
#define motorA_EN 6
#define motorB_EN 7

short ls[6][2]; //ls[1-5][0] for line sensor pin numbers, ls[1-5][1] for sensor values
int firstPin = 22; //first line sensor pin number
float speedMultiplier = 1; //number to divide speed by

L298NX2 robot(motorA_EN, motorA1, motorA2, motorB_EN, motorB1, motorB2); //initialize motor driver

//get value of each line sensor and store it in array
void readLine(){
    for(int i = 1; i <= 5; i++){
        ls[i][1] = digitalRead(ls[i][0]);
    }
}

void steer(int speedA, int SpeedB){
    robot.setSpeedA(speedA / speedMultiplier);
    robot.setSpeedB(SpeedB /speedMultiplier);
}

void followLine(){
    readLine();
    if (ls[1][1]==0 && ls[2][1]==0 && ls[3][1]==1 && ls[4][1]==0 && ls[5][1]==0){ 
        //Serial.println("00100");
        robot.setSpeed(255 / speedMultiplier);
        robot.forward();
    }
    else if (ls[1][1]==0 && ls[2][1]==1 && ls[3][1]==1 && ls[4][1]==1 && ls[5][1]==0){ 
        //Serial.println("01110");
        robot.setSpeed(255 / speedMultiplier);
        robot.forward();
    }
    else if (ls[1][1]==0 && ls[2][1]==1 && ls[3][1]==1 && ls[4][1]==0 && ls[5][1]==0){ 
        //Serial.println("01100");
        steer(0, 255);
        robot.backwardA();
        robot.forwardB();
    }
    else if (ls[1][1]==0 && ls[2][1]==1 && ls[3][1]==0 && ls[4][1]==0 && ls[5][1]==0){ 
        //Serial.println("01000");
        steer(80, 255);
        robot.backwardA();
        robot.forwardB();
    }
    else if (ls[1][1]==1 && ls[2][1]==1 && ls[3][1]==0 && ls[4][1]==0 && ls[5][1]==0){ 
        //Serial.println("11000");
        steer(160, 255);
        robot.backwardA();
        robot.forwardB();
    }
    else if (ls[1][1]==1 && ls[2][1]==0 && ls[3][1]==0 && ls[4][1]==0 && ls[5][1]==0){ 
        //Serial.println("10000");
        steer(255, 255);
        robot.backwardA();
        robot.forwardB();
    }
    else if (ls[1][1]==0 && ls[2][1]==0 && ls[3][1]==1 && ls[4][1]==1 && ls[5][1]==0){ 
        //Serial.println("00110");
        steer(255, 0);
        robot.forwardA();
        robot.backwardB();
    }
    else if (ls[1][1]==0 && ls[2][1]==0 && ls[3][1]==0 && ls[4][1]==1 && ls[5][1]==0){ 
        //Serial.println("00010");
        steer(255, 80);
        robot.forwardA();
        robot.backwardB();
    }
    else if (ls[1][1]==0 && ls[2][1]==0 && ls[3][1]==0 && ls[4][1]==0 && ls[5][1]==1){ 
        //Serial.println("00011");
        steer(255, 160);
        robot.forwardA();
        robot.backwardB();
    }
    else if (ls[1][1]==0 && ls[2][1]==0 && ls[3][1]==0 && ls[4][1]==0 && ls[5][1]==1){ 
        //Serial.println("00001");
        steer(255, 255);
        robot.forwardA();
        robot.backwardB();
    }
    else if (ls[1][1]==0 && ls[2][1]==1 && ls[3][1]==1 && ls[4][1]==1 && ls[5][1]==0){ 
        //Serial.println("01110");
        robot.setSpeed(255 / speedMultiplier);
        robot.forward();
    }
    else if (ls[1][1]==1 && ls[2][1]==1 && ls[3][1]==1 && ls[4][1]==0 && ls[5][1]==0){ 
        //Serial.println("11100");
        steer(128, 255);
        robot.backwardA();
        robot.forwardB();
    }
    else if (ls[1][1]==0 && ls[2][1]==0 && ls[3][1]==1 && ls[4][1]==1 && ls[5][1]==1){ 
        //Serial.println("00111");
        steer(255, 128);
        robot.forwardA();
        robot.backwardB();
    }
    else{
      //Serial.println("ERROR");
    }
}

void setup(){
    //Serial.begin(9600);
    robot.setSpeed(255);
    robot.stop();

    //initialize line sensor pins as inputs
    for(int i = 1; i <= 5; i++){
        ls[i][0] = firstPin - 1 + i;
        pinMode(ls[i][0], INPUT);
    }
}

void loop(){
    followLine();
}