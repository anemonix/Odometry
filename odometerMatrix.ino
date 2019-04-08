#include <BasicLinearAlgebra.h>

/*
 * Haven't printed our chasis yet so setting these values as define for later
 * Values are in cm
 */
#define widthOfRobot 10
#define radiusOfWheel 2
#define turnRatio 75
#define IRL 11
#define IRR 12

/*
 * Setting up some formulas for variables that will be updated throughout
 * These were covered in class
 */
float L = widthOfRobot/2;
float centralAngle = 90/turnRatio;
float arcLength = radiusOfWheel * deg2rad(centralAngle);
float deltaZ = arcLength/widthOfRobot;

//Taken from our FK homework and in class
Matrix<4,4> transformationMatrix = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1}; 
Matrix<4,4> leftRotateMatrix = {cos(-deltaZ),-sin(-deltaZ),0,0, sin(-deltaZ),cos(-deltaZ),0,L, 0,0,1,0, 0,0,0,1};
Matrix<4,4> rightRotateMatrix = {cos(deltaZ),-sin(deltaZ),0,0, sin(deltaZ),cos(deltaZ),0,L, 0,0,1,0, 0,0,0,1};
Matrix<4,4> leftDistanceMatrix = {1,0,0,0, 0,1,0,widthOfRobot, 0,0,1,0, 0,0,0,1};
Matrix<4,4> rightDistanceMatrix = {1,0,0,0, 0,1,0,-widthOfRobot, 0,0,1,0, 0,0,0,1};

Matrix<4,4> rightTransformMatrix = rightRotateMatrix * rightDistanceMatrix;
Matrix<4,4> leftTransformMatrix = leftRotateMatrix * leftDistanceMatrix;


/*
 * Updating our transformation matrix by multiplying it with our
 * left transform matrix accordingly to get our new location values
 * As pointed out in our previous homework assignment - (0,3) contains
 * our x value and (1,3) contains our y value, theta can be found by taking
 * arcos(0,0)
 */
void leftWheelInterrupt()
{ 
  transformationMatrix = transformationMatrix * leftTransformMatrix;
}

/*
 * Updating our transformation matrix by multiplying it with our
 * right transform matrix accordingly to get our new location values
 */
void rightWheelInterrupt()
{ 
  transformationMatrix = transformationMatrix * rightTransformMatrix;
}

/*
 * Setting up our arduino to be able to read inputs from our IR sensors
 * and detect when our IR values change so that it can go into our interrupt functions
 */
void setup()
{
  Serial.begin(9600);
  pinMode(IRL, INPUT_PULLUP);
  pinMode(IRR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRL), leftWheelInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(IRR), rightWheelInterrupt, CHANGE);
}
