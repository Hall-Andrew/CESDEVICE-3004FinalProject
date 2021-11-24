#include "countdownclock.h"

CountDownClock::CountDownClock(int number)
{
    minutes = number;
    sDigitOne=0;
    sDigitTwo;
    finished=false;
}

void CountDownClock::setTimerNumber(int newTimerLength){
    minutes = newTimerLength-1;
    finished=false;
}

void CountDownClock::countdown(){
    if(sDigitTwo != 0 ){
        sDigitTwo-=1;
    }else{
        if(sDigitOne!=0){
            sDigitOne-=1;
        }else{
            minutes-=1;
            sDigitOne=5;
            sDigitTwo=9;
        }
    }
}

QString CountDownClock::getDisplayNumbers(){
    return QString::number(minutes)+":"+QString::number(sDigitOne)+QString::number(sDigitTwo);
}

bool CountDownClock::isTimerFinished(){
    if(minutes==0 && sDigitOne==0 && sDigitTwo ==0 ){
        finished=true;
    }
    return finished;
}
