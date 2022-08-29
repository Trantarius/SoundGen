 
#include "CUtil/util.hpp"
#include <cmath>
#include "AudioFile.h"
#include "sound.hpp"


int main()
{
    Sound wav(1);
    SineWave(100,0,0.5).gen_sound(wav);

    wav.save("out.wav");
    system("play out.wav");
}
