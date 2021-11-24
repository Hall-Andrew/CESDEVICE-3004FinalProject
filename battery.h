#ifndef BATTERY_H
#define BATTERY_H
#include<QLibrary>
#include<QTimer>
#include <iostream>

using namespace std;
class Battery : public QObject
{
<<<<<<< HEAD
public:
    Battery();
   ~Battery();
   void decay(); //default decay method
   void decay(int mod);//call for when machine is running
   bool IsCharge();
=======
    Q_OBJECT
    public :
        Battery();
        ~Battery();
        void charge();
        void startBatteryDrain();
        void stopBatteryDrain();
        void setDrainMultiplier(double);
        double getBatteryPercentage();
//        QTimer* getBatteryTimer();

    private:
        double power;
        double baseDrainAmount;
        double drainModifier;
        QTimer* timer;
        void drain();
>>>>>>> 184913dcbcb00f3b63efe277822daf1d6f7d26dc

    private slots:

    signals:
         void updateBatteryBar(int);
};

#endif // BATTERY_H
