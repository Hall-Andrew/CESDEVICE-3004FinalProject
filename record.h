#ifndef RECORD_H
#define RECORD_H
#include <QLibrary>

class Record
{
    public:
        Record(QString wform,float freq,int dur, int power);
        Record();
        ~Record();
        QString getRecord();
        QString getWaveForm();
        float getFrequency();
        int getDuration();
        int getPowerLevel();
        QString print(); //changed it to string. Gives all the details  of the record
        void setFrequency(float freq); //added setters because of an possible implementation if they arent used will remove /Andrew
        void setDuration(int time);
        void setPowerLevel(int power);
        void setWaveForm(QString waveform);

    private:
        QString description;//used to be record. Basically it's a quick description for the record menu
        QString waveform;
        float frequency;
        int duration;
        int powerLevel;


    public slots:

    signals:
        void sendTherapyInfo(QString);

};

#endif // RECORD_H
