#include "sound.hpp"
#include <cmath>

Sound Sound::imitate(const Sound& b){
    Sound ret;
    ret.setBitDepth(b.getBitDepth());
    ret.setNumChannels(b.getNumChannels());
    ret.setNumSamplesPerChannel(b.getNumSamplesPerChannel());
    ret.setSampleRate(b.getSampleRate());
    return ret;
}

void generate(double(*gen)(double),Sound& target){
    for(size_t n=0;n<target.getNumSamplesPerChannel();n++){
        target.samples[0][n]=gen((double)n/target.getSampleRate());
    }
}

Sound modify(double(*op)(double,double),Sound& a){
    Sound ret=Sound::imitate(a);
    for(size_t n=0;n<ret.getNumSamplesPerChannel();n++){
        ret.samples[0][n]=op(a.samples[0][n],(double)n/ret.getSampleRate());
    }
    return ret;
}

Sound combine(double(*op)(double,double),const Sound& a,const Sound& b){
    Sound ret=Sound::imitate(a);
    for(size_t n=0;n<ret.getNumSamplesPerChannel();n++){
        ret.samples[0][n]=op(a.samples[0][n],b.samples[0][n]);
    }
    return ret;
}
Sound combine(double(*op)(double,double),const Sound& a,double b){
    Sound ret=Sound::imitate(a);
    for(size_t n=0;n<ret.getNumSamplesPerChannel();n++){
        ret.samples[0][n]=op(a.samples[0][n],b);
    }
    return ret;
}
Sound combine(double(*op)(double,double),double a,const Sound& b){
    Sound ret=Sound::imitate(b);
    for(size_t n=0;n<ret.getNumSamplesPerChannel();n++){
        ret.samples[0][n]=op(a,b.samples[0][n]);
    }
    return ret;
}


double SoundGen::sample(double t){
    return 0;
}

double SoundGen::sample(double orig,double t){
    return sample(t);
}

void SoundGen::gen_sound(Sound& target){
    for(size_t n=0;n<target.getNumSamplesPerChannel();n++){
        target.samples[0][n]=sample(target.samples[0][n],(double)n/target.getSampleRate());
    }
}


double SineWave::sample(double t){
    return sin(6.28*t*freq+phase)*amp;
}

double FadeOut::sample(double orig,double t){
    double x=t/duration;
    return ((x-1)*(factor+1)/(factor*(2*x-1)-1))*orig;
}
