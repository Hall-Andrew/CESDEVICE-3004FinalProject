#include "countdownclock.h"

CountDownClock::CountDownClock(int number)
{
    minutes = number;
    sDigitOne = 0;
    sDigitTwo = 0;
    finished = false;
}

void CountDownClock::setMinutes(int newTimerLength)
{
    minutes = newTimerLength;
    finished = false;
}
void CountDownClock::setSeconds(int seconds)
{
    sDigitTwo = seconds % 10;
    sDigitOne = seconds/10 - sDigitTwo/10;
}

void CountDownClock::countdown(){
    if(sDigitTwo != 0 ){
        sDigitTwo-=1;
    }else{
        if(sDigitOne!=0){
            sDigitOne-=1;
            sDigitTwo=9;
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
//    if(minutes==0 && sDigitOne==0 && sDigitTwo ==0 ){
//        finished=true;
//    }
//    return finished;

    // This just seems more clean to me - Aaron
    return minutes == 0 && sDigitOne == 0 && sDigitTwo == 0;
}
