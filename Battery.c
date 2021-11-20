#include "Battery.h"

Battery::Battery()
{
    life=100;
    SpeedOfDeath=0.5;
    /*sets up the default battery, Life being 100 and Speed being .5,
    These are just arbitray number which are subject to change. Point being:
    life represents the battery life and, while the battery is on, it will be
    decreasing
    */
}

Battery::~Battery()
{
  delete decay_mod;
}
Qstring Battery::decay()
{
  while (life<0)
  {
    life-=SpeedOfDeath;
  }
  charged=false;
  return "Your battery is out of life ";
}
/* Basic decay function. Missing a lot of what we need (being able to run in
the backgourn primarily) but a good starting point. There's two versions
of this function, the second takes in a modifier which is needed for when
the machine is running.

*/
Qstring Battery::decay(int mod)
{
  while (life<0)
  {
    life-=(SpeedOfDeath+(SpeedOfDeath*mod));
  }
  charged=false;
  return "Your battery is out of life ";
}
void Battery::charge(){life=100; charged=true;}
//Basic Funct to reset the battery.