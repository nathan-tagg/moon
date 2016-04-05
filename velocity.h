#ifndef VELOCITY_H
#define VELOCITY_H

#include <iostream>
using namespace std;

class Velocity
{
 private:
 	float Dx;
	float Dy;
 public:
 	Velocity()
 	{
 		Dx = -.5;
 	}
 	float getDx() const { return Dx; };
 	float getDy() const { return Dy; };
 	void setDx(float D) { Dx += D; };
 	void setDy(float D) { Dy += D; };
};

#endif
