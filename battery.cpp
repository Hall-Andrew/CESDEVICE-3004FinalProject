#include "battery.h"
#include <string.h>

Battery::Battery()
{
    power=100;
    baseDrainAmount=1;
    drainModifier=0.001;
    powerWarning=false;
    twoPercentWarning=false;
    realisticPowerDraw=true;
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &Battery::drain);
}
Battery::~Battery(){

}

void Battery::charge(){
    power = 100;
    powerWarning=false;
    twoPercentWarning=false;
    emit updateBatteryBar((int)power);
}

void Battery::startBatteryDrain(){
    timer->start();
}

void Battery::stopBatteryDrain(){
    timer->stop();
}

void Battery::setDrainMultiplier(double multi){
    if(realisticPowerDraw){
        if(multi!=0){
            drainModifier=(multi/2)/10000;
        }else{
            drainModifier=0.001;
        }
    }else{
        if(multi!=0){
            drainModifier=(multi)/400;
        }else{
            drainModifier=0.01;
        }
    }
}

void Battery::setBaseDrainValue(double newBaseDrain){
    baseDrainAmount = newBaseDrain;
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
    cout<<"drain rate:"<<baseDrainAmount*drainModifier<<endl;
    power-=(baseDrainAmount*drainModifier);
    cout<<power<<endl;
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

void Battery::toggleRealism(){
    if(realisticPowerDraw){
        realisticPowerDraw=false;
        drainModifier=0.1;
    }else{
        realisticPowerDraw=true;
        drainModifier=0.001;
    }
}

void Battery::resetPowerDraw(){
    if(realisticPowerDraw){
        drainModifier=0.001;
    }else{
        drainModifier=0.1;
    }
}

void Battery::calcDrainSkipped(int seconds){
    cout<<baseDrainAmount*drainModifier<<endl;
    power-=baseDrainAmount*drainModifier*seconds;
    if(power<=0){
        QString warning = "Warning, battery is at 2%, the device will shut off shortly if it is not charged!";
        emit batteryMessage(warning);
        emit shutDown();
    }
}
