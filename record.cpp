#include "record.h"

Record::Record(QString wform, float freq,int dur, int power, QString dateInfo)
{
    frequency = freq;
    duration=dur;
    powerLevel=power;
    waveform=wform;
    startTime = dateInfo;
}

Record::Record()
{
    frequency=0.0;
    duration=0;
    powerLevel=0;
    waveform="";
}

Record::~Record(){

}

QString Record::getRecord(){
    description=("WaveForm: "+waveform+" Total Duration: "+QString::number( duration)+" Started: "+startTime);
    return description;
}

QString Record::getWaveForm(){
    return waveform;
}

float Record::getFrequency(){
    return frequency;
}

int Record::getDuration(){
    return duration;
}

int Record::getPowerLevel(){
    return powerLevel;
}

void Record::setFrequency(float freq){
    frequency = freq;
}

void Record::setDuration(int time){
    duration = time;
}

void Record::setPowerLevel(int power){
    powerLevel=power;
}

void Record::setWaveForm(QString wForm){
    waveform = wForm;
}

QString Record::print(){
    QString report=("Time: "+startTime+"\nWAVEFORM: "+waveform+" \nFREQUENCY: "+ QString::number(frequency)+ "Hz\nDURATION: "+QString::number(duration)+ " seconds \nPOWER LEVEL: "+QString::number(powerLevel)+"µA\n");
    return report;
}
