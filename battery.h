#ifndef BATTERY_H
#define BATTERY_H
#include<QString>
class Battery
{
public:
    Battery();
   ~Battery();
   QString decay(); //default decay method
   QString decay(int mod);//call for when machine is running
   void charge();
private:
    float power;
    float drain; //how fast battery life decays
    float* decay_mod;
    //the modifier to how the battery drains. I figured it would be better as a pointer but idk.
    bool charged;
};

#endif // BATTERY_H
