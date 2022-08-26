#pragma once
#include "CUtil/util.hpp"

class SoundNode{
    bool del_A=false;
    bool del_B=false;
    SoundNode* c_A;
    union{
        SoundNode* c_B;
        double val=0;
    };
    union{
        double (*ufunc)(double);
        double (*bifunc)(double,double);
    };
    double (*evaller)(SoundNode&,double);

    double maker_eval(SoundNode& sn,double t){
        return sn.ufunc(t);
    }
    double unary_eval(SoundNode& sn,double t){
        return sn.ufunc(sn.c_A->get_sample(t));
    }
    double binary_eval(SoundNode& sn,double t){
        return sn.bifunc(sn.c_A->get_sample(t),sn.c_A->get_sample(t));
    }

    SoundNode(){}
public:
    ~SoundNode(){
        if(del_A){
            delete c_A;
        }
        if(del_B){
            delete c_B;
        }
    }
    SoundNode(SoundNode& b){*this=b;}
    double get_sample(double time){
        return evaller(*this,time);
    }
    static SoundNode constant(double val);
    static SoundNode maker(double (*func)(double));
    static SoundNode unary(double (*func)(double));
    static SoundNode binary(double (*func)(double,double));
};

SoundNode operator - (SoundNode& a);

SoundNode operator + (SoundNode& a,SoundNode& b);
SoundNode operator - (SoundNode& a,SoundNode& b);
SoundNode operator * (SoundNode& a,SoundNode& b);
SoundNode operator / (SoundNode& a,SoundNode& b);
