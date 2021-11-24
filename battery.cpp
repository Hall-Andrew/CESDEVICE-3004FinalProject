#include "battery.h"
#include <string.h>

Battery::Battery()
{
    power=49;
    baseDrainAmount=1;
    drainModifier=0.10;
    powerWarning=false;
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
    power=power-(baseDrainAmount*drainModifier);
    if(power<0){
        power=0;
    }else{
//        cout<<power<<endl;
        if(power <6 && power > 4 && !powerWarning){
            powerWarning=true;
            cout<<"5% warning"<<endl;
        }
        {
            if(power<3){
                cout<<"2% shutdown warning!"<<endl;
                emit shutDown();
            }
        }
    }

    emit updateBatteryBar((int)power);
    //cout.precision(2);
    //cout<<fixed<<power<<endl;
}

double Battery::getBatteryPercentage(){
    return power;
}
