#ifndef BATTERY_H
#define BATTERY_H
#include<QString>
class Battery
{
public:
    Battery();
   ~Battery();
   void decay(); //default decay method
   void decay(int mod);//call for when machine is running
   bool IsCharge();

   float getBatteryLevel();
   void setBatteryLevel(float newBatteryLevel);

private:
    float power;
    float drain; //how fast battery life decays
    float* decay_mod;
    //the modifier to how the battery drains. I figured it would be better as a pointer but idk.
    bool charged;
};

#endif // BATTERY_H
