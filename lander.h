#ifndef LANDER_H
#define LANDER_H

#include <iomanip>
#include "velocity.h"
#include "uiDraw.h"
#include "point.h"
#include <iostream>
using namespace std;

class Lander
{
 private:
  int fuel;
  bool alive;
  bool landed;
  Point point;
  Velocity velocity;
 public:
  
  /***********************************************
  * Constructors.
  ***********************************************/
  Lander()
    {
      alive = true;
      landed = false;
      point.setX(190);
      point.setY(190);
      drawLander(point);
    }
  Lander(float X, float Y)
    {
      alive = true;
      landed = false;
      point.setX(X);
      point.setY(Y);
      drawLander(point);
    }

  /***********************************************
  * Getters / setters.
  ***********************************************/  
  void setFuel(int set) { fuel = set; };
  void setAlive(bool set) { alive = set; };
  void setLanded(bool set) { landed = set; };
  void setPoint(Point p) { point = p; };
  void setVelocity(Velocity v) { velocity = v; };
  int getFuel() const { return fuel; };
  Point getPoint() const { return point; };
  Velocity getVelocity() const { return velocity; };
  
  /***********************************************
  * Apply meathods: These meathods call the mutators for the velocity variable. 
  ***********************************************/
  void applyThrustBottom() { velocity.setDy(.3); fuel -= 3; };
  void applyThrustLeft() { velocity.setDx(.1); fuel -= 1; };
  void applyThrustRight() { velocity.setDx(-.1); fuel -= 1; };
  void applyGravity(float gravity) { velocity.setDy(-gravity); };
  
  /**********************************************
  * Boolean meathods: These meathods determine if the lander has landed, has fuel, or has crashed.
  **********************************************/
  bool canThrust() { return (fuel > 0); };
  bool isAlive() const { return alive; };
  bool isLanded() const { return landed; };
  
  /*********************************************
  * Draw: This meathod will draw the lander in the environment.
  *********************************************/
  void draw() { drawLander(point); };

  /********************************************
  * Advance: This meathod will add the velocity to the point each frame.
  * It will wrap the position of the lander around the screen as well.
  ********************************************/
  void advance() 
  { 
    point.addX(velocity.getDx()); 
    point.addY(velocity.getDy());
    if (point.getX() > 195 || point.getX() < -195)
      point.setX(-(point.getX()));
    drawLander(point);
  };
};

#endif
