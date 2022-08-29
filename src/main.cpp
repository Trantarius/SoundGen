 
#include "CUtil/util.hpp"
#include <cmath>
#include "AudioFile.h"
#include "soundnode.hpp"


int main()
{
    AudioFile<double> wav=SineWave(100,0,0.3).gen_sound(1.0);
    wav.save("out.wav");
    system("play out.wav");
}
