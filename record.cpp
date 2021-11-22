#include "record.h"

Record::Record(QString wform, float freq,int dur, int power)
{
    frequency = freq;
    duration=dur;
    powerLevel=power;
    waveform=wform;
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
    description=("Session: %s, %d", waveform,duration);
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

/*/
 * Function: Print()
 * Tentatively planning on it emitting a signal will probably change when we actually go about implementing.
 * changed it so that it gives a string value which it will return to the screen. /j
 /*/
QString Record::print(){
    QString report=("WAVEFORM: %s \n FREQUENCY: %f \n DURATION: %d seconds \n POWER LEVEL: %d",waveform,frequency,duration,QString::number(powerLevel));
    return report;
}
