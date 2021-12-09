#ifndef BATTERY_H
#define BATTERY_H
#include<QLibrary>
#include<QTimer>
#include <iostream>
/*
 * The purpose of this class is to simulate the battery power in the device.
 *      - When the device reaches approximately 5% and 3% it will send out a warning
 *      - The power shuts off when it goes before it goes below 2%
 *
 * Variables:
 *      double power: This is a double which represents the batteries numerical power amount.
 *      double baseDrainAmount: This amount is a base drain amount the device loses power from, this value is set to 1 and does is not changed in this project
 *                              The inclusion of this function was done for code reuseability in the event this class would be modified.
 *      double drainModifier: This is a double which is multiplied against the drainModifier and determines how much power is actually drawn at a given time. Its
 *                            base rate is set to 0.001 for realistic power draw and 0.01 for unrealistic.
 *      bool powerWarning: This boolean will be set to true if the device displays the 5% power warning, it ensures the warning will not be repeated again until the device is charged again.
 *      bool twoPercentWarning: This handles identically to powerWarning, but ensures the warning for when the device is shut off is not repeated again until the device is charged.
 *      bool realisticPowerDraw: This boolean is used by the Battery class to determine if it should follow a realistic power drain method or one designed for showcasing the features.
 *                               When this is true the device will have enough power to fully undergo any therapy at least once, when it is false it will not as the powerDrain will not be realistic.
 *      Qtimer* timer: This is a QT timer object which drains the power every 1000ms. We thought it would be best for this class to have its own timer for increased control over how the battery is simulated.
 *
 * Functions:
 *      Battery(): This is the class constructor, it initalizes all the defaults for the battery class.
 *      charge(): This is a void function, it resets the power value to 100% while also setting the powerWarning and twoPercentWarning booleans to false.
 *                and emits a signal telling MainWindow the battery has changed.
 *      startBatteryDrain(): This function starts the battery classes internal timer. The Timer calls the drain function every 1000ms or 1 second.
 *      stopBatteryDrain(): This function stops the timer and by doing so the battery stops being used.
 *      setDrainMultiplier(double): sets the value of setDrainMultiplier with the value of the double.
 *      setBaseDrainValue(double): sets the baseDrainValue variable with the value of the double.
 *      hasPower(): This function returns a boolean variable. It checks the double power variable to see if it lower than 2.5, and returns false if it is and true if it is not.
 *                  This determines if the device has enough power to be on or not.
 *      getBatteryPercentage(): This function returns the batteries percentage as a double.
 *      drain():private function. This is called every 1000ms by the timer. It decreases the power value by (baseDrainAmount*BaseDrainMultiplier) and handles battery low displays.
 *
 * Signals:
 *      updateBatteryBar(int):Signal connected to the battery Qt object. This notifies MainWindow with the new battery percentage.
 *      shutDown():sends a shut down command to the system. Simulating power loss.
 *      batteryMessage(QString message): sends a warnings when powerWarning/twoPercentWarning are true and the battery is low enough to warrant the specific warning.
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
        void calcDrainSkipped(int seconds);
    private:
        double power;
        double baseDrainAmount;
        double drainModifier;
        void drain();
        bool powerWarning;
        bool twoPercentWarning;
        bool realisticPowerDraw;
        QTimer* timer;

    private slots:

    signals:
         void updateBatteryBar(int);
         void shutDown();
         void batteryMessage(QString message);
};

#endif // BATTERY_H
