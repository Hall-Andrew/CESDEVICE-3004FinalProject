#ifndef COUNTDOWNCLOCK_H
#define COUNTDOWNCLOCK_H
#include <QString>
/* Class:
 * CountDownClock: This Class is used to represent the timer for therapy sessions in the Device.
 *                 The timer will count down from the time allocated in the constructor and properly represent minutes and seconds
 *
 * Variables:
 *      int minutes: stores the minutes for the clock.
 *      int sDigitOne: To display a clock counting down with second values, the seconds must also held in values. sDigitOne and sDigitTwo contain two values which represents.
 *      the numbers of seconds left in the minute. sDigitOne represents the tens column for seconds.
 *      int sDigitTwo: represents the ones column for seconds.
 *      bool finished: boolean which tracks if the timer has runs out of time.
 *
 * Functions:
 *      CountDownClock(int): This is a constructor for the class, it takes the time in minutes you would like to count down from.
 *      countdown: This is also a void function, when this is called it counts down the time showing minutes and seconds.
 *                 This works off a few conditionals which properly simulates counting down minutes by individual seconds.
 *                 If sDigitTwo is equal to zero, then sDigitOne is subtracted by 1. When sDigitOne is equal to zero, minutes is subtracted by 1, everytime minutes are subtracted by
 *                 and sDigitOne and sDigitTwo are set to represent 59 seconds (sOne=5,sTwo=9)
 *      setMinutes(int): This is a void function, it takes an integer and sets the minutes variable, this represents the number of minutes the therapy will take.
 *      setSeconds(int): This is a void function, it also takes an integer which sets the seconds variable, this can be used to set the two variables representing seconds.
 *      getDisplayNumbers(): returns a QString value, the QString is the display numbers which are to be shown on the QLCD display.
 *      isTimerfinished(): return a boolean value, If all three integer variables equal zero it will return true, if not it will return false.
 *      getSecondsRemaining(): returns an integer value, Will return the total number of seconds left in the therapy at any given time.
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
        int getSecondsRemaining();

    private:
        int minutes;
        int sDigitOne;
        int sDigitTwo;
        bool finished;
};

#endif // COUNTDOWNCLOCK_H
