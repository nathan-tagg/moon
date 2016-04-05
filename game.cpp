/*************************************************************
 * File: game.cpp
 * Author: Br. Burton
 *
 * Description: Contains the implementations of the
 *  method bodies for the game class.
 *
 * Please DO NOT share this code with other students from
 *  other sections or other semesters. They may not receive
 *  the same code that you are receiving.
 *************************************************************/

#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock


#ifdef __APPLE__
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32


#include "game.h"
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "ground.h"
#include "lander.h"
#include "velocity.h"

/******************************************
 * GAME :: JUST LANDED
 * Did we land successfully?
 ******************************************/
bool Game :: justLanded() const
{
   bool landed = false;
   
   Point platformCenter = ground.getPlatformPosition();
   int width = ground.getPlatformWidth();

   float xDiff = lander.getPoint().getX() - platformCenter.getX();
   float yDiff = lander.getPoint().getY() - platformCenter.getY();

   float margin = width / 2.0;
   
   if (fabs(xDiff) < margin)
   {
      // between edges
      
      if (yDiff < 4 && yDiff >= 0)
      {
         // right above it
         
         if (fabs(lander.getVelocity().getDx()) < 3 && fabs(lander.getVelocity().getDy()) < 3)
         {
	   // we're there!
            landed = true;
         }
      }
   }
   
   return landed;
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   if (lander.isAlive() && !lander.isLanded())
   {
      // advance the lander
      lander.advance();
   
      // check for crash
      if (!ground.isAboveGround(lander.getPoint()))
      {
         lander.setAlive(false);
      }
   
      // check for just landed
      if (justLanded())
      {
         lander.setLanded(true);
      }
   }
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
   if (lander.isAlive() && !lander.isLanded())
   {
   
      if (ui.isDown() && lander.canThrust())
      {
         lander.applyThrustBottom();
      }
      
      if (ui.isLeft() && lander.canThrust())
      {
         lander.applyThrustLeft();
      }
      
      if (ui.isRight() && lander.canThrust())
      {
         lander.applyThrustRight();
      }
   }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
   lander.draw();

   Point text;
   text.setX(-60);
   text.setY(75);
   Point start(190, 190);
   Point zero(0, 0);
   Velocity vel;

   if (lander.isLanded())
   {
      drawText(text, "You have successfully landed! ( Space bar )");
   }
   
   if (!lander.isAlive())
   {
      drawText(text, "You have crashed! ( Space bar )");
      glColor3f(1.5, 0.0, 0.8);
      drawToughBird(lander.getPoint(), 30, 0);
      glColor3f(1.0, 1.0, 1.0);
      glEnd();
   }
   
   if (lander.canThrust())
   {
      drawLanderFlames(lander.getPoint(), ui.isDown(), ui.isLeft(), ui.isRight());
   }

   if (ui.isSpace() &&lander.isLanded())
   {
      lander.setAlive(true);
      lander.setLanded(false);
      lander.setFuel(500);
      lander.setPoint(start);
      lander.setVelocity(vel);
      level.addLevel();
      ground.generateGround();
   }

   if (ui.isSpace() && !lander.isAlive())
   {
      lander.setAlive(true);
      lander.setLanded(false);
      lander.setFuel(500);
      lander.setPoint(start);
      lander.setVelocity(vel);
      level.setLevel(1);
      ground.generateGround();
   }
   
   if (ui.isSpace() && level.getLevel() > 14)
   {
      lander.setAlive(true);
      lander.setLanded(false);
      lander.setFuel(500);
      lander.setPoint(start);
      lander.setVelocity(vel);
      level.setLevel(1);
      ground.generateGround();
   }

   Point end(-50, -100);
   Point fuelLocation;
   fuelLocation.setX(topLeft.getX() + 5);
   fuelLocation.setY(topLeft.getY() - 5);
   Point levelLocation;
   levelLocation.setX(-35);
   levelLocation.setY(150);
   
   if (lander.getFuel() > 0)
     drawNumber(fuelLocation, lander.getFuel());
   else
     drawNumber(fuelLocation, 0);
   // draw ground
   if (level.getLevel() == 1)
   {
      drawText(levelLocation, "Level 1: Moon");
      ground.drawMoon();
      lander.applyGravity(0.1);
   }
   else if (level.getLevel() == 2)
   {
      drawText(levelLocation, "Level 2: Pluto");
      ground.drawPluto();
      lander.applyGravity(0.12);
   }
   else if(level.getLevel() == 3)
   {
      drawText(levelLocation, "Level 3: Mercury");
      ground.drawMercury();
      lander.applyGravity(.14);
   }
   else if(level.getLevel() == 4)
   {
      drawText(levelLocation, "Level 4: Mars");
      ground.drawMars();
      lander.applyGravity(.16);
   }
   else if(level.getLevel() == 5)
   {
      drawText(levelLocation, "Level 5: Venus");
      ground.drawVenus();
      lander.applyGravity(.18);
   }
      else if(level.getLevel() == 6)
   {
      drawText(levelLocation, "Level 6: Uranus");
      ground.drawUranus();
      lander.applyGravity(.20);
   }
   else if(level.getLevel() == 7)
   {
      drawText(levelLocation, "Level 7: Earth (Everest)");
      ground.drawEverest();
      lander.applyGravity(.21);
   }
   else if(level.getLevel() == 8)
   {
      drawText(levelLocation, "Level 8: Neptune");
      ground.drawNeptune();
      lander.applyGravity(.22);
   }
   else if(level.getLevel() == 9)
   {
      drawText(levelLocation, "Level 9: Saturn");
      ground.drawSaturn();
      lander.applyGravity(.23);
   }
   else if(level.getLevel() == 10)
   {
      drawText(levelLocation, "Level 10: Jupter");
      ground.drawJupiter();
      lander.applyGravity(.24);
   }
   else if(level.getLevel() == 11)
   {
      drawText(levelLocation, "Level 11: Heleos");
      ground.drawSun();
      lander.applyGravity(.25);
   }
   else if(level.getLevel() == 12)
   {
      drawText(levelLocation, "Level 12: r136a1");
      ground.drawR136a1();
      lander.applyGravity(.26);
   }
   else if(level.getLevel() == 13)
   {
      drawText(levelLocation, "Level 13: Black Hole");
      ground.drawHole();
      lander.applyGravity(.27);
   }
   else
   {
      drawText(levelLocation, "Outer Darkness");
      drawText(end, "You win. Go tell someone");
      lander.applyGravity(0);
      lander.setPoint(zero);
   }
}

