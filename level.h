#ifndef LEVEL_H
#define LEVEL_H
#include <iostream>
using namespace std;

class Level
{
 private:
  int level;
  float gravity;
 public:
	Level()
	{
		level = 1;
	}
  int getLevel() const { return level; };
  void setLevel(int l) { level = l; };
  void addLevel() { level ++; };
};

#endif