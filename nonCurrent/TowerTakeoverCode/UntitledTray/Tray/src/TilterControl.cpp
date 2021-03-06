#include "vex.h"
using namespace vex;

int tilterControls(){
  double traySpeed = 1; //standard tilt speed
  double traySpeed2 = 1; //tilt speed for arm control
  double trayToggleSpeed = 1; //toggle slow speed
  int trayToggle = 0; //toggle slow variable
  bool controllerRumble = false;
  while (1){
    if (getController(BTNRIGHT)){ //toggle slow speed button
      while (getController(BTNRIGHT)){
        wait(1, msec);
      }
      if (trayToggle == 0){
        trayToggleSpeed = 0.4;
        trayToggle = 1;
        controllerRumble = true;
      }
      else if (trayToggle == 1){
        trayToggleSpeed = 1;
        trayToggle = 0;
        controllerRumble = false;
      }
    }
    if (getController(BTNLEFT)){ //reset button
      while (getController(BTNLEFT)){
        wait(1, msec);
      }
      Tilter.resetRotation();
    }
    if (controllerRumble){
      Controller.rumble(".");
    }
    if (getTrayLimit()){ //reset switch
      Tilter.resetRotation();
    }
    if (Tilter.rotation(rotationUnits::deg) >= 400){ //trayP
      double error = 850 - Tilter.rotation(rotationUnits::deg);
      traySpeed = 0.0012*error;
    }
    else{
      traySpeed = 1; //tray speed is 1 unless it is past 400 degreese
    }
    if ((Tilter.rotation(rotationUnits::deg) >= 150)){ //tray only tilts with arms until 150 degrees
      traySpeed2 = 0;
    }
    else{
      traySpeed2 = 1;
    }
    if (getController(BTNB)){ //tilt
      tray(TILT, 100*traySpeed*trayToggleSpeed);
    }
    else if (getController(BTNY)){ //untilt
      tray(UNTILT, 100*trayToggleSpeed);
    }
    else if (getController(BTNL1)){ //tilt with arms
      tray(TILT, 40*traySpeed2);
    }
    else if (getController(BTNL2)){ //untilt with arms
      tray(UNTILT, 70);
    }
    else{
      trayBrake();
    }
  }
  wait(10, msec);
  return 0;
}