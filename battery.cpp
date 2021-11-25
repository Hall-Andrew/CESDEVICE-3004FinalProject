#include "battery.h"
#include <string.h>

Battery::Battery()
{
    power=50;
    baseDrainAmount=1;
    drainModifier=0.10;
    powerWarning=false;
    twoPercentWarning=false;
    timer = new QTimer(this);
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, this, &Battery::drain);
    turnOffCount=0;
}
Battery::~Battery(){

}

void Battery::charge(){
    power = 100;
    powerWarning=false;
    twoPercentWarning=false;
    turnOffCount=0;
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
    if(power>2){
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
//        cout<<power<<endl;
        if(power <6 && power > 4 && !powerWarning){
            powerWarning=true;
            cout<<"5% warning"<<endl;
            warning = "Warning, battery is at 5%, please charge the device!";
            emit batteryMessage(warning);
        }else{
            if(power<3 && !twoPercentWarning){
                cout<<"2% shutdown warning!"<<endl;
                twoPercentWarning = true;
                warning = "Warning, battery is at 2%, the device will shut off shortly if it is not charged!";
                emit batteryMessage(warning);
            }
        }
    }
    if(twoPercentWarning){
        turnOffCount+=1;
        if(turnOffCount>3){
            emit shutDown();
        }
    }
    emit updateBatteryBar((int)power);
    //cout.precision(2);
    //cout<<fixed<<power<<endl;
}

double Battery::getBatteryPercentage(){
    return power;
}
