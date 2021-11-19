#include "record.h"

Record::Record(QString wform, float freq,int dur, int power)
{
    frequency = freq;
    duration=dur;
    powerLevel=power;
    waveform=wform;
}

Record::~Record(){

}

QString Record::getRecord(){
    return record;
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

/*/
 * Function: Print()
 * Tentatively planning on it emitting a signal will probably change when we actually go about implementing.
 /*/
void Record::print(){

}
