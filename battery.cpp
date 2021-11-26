#include "battery.h"
#include <string.h>

Battery::Battery()
{
    power=3;
    baseDrainAmount=1;
    drainModifier=0.10;
    powerWarning=false;
    twoPercentWarning=false;
    timer = new QTimer(this);
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, this, &Battery::drain);
}
Battery::~Battery(){

}

void Battery::charge(){
    power = 100;
    powerWarning=false;
    twoPercentWarning=false;
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

bool Battery::hasPower(){
    if(power>2.5){
        return true;
    }else{
        return false;
    }
}

void Battery::drain(){
    QString warning;
    power=power-(baseDrainAmount*drainModifier);
    if(power<0){
        power=0;
    }else{
        if(power <6 && power > 4 && !powerWarning){
            powerWarning=true;
            warning = "Warning, battery is at 5%, please charge the device!";
            emit batteryMessage(warning);
        }else{
            if(power<3 && !twoPercentWarning){
                twoPercentWarning = true;
                warning = "Warning, battery is at 2%, the device will shut off shortly if it is not charged!";
                emit batteryMessage(warning);
            }
        }
    }
    if(twoPercentWarning){
        if(power<2.5){
            emit shutDown();
        }
    }
    emit updateBatteryBar((int)power);
}

double Battery::getBatteryPercentage(){
    return power;
}
