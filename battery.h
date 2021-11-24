#ifndef BATTERY_H
#define BATTERY_H
#include<QLibrary>
#include<QTimer>
#include <iostream>

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
        double getBatteryPercentage();
        QTimer* getBatteryTimer();

    private:
        double power;
        double baseDrainAmount;
        double drainModifier;
        QTimer* timer;
        void drain();
        bool powerWarning;

    private slots:

    signals:
         void updateBatteryBar(int);
         void shutDown();
};

#endif // BATTERY_H
