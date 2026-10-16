#include "shapes.h"

#include <math.h>

namespace epaper_ui {

namespace {

int16_t px(float v) { return static_cast<int16_t>(lroundf(v)); }

}  // namespace

void thickLine(Adafruit_GFX& g, Point a, Point b, float width, uint16_t color) {
  // A wide line is just a long thin rectangle (= two triangles) with a dot
  // on each end to round it off.
  const float half = width / 2;
  const float dx = b.x - a.x, dy = b.y - a.y;
  const float len = sqrtf(dx * dx + dy * dy);
  if (len > 0.5f) {
    // (nx, ny) points sideways from the line, half a line-width long.
    const float nx = -dy / len * half, ny = dx / len * half;
    g.fillTriangle(px(a.x + nx), px(a.y + ny), px(b.x + nx), px(b.y + ny),
                   px(b.x - nx), px(b.y - ny), color);
    g.fillTriangle(px(a.x + nx), px(a.y + ny), px(b.x - nx), px(b.y - ny),
                   px(a.x - nx), px(a.y - ny), color);
  }
  const int16_t capRadius = static_cast<int16_t>((width - 1) / 2);
  g.fillCircle(px(a.x), px(a.y), capRadius, color);
  g.fillCircle(px(b.x), px(b.y), capRadius, color);
}

Point bezier(Point p0, Point p1, Point p2, float t) {
  const float u = 1 - t;
  return {u * u * p0.x + 2 * u * t * p1.x + t * t * p2.x,
          u * u * p0.y + 2 * u * t * p1.y + t * t * p2.y};
}

void thickCurve(Adafruit_GFX& g, Point p0, Point p1, Point p2, float width, uint16_t color) {
  // Curves are drawn as many short straight pieces.
  constexpr int SEGMENTS = 24;
  Point prev = p0;
  for (int i = 1; i <= SEGMENTS; i++) {
    const Point next = bezier(p0, p1, p2, static_cast<float>(i) / SEGMENTS);
    thickLine(g, prev, next, width, color);
    prev = next;
  }
}

void outline(Adafruit_GFX& g, const Point* points, int count, float width, uint16_t color) {
  for (int i = 0; i < count; i++) {
    thickLine(g, points[i], points[(i + 1) % count], width, color);
  }
}

}  // namespace epaper_ui
