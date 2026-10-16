#pragma once

// Shapes Adafruit_GFX doesn't have built in: lines thicker than 1 pixel,
// curves and outlines. They only use the Adafruit_GFX API, so they work on
// any GFX target: e-paper, TFT, OLED or an in-memory GFXcanvas.
//
// The geometry is done in floats and rounded only when the pixels are drawn.

#include <Adafruit_GFX.h>

namespace epaper_ui {

struct Point {
  float x, y;
};

// GFX lines are always 1 pixel wide. This one is `width` pixels wide, with
// round ends.
void thickLine(Adafruit_GFX& gfx, Point a, Point b, float width, uint16_t color);

// A point on a quadratic Bezier curve: it starts at p0, ends at p2 and is
// "pulled" towards p1. t goes from 0 (start) to 1 (end).
Point bezier(Point p0, Point p1, Point p2, float t);

// The Bezier curve from p0 to p2 (see bezier()), drawn as a thick line.
void thickCurve(Adafruit_GFX& gfx, Point p0, Point p1, Point p2, float width, uint16_t color);

// Outlines a closed shape given as a list of `count` corner points.
void outline(Adafruit_GFX& gfx, const Point* points, int count, float width, uint16_t color);

}  // namespace epaper_ui
