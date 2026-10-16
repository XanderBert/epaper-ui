#include "battery.h"

#include <stdio.h>  // snprintf

#include <Fonts/FreeSans9pt7b.h>

#include "colors.h"

namespace epaper_ui {

namespace {

constexpr int LOW_PERCENT = 20;  // at or below this, the icon turns red

}  // namespace

void drawBattery(Adafruit_GFX& g, float volts, int percent, int16_t x, int16_t y) {
  const bool low = percent <= LOW_PERCENT;
  const uint16_t color = low ? RED : BLACK;

  // The body (a 2-pixel outline) and the little terminal nub on the right.
  constexpr int16_t W = 34, H = 16;
  g.drawRoundRect(x, y, W, H, 3, BLACK);
  g.drawRoundRect(x + 1, y + 1, W - 2, H - 2, 2, BLACK);
  g.fillRect(x + W, y + 5, 3, H - 10, BLACK);

  // The charge bar inside, as wide as the percentage. "+ 50" rounds to the
  // nearest pixel instead of always rounding down.
  constexpr int16_t INNER_W = W - 6;
  const int16_t level = (INNER_W * percent + 50) / 100;
  if (level > 0) {
    g.fillRect(x + 3, y + 3, level, H - 6, color);
  }

  // The numbers. snprintf() formats text into a buffer, like printf() but
  // into a string: %.2f = a number with 2 decimals, %% = a literal "%".
  char text[20];
  snprintf(text, sizeof(text), "%.2f V  %d%%", static_cast<double>(volts), percent);
  g.setFont(&FreeSans9pt7b);
  g.setTextColor(color);
  g.setCursor(x + W + 9, y + H - 2);  // baseline, lined up with the icon's bottom
  g.print(text);
}

}  // namespace epaper_ui
