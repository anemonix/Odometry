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
float anglePerTickX = L * sin(deltaZ);
float anglePerTickY = L * (1 - cos(deltaZ));

//Initial location and z theta
float x = 0;
float y = 0;
float z = 0;

//Change in location and z theta
float deltaX = 0;
float deltaY = 0;
float deltaZ = arcLength/widthOfRobot;

/*
 * When left wheel interrupt is activated, we decrease our change in y since
 * that is what we defined. Notice that x is still increasing, and will always be forward
 * since we're never moving backward at any point.
 */
void leftWheelInterrupt()
{ 
  //Calculating our new deltas
  deltaX = ((anglePerTickX * cos(deltaZ)) + (anglePerTickY * sin(deltaZ)));
  deltaY = ((anglePerTickX * sin(deltaZ)) + (anglePerTickY * cos(deltaZ)));

  //Updating our position and theta
  x += deltaX;
  y -= deltaY;
  z += deltaZ;

  //Printing out our new position and theta
  Serial.print("Our new x location is: ");
  Serial.println(x);
  Serial.print("Our new y location is: ");
  Serial.println(y);
  Serial.print("Our new theta is: ");
  Serial.println(z);
}

/*
 * When right wheel interrupt is activated, we will get the change in x and y values
 * and add it to our previous/original x and y value to get our new position
 */
void rightWheelInterrupt()
{ 
  //Calculating our new deltas
  deltaX = ((anglePerTickX * cos(deltaZ)) + (anglePerTickY * sin(deltaZ)));
  deltaY = ((anglePerTickX * sin(deltaZ)) + (anglePerTickY * cos(deltaZ)));

  //Updating our position and theta
  x += deltaX;
  y += deltaY;
  z -= deltaZ;

  //Printing out our new position and theta
  Serial.print("Our new x location is: ");
  Serial.println(x);
  Serial.print("Our new y location is: ");
  Serial.println(y);
  Serial.print("Our new theta is: ");
  Serial.println(z);
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
