#ifndef BATTERY_H
#define BATTERY_H
#include<QLibrary>
#include<QTimer>
#include <iostream>
/* Header for the battery class. The purpose of this class is to simulate battery life in the device. When the device reaches 5% and 2% it will send out a warning and when it reachs 0% it will shut off.
 * Variables:
 * double power: a double which represents the batteries numerical life.
 * double baseDrainAmount: amount which is subtracted from power to simulate a battery draining. This value.
 * double drainModifier:When a session is ran, the battery loses more power. This modifier is added to the baseDrainAmount when a session is active.
 * bool powerWarning: This boolean checks if power is lower than a certain value.When it is, it becomes true.
 * bool twoPercentWarning: same as powerWarning, but when power is a value lower than 2.
 * Qtimer* timer: a Qt object which keeps track of a set amount of time.
 * Signal Functions:
 * charge():sets the power value to 100, resetting powerWarning and twoPercentWarning to false and emits a signal to update battery.
 * startBatteryDrain(): starts timer. timer will be allocated a set value to countdown from.
 * stopBatteryDrain(): stops timer.
 * setDrainMultiplier(double): sets the value of setDrainMultiplier with the value of the double.
 * setBaseDrainValue(double): sets the baseDrainValue variable with the value of the double.
 * hasPower(): boolean return method. Checks the power value to see if it lower than 2.5, and returns false if it is and true if it is not.
 * getBatteryPercentage(): returns the power value.
 * drain():private function. Called when timer reaches the end of it's time. Decreases the power value by baseDrainAmount*BasDrainMultiplier.
 * Signals
 * updateBatteryBar(int):Signal connected to the battery Qt object. changes the battery life based on power.
 * shutDown():sends a shut down command to the system. Simulating power loss.
 * batteryMessage(QString message): sends warnings when powerWarning/twoPercentWarning are true.
 *
 *
 *
 *
 * */
using namespace std;
class Battery : public QObject
{
    Q_OBJECT
    public :
        Battery();
        ~Battery();
        void charge();
        void startBatteryDrain();
        void stopBatteryDrain();
        void setDrainMultiplier(double);
        void setBaseDrainValue(double);
        bool hasPower();
        double getBatteryPercentage();
        void toggleRealism();
        void resetPowerDraw();
    private:
        double power;
        double baseDrainAmount;
        double drainModifier;
        QTimer* timer;
        void drain();
        bool powerWarning;
        bool twoPercentWarning;
        bool realisticPowerDraw;

    private slots:

    signals:
         void updateBatteryBar(int);
         void shutDown();
         void batteryMessage(QString message);
};

#endif // BATTERY_H
