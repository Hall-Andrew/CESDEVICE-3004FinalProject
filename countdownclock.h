#ifndef COUNTDOWNCLOCK_H
#define COUNTDOWNCLOCK_H
#include <QString>
/*
 * Countdown clock: represents the timer for sessions in the Device. The timer will count down from the time allocated and, when it reaches zero, end the session.
 *
 * Variables:
 *      int minutes: holds the minutes for the clock.
 *      int sDigitOne: To display a clock counting down with second values, the seconds must also held in values. sDigitOne and sDigitTwo contain two values which represents
 *      the numbers of seconds left in the minute.
 *      int sDigitTwo:see sDigitOne
 *      bool finished: boolean which tracks if the timer runs out of time.
 *
 * Functions
 *      countdown: counts down the time by conditionals. if sDigitTwo is equal to zero, the sDigitOne is subtracted by 1. When sDigitOne is equal to zero, minutes is subtracted by 1
 *                  and sDigitOne and sDigitTwo are set to represent 59 seconds (sOne=5,sTwo=9)
 *      setMinutes: sets the miuntes variable
 *      setSeconds: sets the seconds variables
 *      getDisplayNumbers: retuns what is being displatyed on the device
 *      isTimerfinished: sees if the timer is at 0::00.
 * */
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
