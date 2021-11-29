#ifndef RECORD_H
#define RECORD_H
#include <QLibrary>
#include <QDateTime>
/*
 * Contains information for the Record object, which will hold the information of the session.
 *
 * Variables:
 *      QString description: used to be record. Basically it's a quick description for the record menu
 *      QString waveform: contatins the waveform of the session
 *      float frequency: contains the frequency of the session.
 *      int duration: holds the elapsed time of the session
 *      int powerLevel: holds the level of power that the session was at.
 *
 * Functions:
 *      getRecord(): sets up the desciption variable and then returns it.
 *      getWaveForm():returns the waveform variable
 *      getFrequency(): returns the frequency
 *      getDuration(): returns the duration
 *      getPowerLevel(): returns the powerlevel
 *      print(): creates a Qstring variable which conatins all information from the record.
 *      setFrequency(float freq):sets the frequency
 *      setDuration(int time): sets the duration
 *      setPowerLevel(int power): sets the powerlevel
 *      setWaveForm(QString waveform): sets the waveform.
 * */
class Record
{
    public:
        Record(QString wform,float freq,int dur, int power, QString dateInfo);
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
        QString startTime;


    public slots:

    signals:
        void sendTherapyInfo(QString);

};

#endif // RECORD_H
