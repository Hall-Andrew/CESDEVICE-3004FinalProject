#include "battery.h"
#include <string.h>

Battery::Battery()
{
    power=100;
    baseDrainAmount=1;
    drainModifier=0.10;
    timer = new QTimer(this);
    timer->setInterval(2500);
    connect(timer, &QTimer::timeout, this, &Battery::drain);
}
Battery::~Battery(){

}

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
    if((power-(baseDrainAmount*drainModifier))>0){
        power=power-(baseDrainAmount*drainModifier);
    }else{
        power = 0;
    }
    emit updateBatteryBar((int)power);
    cout.precision(2);
    cout<<fixed<<power<<endl;
}

double Battery::getBatteryPercentage(){
    return power;
}
