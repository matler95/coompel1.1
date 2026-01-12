#include "DisplaySystem.h"

// LVGL 1-bit buffer must be exactly 1024 bytes for 128x64
static uint8_t buf[1024];

void my_disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map) {
    DisplaySystem& ds = DisplaySystem::getInstance();
    
    // Width and height of the area LVGL is pushing
    int32_t w = (area->x2 - area->x1 + 1);
    int32_t h = (area->y2 - area->y1 + 1);

    // Bypasses coordinate math by using the library's native bitmap handler
    ds.getRawDisplay().drawBitmap(area->x1, area->y1, px_map, w, h, SH110X_WHITE, SH110X_BLACK);
    
    // Only push to physical hardware when the full frame is ready
    if(lv_display_flush_is_last(disp)) {
        ds.getRawDisplay().display();
    }
    
    lv_display_flush_ready(disp);
}