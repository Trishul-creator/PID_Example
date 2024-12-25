#include "PIDFunctions.h"

void drive(PIDController& pid, int distance, vex::directionType direction) {
  pid.setDesiredValue(distance);

  while (!pid.atTarget()) {
    int leftMotorPosition = LeftDriveSmart.position(degrees) * 200 * M_PI / 360;
    int rightMotorPosition = RightDriveSmart.position(degrees) * 200 * M_PI / 360;
    int averagePosition = (leftMotorPosition + rightMotorPosition) / 2;

    int motorPower = pid.calculate(averagePosition);

    

    LeftDriveSmart.spin(direction, motorPower, percent);
    RightDriveSmart.spin(direction, motorPower, percent);
    wait(20, msec);
  }
  Drivetrain.stop();
}

void turn(PIDController& pid, int angle, vex::turnType rightOrLeft) {
  pid.setTurnDesiredValue(angle);

  while (!pid.atTurnTarget()) {
    int currentAngle = BrainInertial.rotation();
    int turnPower = pid.calculateTurn(currentAngle);

    if(rightOrLeft == right) {
      LeftDriveSmart.spin(forward, turnPower, percent);
      RightDriveSmart.spin(reverse, turnPower, percent);
    } else if(rightOrLeft == left){
      LeftDriveSmart.spin(reverse, turnPower, percent);
      RightDriveSmart.spin(forward, turnPower, percent);
    } else {
      Brain.Screen.print("Invalid turn type");
    }
    wait(20, msec);
  }
  Drivetrain.stop();
}