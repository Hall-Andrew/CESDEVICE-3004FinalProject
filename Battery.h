#ifndef BATTERY_H
#define BATTERY_H
#include<QString>
class Battery
{
public:
    Battery();
   ~Battery();
   Qstring Decay(); //default decay method
   Qstring Decay(int mod);//call for when machine is running
   void charge();
private:
    float life;
    float SpeedOfDeath; //how fast battery life decays
    float* decay_mod;
    //the modifier to how the battery decays. I figured it would be better as a pointer but idk.
    bool charged;
};

#endif // BATTERY_H
