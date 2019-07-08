//#include "robot-config.h"
#include "PID.cpp"
#include <string>
#include <cmath>x

double speed1;

float stickDead = 6;
int brakeVar = 0;
int intakeBrakeVar = 0;
double turnSpeed = 1;
double straightSpeed = 1;
double hSpeed = 1;
double mechSpeed = 1;
double inchConvertVal = 28.5;
double degreeConvertVal = 1;
double autoCol;
double autoPos;
bool autoRunning = true;
bool running = true;
double error;
double target;
bool targetToggle = true;

#define FORWARD 1
#define BACKWARD -1
#define REVERSE -1
#define FAST 200
#define MEDIUM 100
#define SLOW 50
#define ROBOTCFAST 127
#define LEFT 1
#define RIGHT -1
#define RED 0
#define BLUE 1
#define RIGHT_AXIS_Y 2
#define LEFT_AXIS_Y 3
#define RIGHT_AXIS_X 1
#define LEFT_AXIS_X 4
//int autoCol = 0;
//int autoNum = 0;

//get joystick values
double getAnalog(int axis){
  if (axis  == 1){
    return Controller1.Axis1.value();
  }
  if (axis == 2){
    return Controller1.Axis2.value();
  }
  if (axis == 3){
    return Controller1.Axis3.value();
  }
  if (axis == 4){
    return Controller1.Axis4.value();
  }
  else{
    return 100;
  }

}

//task sleep shortcut (wait1Msec())
void wait(int time){
    vex::task::sleep(time);
}

//artificial yield example
void yieldaction(int time){
  int i = 0;
  while (i < time){
    task::sleep(1);
    i++;
  }

  i = 0;
}


//DRIVE COMMANDS

//stops drive
void stopall(int time){
    vex::task::sleep(time);
    Lwheel.stop();
    Rwheel.stop();
    Lwheel2.stop();
    Rwheel2.stop();
    
}
//activates brake type hold
void baseBrakeHold (int time){
    vex::task::sleep(time);
    Lwheel.stop(vex::brakeType::hold);
    Lwheel2.stop(vex::brakeType::hold);
    Rwheel.stop(vex::brakeType::hold);
    Rwheel2.stop(vex::brakeType::hold);
}
void hBrakeHold (int time){
    vex::task::sleep(time);
    Hwheel.stop(vex::brakeType::hold);
}
//sets base motors to coast
void baseBrakeCoast (int time){
    vex::task::sleep(time);
    Lwheel.stop(vex::brakeType::coast);
    Lwheel2.stop(vex::brakeType::coast);
    Rwheel.stop(vex::brakeType::coast);
    Rwheel2.stop(vex::brakeType::coast);
}
void hBrakeCoast (int time){
    vex::task::sleep(time);
    Hwheel.stop(vex::brakeType::coast);
}
void upBrake(){
  LUp.stop(vex::brakeType::hold);
  RUp.stop(vex::brakeType::hold);
}

//go straight using voltage (-12 to 12)
void govolt(float direction, float speed, float time){
    LB.spin(vex::directionType::fwd, speed*direction, vex::voltageUnits::volt);  
    LF.spin(vex::directionType::fwd, speed*direction, vex::voltageUnits::volt);
    RB.spin(vex::directionType::fwd, speed*direction, vex::voltageUnits::volt);  
    RF.spin(vex::directionType::fwd, speed*direction, vex::voltageUnits::volt);
    wait(time);
}

//USER CONTROL DRIVE COMMANDS
//right side of drive voltage (-100 to 100)
void setDriveRight(double speed){ 
    RB.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt);  
    RF.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt); 
}
void setDriveRF(double speed){
    RF.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt); 
}
void setDriveRB(double speed){
    RB.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt); 
}
//left side of drive voltage (-100 to 100)
void setDriveLeft(double speed){
  LB.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt);  
  LF.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt);
}
void setDriveLF(double speed){
  LF.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt); 
}
void setDriveLB(double speed){
  LB.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt); 
}

void setDriveBack(double speed){
  LB.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt); 
  RB.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt); 
}

void setDriveFront(double speed){
  LF.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt); 
  RF.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt); 
}


//runs center H wheel with voltage assuming H-Drive (-100 to 100)
void setDriveH(double speed){
  MH.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt);
}
//use with mechanum drive to strafe voltage (-100 to 100)
void strafeMech(double speed){
  LB.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt);  
  LF.spin(vex::directionType::fwd, -1*0.12*speed, vex::voltageUnits::volt);
  RB.spin(vex::directionType::fwd, -1*0.12*speed, vex::voltageUnits::volt);  
  RF.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt);
}
//drive straight voltage (-100 to 100)
void setDriveStraight(double speed){
  RB.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt);  
  RF.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt);
  LB.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt);  
  LF.spin(vex::directionType::fwd, 0.12*speed, vex::voltageUnits::volt);
}
//set each side of drive voltage (-100 to 100)
void setDrive(double leftspeed, double rightspeed){
  RB.spin(vex::directionType::fwd, 0.12*rightspeed, vex::voltageUnits::volt);  
  RF.spin(vex::directionType::fwd, 0.12*rightspeed, vex::voltageUnits::volt);
  LB.spin(vex::directionType::fwd, 0.12*leftspeed, vex::voltageUnits::volt);  
  LF.spin(vex::directionType::fwd, 0.12*leftspeed, vex::voltageUnits::volt);
}


//OTHER DRIVE COMMANDS
//this section needs to be cleaned up

void driveStraightEncoders(int direction, double speed, double degrees){
  Lwheel.startRotateFor(direction*degrees, rotationUnits::deg, direction*speed, velocityUnits::rpm);
  Lwheel2.startRotateFor(direction*degrees, rotationUnits::deg, direction*speed, velocityUnits::rpm);
  Rwheel.startRotateFor(direction*degrees, rotationUnits::deg, direction*speed, velocityUnits::rpm);
  Rwheel2.startRotateFor(direction*degrees, rotationUnits::deg, direction*speed, velocityUnits::rpm);
  /*Lwheel.stop();
  Lwheel2.stop();
  Rwheel.stop();
  Rwheel2.stop();*/
}
void stopDriveLeft(){
  LB.stop(brakeType::hold);
  LF.stop(brakeType::hold);
}
void stopDriveRight(){
  RB.stop(brakeType::hold);
  RF.stop(brakeType::hold);
}
void stopDriveH(){
  MH.stop(brakeType::hold);
}
void stopDriveFull(double time){
  wait(time);
  stopDriveLeft();
  stopDriveRight();
  stopDriveH();
}
void stopDrive(int time){
  wait(time);
  stopDriveLeft();
  stopDriveRight();
}
void spinEncoder(int direction, double speed, double degrees){
  while(abs(getSensorPos())<abs(degrees)){
    RB.spin(vex::directionType::fwd, direction*0.12*speed, vex::voltageUnits::volt);  
    RF.spin(vex::directionType::fwd, direction*0.12*speed, vex::voltageUnits::volt);
    LB.spin(vex::directionType::fwd, direction*0.12*speed, vex::voltageUnits::volt);  
    LF.spin(vex::directionType::fwd, direction*0.12*speed, vex::voltageUnits::volt);
  }
  Lwheel.stop();
  Lwheel2.stop();
  Rwheel.stop();
  Rwheel2.stop();
}


//PID COMMANDS
//go straight with PID
void straightPID(int direction, double speed, double degrees){
  double inches = degrees*inchConvertVal;
  double motorSpeed;
  while ((getSensorPos()) < abs(inches)){
    motorSpeed = calculatePID(2, 1, 0.01, 0.2*inches, 0.8*inches, 1, inches);
    setDriveStraight(direction*motorSpeed*speed);
  }
}

//turn with PID
void turnPID(int direction, double speed, double degrees){
  double turnDegrees = degrees*degreeConvertVal;
  double motorSpeed;
  while ((getSensorPos())<abs(turnDegrees)){
    motorSpeed = motorSpeed = calculatePID(2, 1, 0.01, 0.2*turnDegrees, 0.8*turnDegrees, 1, turnDegrees);
    setDrive(speed*direction*motorSpeed,speed*direction*motorSpeed*-1);
  }
}

void movebase(int speed){
    Lwheel.spin(vex::directionType::fwd,speed,vex::velocityUnits::rpm);
    Lwheel2.spin(vex::directionType::fwd,speed,vex::velocityUnits::rpm);
    Rwheel2.spin(vex::directionType::fwd,speed,vex::velocityUnits::rpm);
    Rwheel.spin(vex::directionType::fwd,speed,vex::velocityUnits::rpm);
}

void turnbase(int speed, int direction){
    Lwheel.spin(vex::directionType::fwd,speed*-1*direction,vex::velocityUnits::rpm);
    Lwheel2.spin(vex::directionType::fwd,speed*-1*direction,vex::velocityUnits::rpm);
    Rwheel2.spin(vex::directionType::fwd,speed*1*direction,vex::velocityUnits::rpm);
    Rwheel.spin(vex::directionType::fwd,speed*1*direction,vex::velocityUnits::rpm);
}

void upGoL(int speed, int direction){
  LUp.spin(vex::directionType::fwd,speed*1*direction,vex::velocityUnits::rpm);
}

void upGoR(int speed, int direction){
  RUp.spin(vex::directionType::fwd,speed*1*direction,vex::velocityUnits::rpm);
}



void upStop(){
  RUp.stop();
  LUp.stop();
}

void upCoast(){
  RUp.stop(brakeType::coast);
  LUp.stop(brakeType::coast);
}

void intakeMove(int direction, double speed, double degrees){
  Intake.startRotateFor(direction*degrees, rotationUnits::deg, direction*speed, velocityUnits::pct);
  while (Intake.isSpinning()){
        wait(1);
      }
}

void upMove(int direction, double speed, double degrees){
  LUp.startRotateFor(direction*degrees, rotationUnits::deg, direction*speed, velocityUnits::pct);
  RUp.startRotateFor(direction*degrees, rotationUnits::deg, direction*speed, velocityUnits::pct);
  while (LUp.isSpinning()){
        wait(1);
      }
}

void stopEverything(){
  Intake.stop(brakeType::hold);
  RUp.stop(brakeType::hold);
  LUp.stop(brakeType::hold);
  MH.stop(brakeType::hold);
  RB.stop(brakeType::hold);
  RF.stop(brakeType::hold);
  LB.stop(brakeType::hold);
  LF.stop(brakeType::hold);
}



//OTHER SUBSYSTEMS

void intakeSpin(double direction, double speed){
  Intake.spin(vex::directionType::fwd, direction*speed, vex::velocityUnits::rpm);
}

void intakeBrake(){
  Intake.stop(brakeType::hold);
}

void intakeCoast(){
  Intake.stop(brakeType::coast);
}

void intakeStop(){
  Intake.stop();
}




void routine(double speed){
  intakeMove(BACKWARD, speed, 400);
  upMove(BACKWARD, speed, 200);
  intakeMove(FORWARD, speed, 400);
  upMove(FORWARD, speed, 200);
}

















































//UP PID (Correction)     (not correction anymorel just Up)
void up(int direction, float speed){
  //resetUp();
  upGoL(speed, direction);
  upGoR(speed, direction);
  //double difference1 = 0.6*(getLUp() - getRUp());
  //if (getLUp() > getRUp()){
    //upGoL(200*speed - abs(difference1)*speed, direction);
    //upGoR(200*speed, direction);
  //}
  //if (getRUp() > getLUp()){
    //upGoR(200*speed - abs(difference1)*speed, direction);
    //upGoL(200*speed, direction);
  //}
}

/*void upCorrection(){
  //resetUp();
  double difference1 = 0.6*(getLUp() - getRUp());
  while (getLUp() > getRUp()){
    upGoR(5,FORWARD);
    upGoR(5,FORWARD);
  }
  if (getRUp() > getLUp()){
    upGoR(200*speed - abs(difference1)*speed, direction);
    upGoL(200*speed, direction);
  }
}*/

/*void RUpCorrection(){
  upGoR(5,FORWARD);
  upGoL(5,BACKWARD);
}

void LUpCorrection(){
  upGoL(5,FORWARD);
  upGoR(5,BACKWARD);
}*/



/*void TestUp(){
  if ((getUp()) <= -10){
    Brain.Screen.setFillColor(vex::color::red);
  }
  else{
    Brain.Screen.setFillColor(vex::color::blue);
  }
    }


void upp(int direction, float speed){
  resetUp();
  double error = 0 - getUp();
  if ((getUp()) <= 10){
    up(direction, speed);
  }
  else if ((getUp()) > 10){
  }
}

void upAll(int direction, float speed, float degrees){
 while ((abs(getUp()) <= abs(0.25*degrees))){
    upGoL(200, direction);
    upGoR(200, direction);
  }
   while ((abs(getUp()) < abs(0.75*degrees))&&(abs(getUp()) > abs(0.25*degrees))){
    upGoL(200, direction);
    upGoR(200, direction);
  }
   while ((abs(getUp()) <= abs(degrees))&&(abs(getUp()) > abs(0.75*degrees))){
    upGoL(50, direction);
    upGoR(50, direction);
  }
}*/











//UP PID OLD DRIVE POSITIONING
void upGoUp(double degrees, double speed, double wait){
  float deg = abs(degrees);
  float Kp = 0.2;
  float Ki = 0;
  float Kd = 0;
  int error;
  float proportion;
  int iraw;
  float integral;
  int finalerror;
  float derivative;
  const float iactivezone = 43;
  int FinalPower;
  
  int direction;
  if (degrees > 0){
      direction = 1;
  }
  else{
      direction = -1;
  }
  bool TimerBool = true;
  if (wait < .25){
      wait = .25;
  }

  resetUp();
  TimerUp.clear();
  while(TimerUp.time(vex::timeUnits::sec) < wait){
    error = deg - abs((getUp()));
	if ((error < iactivezone) && (error != 0)){
	  iraw = iraw + error;
	}
	else{
	  iraw = 0;
	}
    proportion = Kp * error;
    iraw = iraw + error;
    integral = Ki*iraw;
    derivative = Kd*(error - finalerror);
    finalerror = error;
    if (error == 0){
        derivative = 0;
    }
    FinalPower = (proportion + integral + derivative)*speed*direction; //proportion + integral + derivative
    
    up(direction, FinalPower);
      
      
    if (abs(error) < 200){
      TimerBool = false;
    }
    if (TimerBool){
      TimerUp.clear();
        
    }
  Controller1.Screen.print(error);
  
  }

  LUp.stop(vex::brakeType::brake);
  RUp.stop(vex::brakeType::brake);
  vex::task::sleep(50);
}





void upDriverLoop(){
  //resetUp();

  error = target - getUp();
  double kp = 0.1;
  error = target - getUp();
  double finalPower = kp * error;
  up(FORWARD, finalPower);
  upCoast();
  wait(10);

}

/*void upRoutine(){
  //intakeBrake();
  intakeMove(FORWARD, FAST, 100);
  upMove(BACKWARD, FAST, 200);
  intakeMove(BACKWARD, FAST, 100);
  upMove(FORWARD, FAST, 200);
}*/






























//OLD COMMANDS
void goo(int direction, int speed, float inches, int degrees2, int time){
    
    float degrees = 28.5*inches;
    Lwheel.startRotateFor(direction*degrees, vex::rotationUnits::deg,direction*speed,vex::velocityUnits::rpm);
    Rwheel.startRotateFor(direction*degrees, vex::rotationUnits::deg,direction*speed,vex::velocityUnits::rpm);
    Lwheel2.startRotateFor(direction*degrees, vex::rotationUnits::deg,direction*speed,vex::velocityUnits::rpm);
    Rwheel2.startRotateFor(direction*degrees, vex::rotationUnits::deg,direction*speed,vex::velocityUnits::rpm);
    while (((Lwheel.rotation(vex::rotationUnits::deg)) < abs(degrees2))&&((Lwheel2.rotation(vex::rotationUnits::deg)) < abs(degrees2))&&((Rwheel.rotation(vex::rotationUnits::deg)) < abs(degrees2))&&((Rwheel2.rotation(vex::rotationUnits::deg)) < abs(degrees2))){
    vex::task::sleep(1);
    }
    
    Lwheel.resetRotation();
    Lwheel2.resetRotation();
    Rwheel.resetRotation();
    Rwheel2.resetRotation();
    
    //task::sleep(time);
    //Lwheel.stop();
    //Rwheel.stop();
    //Lwheel2.stop();
    //Rwheel2.stop();
}



void turnOldPID(float direction, float degrees, float speed, float wait){
    
    float deg = abs(degrees*2*3.5);
    float Kp = 0.2;
    float Ki = 0.000005;
    float Kd = 0.84;
    int error;
    float proportion;
    int iraw;
    float integral;
    int finalerror;
    float derivative;
    const float iactivezone = 43;
    int FinalPower;
    bool TimerBool = true;
    if (wait < .25){
        wait = .25;
    }
    Lwheel.resetRotation();
    Rwheel.resetRotation();
    
    TimerDrive.clear(); 
     while(TimerDrive.time(vex::timeUnits::sec) < wait){
        error = deg - (Lwheel.rotation(vex::rotationUnits::deg)*-1*direction + Rwheel.rotation(vex::rotationUnits::deg)*1*direction);
	if ((error < iactivezone) && (error != 0)){
	    iraw = iraw + error;
	}
	else{
	    iraw = 0;
	}
        proportion = Kp * error;
        iraw = iraw + error;
        integral = Ki*iraw;
	    derivative = Kd*(error - finalerror);
    	finalerror = error;
        if (error == 0){
            derivative = 0;
    	}
        FinalPower = (proportion + integral+derivative)*speed; //proportion + integral + derivative
        
        turnbase(FinalPower, direction);
         
        if (abs(error) < 10){
            TimerBool = false;
        }
        if (TimerBool){
            TimerDrive.clear();
            
        } 
    }
    Lwheel.stop(vex::brakeType::brake);
    Rwheel.stop(vex::brakeType::brake);
    Rwheel2.stop(vex::brakeType::brake);
    Lwheel2.stop(vex::brakeType::brake);
    vex::task::sleep(500);
    Lwheel.stop(vex::brakeType::coast);
    Rwheel.stop(vex::brakeType::coast);
    Rwheel2.stop(vex::brakeType::coast);
    Lwheel2.stop(vex::brakeType::coast);
    
    
    
    
    
}


void turnsmall(float direction, float degrees, float speed, float wait){
    float deg = abs(degrees*2*3.5);
    float Kp = 0.2;
    float Ki = 0.000005;
    float Kd = 0.84;
    int error;
    float proportion;
    int iraw;
    float integral;
    int finalerror;
    float derivative;
    const float iactivezone = 43;
    int FinalPower;
    bool TimerBool = true;
    if (wait < .25){
        wait = .25;
    }
    Lwheel.resetRotation();
    Rwheel.resetRotation();
    
    
    Brain.resetTimer(); 
     while(Brain.timer(vex::timeUnits::sec) < wait){
        error = deg - (Lwheel.rotation(vex::rotationUnits::deg)*-1*direction + Rwheel.rotation(vex::rotationUnits::deg)*1*direction);
	if ((error < iactivezone) && (error != 0)){
	    iraw = iraw + error;
	}
	else{
	    iraw = 0;
	}
        proportion = Kp * error;
        iraw = iraw + error;
        integral = Ki*iraw;
	    derivative = Kd*(error - finalerror);
    	finalerror = error;
        if (error == 0){
            derivative = 0;
    	}
        FinalPower = (proportion + integral+derivative)*speed; //proportion + integral + derivative
        
        turnbase(FinalPower, direction);
         
         
        if (abs(error) < 10){
            TimerBool = false;
        }
        if (TimerBool){
            Brain.resetTimer();
            
        } 
    }
    Lwheel.stop(vex::brakeType::brake);
    Rwheel.stop(vex::brakeType::brake);
    Rwheel2.stop(vex::brakeType::brake);
    Lwheel2.stop(vex::brakeType::brake);
    vex::task::sleep(500);
    Lwheel.stop(vex::brakeType::coast);
    Rwheel.stop(vex::brakeType::coast);
    Rwheel2.stop(vex::brakeType::coast);
    Lwheel2.stop(vex::brakeType::coast);
    
    
}
void goOldPID (float inch, float speed, float wait){
    float deg = abs(inch*57);
    float Kp = 0.2;
    float Ki = 0.000005;
    float Kd = 0.84;
    int error;
    float proportion;
    int iraw;
    float integral;
    int finalerror;
    float derivative;
    const float iactivezone = 43;
    int FinalPower;
    
   int direction;
   if (deg > 0){
       direction = 1;
   }
    else{
        direction = -1;
    }
    bool TimerBool = true;
    if (wait < .25){
        wait = .25;
    }
    Lwheel.resetRotation();
    Rwheel.resetRotation();
    
    
    TimerDrive.clear(); 
     while(TimerDrive.time(vex::timeUnits::sec) < wait){
        error = deg - abs((Lwheel.rotation(vex::rotationUnits::deg) + Rwheel.rotation(vex::rotationUnits::deg)));
	if ((error < iactivezone) && (error != 0)){
	    iraw = iraw + error;
	}
	else{
	    iraw = 0;
	}
        proportion = Kp * error;
        iraw = iraw + error;
        integral = Ki*iraw;
        derivative = Kd*(error - finalerror);
        finalerror = error;
        if (error == 0){
            derivative = 0;
    	  }
        FinalPower = (proportion + integral + derivative)*speed*direction; //proportion + integral + derivative
        
        movebase(FinalPower);
         
         
        if (abs(error) < 40){
            TimerBool = false;
        }
        if (TimerBool){
            TimerDrive.clear();
            
        } 
    }
    Lwheel.stop(vex::brakeType::brake);
    Rwheel.stop(vex::brakeType::brake);
    Rwheel2.stop(vex::brakeType::brake);
    Lwheel2.stop(vex::brakeType::brake);
    vex::task::sleep(50);
    Lwheel.stop(vex::brakeType::coast);
    Rwheel.stop(vex::brakeType::coast);
    Rwheel2.stop(vex::brakeType::coast);
    Lwheel2.stop(vex::brakeType::coast);
} 






























































//AUTO INIT COMMANDS

//this will be the input for color argument within runAuto function (this is probably a lie)
void autoColorSelect(){
  //int autoCol = 0;
    //if (Brain.Screen.pressing()){
        /*if (autoCol == 0){
          wait(200);
          autoCol = 1;
          Brain.Screen.drawRectangle(15, 15, 50, 50, blue);
        }
        else if (autoCol == 1){
          wait(200);
          Brain.Screen.drawRectangle(15, 15, 50, 50, red);
          autoCol = 0;
        }*/
        
      //}
  //return autoCol;
}

//this will be the input for number argument within runAuto function (this is also probably not true)
void autoPositionSelect(){
  //double autoNum = 0;
  //return autoNum;

}

//Stack Auto Function

int autoColorReturn(){
  return autoCol;
}

int autoPositionReturn(){
  return autoPos;
}


//auto selection
void runAuto(int autoColor, int autoNumber, bool running){

  if (running){
  //red
    if (autoColor == 0){
      if (autoNumber == 1){
        stopEverything();
        goOldPID(360, 200, 0);
        turnOldPID(RIGHT, 90, 200, 0);
      }
      if (autoNumber == 2){

      }
      if (autoNumber == 3){

      }
      if (autoNumber == 4){

      }
    }

    //blue
    if (autoColor == 1){
      if (autoNumber == 1){
        goOldPID(360, 200, 0);
        turnOldPID(LEFT, 90, 200, 0);
      }
      if (autoNumber == 2){

      }
      if (autoNumber == 3){

      }
      if (autoNumber == 4){

      }
    }
  }

  //not running (just deploy)
  else{
    upGoUp(300, 1.5, 0);
    autoRunning = false;
  }
}



