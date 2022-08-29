#include "soundnode.hpp"


//make an empty audio file with the same parameters as b
AudioFile<double> imitate(AudioFile<double>& b){
    AudioFile<double> ret;
    ret.setBitDepth(b.getBitDepth());
    ret.setNumChannels(b.getNumChannels());
    ret.setNumSamplesPerChannel(b.getNumSamplesPerChannel());
    ret.setSampleRate(b.getSampleRate());
    return ret;
}


double SoundGen::sample(double t){
    return 0;
}

void SoundGen::gen_sound(AudioFile<double>& target){
    for(size_t n=0;n<target.getNumSamplesPerChannel();n++){
        target.samples[0][n]=sample((double)n/target.getSampleRate());
    }
}

AudioFile<double> SoundGen::gen_sound(double len){
    AudioFile<double> sound;
    sound.setNumSamplesPerChannel(len*sound.getSampleRate());
    gen_sound(sound);
    return sound;
}

void SoundUnOp::gen_sound(AudioFile<double>& target){
    child->gen_sound(target);
    for(size_t n=0;n<target.getNumSamplesPerChannel();n++){
        target.samples[0][n]=unop(target.samples[0][n]);
    }
}

SoundUnOp::~SoundUnOp(){
    if(del){
        delete child;
    }
}

SoundGen* SoundUnOp::clone(){
    return new SoundUnOp(unop,child->clone(),true);
}

void SoundBiOp::gen_sound(AudioFile<double>& target){
    AudioFile<double> b=imitate(target);
    left->gen_sound(target);
    right->gen_sound(b);
    for(size_t n=0;n<target.getNumSamplesPerChannel();n++){
        target.samples[0][n]=biop(target.samples[0][n],b.samples[0][n]);
    }
}

SoundBiOp::~SoundBiOp(){
    if(del_left){
        delete left;
    }
    if(del_right){
        delete right;
    }
}

SoundGen* SoundBiOp::clone(){
    return new SoundBiOp(biop,left->clone(),right->clone(),true,true);
}


double SineWave::sample(double t){
    return sin(6.28*t*freq+phase)*amp;
}

SoundGen* SineWave::clone(){
    return new SineWave(freq,phase,amp);
}
