#pragma once
#include "png++/png.hpp"
#include "sound.hpp"
typedef png::image<png::rgb_pixel> image;

image makeWaveform(Sound& sound,uint width,uint height);
