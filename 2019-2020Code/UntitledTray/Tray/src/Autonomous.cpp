#include "vex.h"
using namespace vex;

bool autoRunning = false;
int autoVar = 0;

int autoVarReturn(){
  return autoVar;
}

void deploy(){
  armEncoder(UP, 100, 150);
  armEncoder(DOWN, 100, 150);
}
int go1(){
  goP(FORWARD, 30, 38, 4);
  turnP(RIGHT, 100, 90, 5);
  goP(FORWARD, 100, 10, 1);
  turnP(RIGHT, 100, 90, 5);
  goP(FORWARD, 100, 50, 3);
  turnP(LEFT, 100, 30, 3);
  goP(FORWARD, 100, 15, 2);
  return 0;
}

void test(){
  trayTime(UNTILT, 100, 200);
  trayBrake();
  intake(IN, 100);
}

void runAutoTester(){
  //deploy
  armEncoder(UP, 100, 150);
  armGo(DOWN, 100);
  tray(UNTILT, 15);
  intake(IN, 100);
  //first 5 cubes
  driveEncoder(FORWARD, 100, 4);
  goP(FORWARD, 40, 36, 10);
  armGo(DOWN, 20);
  wait(250, msec);
  trayTime(TILT, 30, 75);
  trayBrake();
  driveBrake();
  wait(50, msec);
  armEncoder(UP, 100, 70);
  driveEncoder(FORWARD, 10, 4);
  goP(FORWARD, 60, 16, 9);
  armGo(DOWN, 100);
  goP(FORWARD, 70, 20, 10);
  armCoast();
  wait(100, msec);
  armBrake();
  //back up
  driveEncoder(BACKWARD, 70, 13.5);
  wait(250,msec);
  turnEncoder(LEFT, 60, 35);
  //wait(100,msec);
  driveEncoder(BACKWARD, 70, 30);
  //intakeBrake();
  //goP(BACKWARD, 40, 55, 10);
  //driveTime(BACKWARD, 30, 200);
  //align with cubes 6-9
  //turnPStop(RIGHT, 70, 90, 65);
  wait(250,msec);
  turnEncoder(RIGHT, 70, 50);
  intake(IN, 100);
  //last 4 cubes
  driveEncoder(FORWARD, 31, 37);
  //goPStop(FORWARD, 50, 50, 10);
  
  //align with zone
  goPStop(BACKWARD, 70, 32, 10);
  //turnP(RIGHT, 150, 115, 40);
  turnEncoder(RIGHT, 70, 112);
  intakeBrake();                                                
  //place stack
  driveEncoder(FORWARD, 40, 14);
  //goPStop(FORWARD, 60, 30, 10);
  armGo(DOWN, 60);
  intake(OUT, 20);
  trayP(70, 600);
  intake(OUT, 40);
  driveEncoder(BACKWARD, 25, 40);
}










void runAutoTesterBlue(){
  //deploy
  armEncoder(UP, 100, 150);
  armGo(DOWN, 100);
  tray(UNTILT, 15);
  intake(IN, 100);
  //first 5 cubes
  driveEncoder(FORWARD, 100, 4);
  goP(FORWARD, 40, 36, 10);
  armGo(DOWN, 20);
  wait(250, msec);
  trayTime(TILT, 30, 75);
  trayBrake();
  driveBrake();
  wait(50, msec);
  armEncoder(UP, 100, 70);
  driveEncoder(FORWARD, 10, 4);
  goP(FORWARD, 60, 16, 9);
  armGo(DOWN, 100);
  goP(FORWARD, 70, 20, 10);
  armCoast();
  wait(100, msec);
  armBrake();
  //back up
  driveEncoder(BACKWARD, 70, 13.5);
  wait(250,msec);
  turnEncoder(RIGHT, 60, 35);
  //wait(100,msec);
  driveEncoder(BACKWARD, 70, 30);
  //intakeBrake();
  //goP(BACKWARD, 40, 55, 10);
  //driveTime(BACKWARD, 30, 200);
  //align with cubes 6-9
  //turnPStop(RIGHT, 70, 90, 65);
  wait(250,msec);
  turnEncoder(LEFT, 70, 50);
  intake(IN, 100);
  //last 4 cubes
  driveEncoder(FORWARD, 31, 37);
  //goPStop(FORWARD, 50, 50, 10);
  
  //align with zone
  goPStop(BACKWARD, 70, 32, 10);
  //turnP(RIGHT, 150, 115, 40);
  turnEncoder(LEFT, 70, 112);
  intakeBrake();                                                
  //place stack
  driveEncoder(FORWARD, 40, 14);
  //goPStop(FORWARD, 60, 30, 10);
  armGo(DOWN, 60);
  intake(OUT, 20);
  trayP(70, 600);
  intake(OUT, 40);
  driveEncoder(BACKWARD, 25, 40);
}




void runAutoPID(){
turnP(RIGHT, 130, 115, 40);
}
void runAutoenc(){
turnEncoder(RIGHT, 70, 30);
}

void runAuto10Test(){
  deploy();
  armGo(DOWN, 30);
  intake(IN, 100);
  trayTime(UNTILT, 100, 200);
  trayBrake();
  goP(FORWARD, 40, 41, 10);
  trayTime(TILT, 30, 75);
  armEncoder(UP, 100, 60);
  goP(FORWARD, 60, 20, 9);
  armGo(DOWN, 100);
  goP(FORWARD, 70, 11, 6);
  armCoast();
  wait(100, msec);
  armBrake();
  intakeBrake();
  turnP(RIGHT, 100, 80, 30);
  intake(IN, 100);
  goP(FORWARD, 70, 11, 6);
  turnP(RIGHT, 100, 60, 30);
  goP(FORWARD, 70, 50, 10);
  /*armEncoder(UP, 100, 40);
  turnP(RIGHT, 100, 90, 5);
  goP(FORWARD, 100, 10, 1);
  turnP(RIGHT, 100, 90, 5);
  goP(FORWARD, 100, 50, 3);
  turnP(LEFT, 100, 30, 3);
  goP(FORWARD, 100, 15, 2);
  intakeBrake();
  trayP(100, 600);*/

}

void runAuto10Small(){

}

void runAuto(int autoNumber){
  autoRunning = true;
  if (autoNumber == 0){
    deploy();
  }  
  else if (autoNumber == 1){
    runAutoTester();
  }
  else if (autoNumber == 2){
    
  }
  else if (autoNumber == 3){
    runAutoTesterBlue();
  }
  else if (autoNumber == 4){
    
  }
}

int autoSelector(){
  while (!(autoRunning)){
    if ((Brain.Screen.pressing()) && (autoVar < TOTAL_AUTONS)){
      autoVar++;
    }
    else if ((Brain.Screen.pressing()) && (autoVar >= TOTAL_AUTONS)){
      autoVar = 0;
    }
  }
  return 0;
}


int autoIndicator(){
  while (!(autoRunning)){
    if (autoVar == 0){
      Brain.Screen.clearScreen();
      Brain.Screen.drawRectangle(100, 100, 100, 100, purple);
      Brain.Screen.print("deploy");
    }
    else if (autoVar == 1){
      Brain.Screen.clearScreen();
      Brain.Screen.drawRectangle(100, 100, 100, 100, red);
      Brain.Screen.print("large zone");
    }
    else if (autoVar == 2){
      Brain.Screen.clearScreen();
      Brain.Screen.drawRectangle(100, 100, 100, 100, red);
      Brain.Screen.print("small zone");
    }
    else if (autoVar == 3){
      Brain.Screen.clearScreen();
      Brain.Screen.drawRectangle(100, 100, 100, 100, blue);
      Brain.Screen.print("large zone");
    }
    else if (autoVar == 4){
      Brain.Screen.clearScreen();
      Brain.Screen.drawRectangle(100, 100, 100, 100, blue);
      Brain.Screen.print("small zone");
    }
  }
  return 0;
}
