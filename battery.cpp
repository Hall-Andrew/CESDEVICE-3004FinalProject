#include "battery.h"
#include <string.h>

Battery::Battery()
{
    power=100;
<<<<<<< HEAD
    drain=10;
    /*sets up the default battery, Life being 100 and Speed being .5,
    These are just arbitray number which are subject to change. Point being:
    power represents the batteries charge and, while the battery is on, it will be
    decreasing
    */
=======
    baseDrainAmount=1;
    drainModifier=0.10;
    timer = new QTimer(this);
    timer->setInterval(2500);
    connect(timer, &QTimer::timeout, this, &Battery::drain);
>>>>>>> 184913dcbcb00f3b63efe277822daf1d6f7d26dc
}
Battery::~Battery(){

}

<<<<<<< HEAD
void Battery::decay()
{
    power-=drain;
    if (power<=0)
    {
        charged=false;
    }
}

/* Basic decay function. Missing a lot of what we need (being able to run in
the background primarily) but a good starting point. There's two versions
of this function, the second takes in a modifier which is needed for when
the machine is running.
*/
void Battery::decay(int mod)
{

  power-=drain+(drain*mod);
  if (power<=0)
  {
      charged=false;
  }
}
bool Battery::IsCharge(){return charged;}
//Basic Funct to reset the battery.

float Battery::getBatteryLevel() { return power; }
void Battery::setBatteryLevel(float newPowerLevel) { power = newPowerLevel; }
=======
void Battery::charge(){
    power = 100;
}

void Battery::startBatteryDrain(){
    timer->start();
}

void Battery::stopBatteryDrain(){
    timer->stop();
}

void Battery::setDrainMultiplier(double multi){
    drainModifier=multi;
}

void Battery::drain(){
    power=power-(baseDrainAmount*drainModifier);
    emit updateBatteryBar((int)power);
    cout.precision(2);
    cout<<fixed<<power<<endl;
}

double Battery::getBatteryPercentage(){
    return power;
}
>>>>>>> 184913dcbcb00f3b63efe277822daf1d6f7d26dc
