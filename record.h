#ifndef RECORD_H
#define RECORD_H
#include <QLibrary>

class Record
{
    public:
        Record(QString wform,float freq,int dur, int power);
        ~Record();
        QString getRecord();
        QString getWaveForm();
        float getFrequency();
        int getDuration();
        int getPowerLevel();
        void print();

    private:
        QString record;
        QString waveform;
        float frequency;
        int duration;
        int powerLevel;


    public slots:

    signals:
        QString sendTherapyInfo(QString);

};

#endif // RECORD_H
