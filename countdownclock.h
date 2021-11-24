#ifndef COUNTDOWNCLOCK_H
#define COUNTDOWNCLOCK_H
#include <QString>

class CountDownClock
{
    public:
        CountDownClock(int number);
        void countdown();
        void setMinutes(int newTimerLength);
        void setSeconds(int seconds);
        QString getDisplayNumbers();
        bool isTimerFinished();

    private:
        int minutes;
        int sDigitOne;
        int sDigitTwo;
        bool finished;

};

#endif // COUNTDOWNCLOCK_H
