#pragma once

#include <stdint.h>

namespace epaper_ui {

// A black/white/red panel only knows these three colours. They have the same
// values as GxEPD2's GxEPD_BLACK, GxEPD_WHITE and GxEPD_RED, but this library
// doesn't need GxEPD2, so it also draws into a GFXcanvas for a desktop preview.
constexpr uint16_t BLACK = 0x0000;
constexpr uint16_t WHITE = 0xFFFF;
constexpr uint16_t RED   = 0xF800;

}  // namespace epaper_ui
