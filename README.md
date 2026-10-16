# epaper-ui

Drawing helpers for Adafruit GFX displays, made for three-colour (black/white/red)
e-paper: thick lines, Bezier curves, outlines and a battery indicator.

It only depends on Adafruit GFX, not on GxEPD2 or any board. So it draws on any GFX
display, and into a `GFXcanvas` for a desktop preview.

## Use it in a project

In `platformio.ini`, pick one of these:

```ini
lib_deps =
    ; while working on the library: use the local folder, edits show up on the next build
    symlink://../libs/epaper-ui
    ; once it's on GitHub: a fixed version
    https://github.com/<you>/epaper-ui.git#v1.0.0
```

## What's in it

| Header | |
|---|---|
| `<epaper_ui/colors.h>` | `epaper_ui::BLACK`, `WHITE`, `RED`. Same values as GxEPD2's `GxEPD_*` |
| `<epaper_ui/shapes.h>` | `Point`, `thickLine()`, `bezier()`, `thickCurve()`, `outline()` |
| `<epaper_ui/battery.h>` | `drawBattery(gfx, volts, percent, x, y)`: icon + "3.92 V  78%", red at 20 % or less |

```cpp
#include <epaper_ui/battery.h>
#include <epaper_ui/colors.h>
#include <epaper_ui/shapes.h>

void drawScreen(Adafruit_GFX& g, float volts, int percent) {
  g.fillScreen(epaper_ui::WHITE);
  epaper_ui::thickLine(g, {20, 20}, {380, 60}, 4, epaper_ui::BLACK);
  epaper_ui::thickCurve(g, {20, 200}, {200, 80}, {380, 200}, 3, epaper_ui::RED);
  epaper_ui::drawBattery(g, volts, percent, 236, 280);
}
```

With GxEPD2, pass the display object as `g`. With
[espink42-board](../espink42-board), `volts` and `percent` come from
`espink42::readBattery()`.

## Releasing a new version

Bump `version` in `library.json`, commit, then tag and push:

```bash
git tag v1.0.1 && git push --tags
```

Projects only pick it up when you change the `#v...` in their `lib_deps`.
