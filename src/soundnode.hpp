#pragma once
#include "CUtil/util.hpp"
#include "AudioFile.h"
#include <cmath>

namespace ops{
    inline double neg(double a){return -a;}
    inline double abs(double a){return fabs(a);}
    inline double sqr(double a){return a*a;}

    inline double add(double a,double b){return a+b;}
    inline double mul(double a,double b){return a*b;}
    inline double sub(double a,double b){return a-b;}
    inline double div(double a,double b){return a/b;}
    inline double avg(double a,double b){return (a+b)/2;}
    inline double min(double a,double b){return fmin(a,b);}
    inline double max(double a,double b){return fmax(a,b);}
};

struct SoundGen{
    virtual double sample(double t);
    virtual void gen_sound(AudioFile<double>& target);
    AudioFile<double> gen_sound(double len);
    virtual ~SoundGen(){}

    //allows r-values to be used by unop/biop below
    virtual SoundGen* clone()=0;
};

struct SoundUnOp:public SoundGen{
    double (*unop)(double);
    SoundGen* child;
    bool del=false;
    void gen_sound(AudioFile<double>& target);
    SoundUnOp(double(*op)(double),SoundGen* cld,bool own_child=false):
        unop(op),child(cld),del(own_child){}
    SoundUnOp(double(*op)(double),SoundGen&& cld):unop(op),child(cld.clone()),del(true){}
    ~SoundUnOp();

    SoundGen* clone();
};

struct SoundBiOp:public SoundGen{
    double (*biop)(double,double);
    SoundGen *left,*right;
    bool del_left=false,del_right=false;
    void gen_sound(AudioFile<double>& target);
    SoundBiOp(double (*op)(double,double),SoundGen* l,SoundGen* r,bool own_left=false,bool own_right=false):
        biop(op),left(l),right(r),del_left(own_left),del_right(own_right){}
    SoundBiOp(double (*op)(double,double),SoundGen&& l,SoundGen&& r):
        biop(op), left(l.clone()), right(r.clone()), del_left(true), del_right(true){}
    ~SoundBiOp();

    SoundGen* clone();
};


struct SineWave:public SoundGen{
    double freq=100;
    double phase=0.0;
    double amp=1.0;
    double sample(double t);
    SineWave(double f=100,double p=0.0,double a=1.0):freq(f),phase(p),amp(a){}

    SoundGen* clone();
};
