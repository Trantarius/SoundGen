 
#include "CUtil/util.hpp"
#include <cmath>
#include "AudioFile.h"

typedef double (*SoundNode)(double);

SoundNode operator +(SoundNode a,SoundNode b){

}

int main()
{
    AudioFile<double> wav;
    double length=1;
    double freq=100;
    wav.setNumSamplesPerChannel(length*wav.getSampleRate());
    for(size_t n=0;n<wav.getNumSamplesPerChannel();n++){
        wav.samples[0][n]=sin((double)n/wav.getSampleRate()*6.28*freq);
    }
    wav.save("out.wav");
    system("play out.wav");
}
