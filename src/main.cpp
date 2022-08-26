 
#include "CUtil/util.hpp"
#include "AudioFile.h"

int main()
{
    AudioFile<double> wav;
    print("sample rate: ",wav.getSampleRate());
    print("bit depth: ",wav.getBitDepth());
    print("num channels: ",wav.getNumChannels());
    print("mono? ",wav.isMono());
    print("stereo? ",wav.isStereo());
    print("num samples: ",wav.getNumSamplesPerChannel());
}
