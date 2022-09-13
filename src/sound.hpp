#pragma once
#include "AudioFile.h"

struct Sound:public AudioFile<double>{
    Sound(){}
    Sound(double len){
        setNumSamplesPerChannel(len*getSampleRate());
    }

    static Sound imitate(const Sound& b);
};

void generate(double(*gen)(double),Sound& target);
Sound modify(double(*op)(double,double),Sound& a);
Sound combine(double(*op)(double,double),const Sound& a,const Sound& b);
Sound combine(double(*op)(double,double),const Sound& a,double b);
Sound combine(double(*op)(double,double),double a,Sound& b);

#define BIOP(OP)                                                                       \
inline Sound operator OP (const Sound& a,const Sound& b){                                          \
    return combine([](double a,double b)->double{return a OP b;},a,b);                 \
}                                                                                      \
inline Sound operator OP (const Sound& a,double b){                                          \
    return combine([](double a,double b)->double{return a OP b;},a,b);                 \
}                                                                                      \
inline Sound operator OP (double a,const Sound& b){                                          \
    return combine([](double a,double b)->double{return a OP b;},a,b);                 \
}

BIOP(+)
BIOP(-)
BIOP(*)
BIOP(/)
#undef BIOP

inline Sound operator - (Sound& a){
    return modify([](double a,double)->double{return -a;},a);
}



struct SoundGen{
    virtual double sample(double t);
    virtual double sample(double orig,double t);
    virtual void gen_sound(Sound& target);
};


struct SineWave:public SoundGen{
    double freq=100;
    double phase=0.0;
    double amp=1.0;
    double sample(double t);
    SineWave(double f=100,double p=0.0,double a=1.0):freq(f),phase(p),amp(a){}
};

struct FadeOut:public SoundGen{
    double factor=0;//in range (-1,1)
    double duration=1;//seconds until scale becomes 0
    double sample(double orig,double t);
    FadeOut(double f=0.0,double d=1):factor(f),duration(d){}
};
