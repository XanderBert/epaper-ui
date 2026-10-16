#pragma once

#include <Adafruit_GFX.h>

namespace epaper_ui {

// Draws a battery icon followed by e.g. "3.92 V  78%". (x, y) is the top-left
// corner of the icon; the whole thing is up to 150 x 16 pixels ("4.20 V  100%").
// At 20 % or less it turns red.
void drawBattery(Adafruit_GFX& gfx, float volts, int percent, int16_t x, int16_t y);

}  // namespace epaper_ui
