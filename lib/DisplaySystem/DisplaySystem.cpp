#include "DisplaySystem.h"

// LVGL 1-bit buffer: (128*64)/8 = 1024 bytes
static uint8_t buf[1024];

void my_disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map) {
    DisplaySystem& ds = DisplaySystem::getInstance();
    
    int32_t w = (area->x2 - area->x1 + 1);
    int32_t h = (area->y2 - area->y1 + 1);

    // drawBitmap is the most reliable way to sync LVGL 1-bit with Adafruit GFX
    ds.getRawDisplay().drawBitmap(area->x1, area->y1, px_map, w, h, SH110X_WHITE, SH110X_BLACK);
    
    // Some SH1106 drivers need to be told explicitly to push the buffer to hardware
    if(lv_display_flush_is_last(disp)) {
        ds.getRawDisplay().display();
    }
    
    lv_display_flush_ready(disp);
}

void DisplaySystem::begin() {
    Wire.begin(I2C_SDA, I2C_SCL);
    // Lower I2C speed can help with breadboard noise/glitches
    Wire.setClock(100000); 

    if(!display.begin(SCREEN_ADDRESS, true)) {
        Serial.println("SH1106 Init Failed");
    }

    display.clearDisplay();
    display.display();

    lv_init();
    
    lv_display_t * disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_FULL);

    screen_face = lv_obj_create(NULL);
    screen_climate = lv_obj_create(NULL);
    
    // Set backgrounds to black to avoid artifacts
    lv_obj_set_style_bg_color(screen_face, lv_color_black(), 0);
    lv_obj_set_style_bg_color(screen_climate, lv_color_black(), 0);

    createFaceApp();
    createClimateApp();
    lv_screen_load(screen_face);
}

void DisplaySystem::createFaceApp() {
    left_eye = lv_obj_create(screen_face);
    right_eye = lv_obj_create(screen_face);
    
    auto style_eye = [](lv_obj_t* obj) {
        lv_obj_set_style_bg_color(obj, lv_color_white(), 0);
        lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);
        lv_obj_set_style_radius(obj, 8, 0);
        lv_obj_set_style_border_width(obj, 0, 0);
        lv_obj_set_size(obj, 25, 35);
    };

    style_eye(left_eye);
    style_eye(right_eye);
    lv_obj_align(left_eye, LV_ALIGN_CENTER, -35, 0);
    lv_obj_align(right_eye, LV_ALIGN_CENTER, 35, 0);
}

void DisplaySystem::createClimateApp() {
    label_temp = lv_label_create(screen_climate);
    label_hum = lv_label_create(screen_climate);
    lv_obj_set_style_text_color(label_temp, lv_color_white(), 0);
    lv_obj_set_style_text_color(label_hum, lv_color_white(), 0);
    lv_obj_align(label_temp, LV_ALIGN_CENTER, 0, -12);
    lv_obj_align(label_hum, LV_ALIGN_CENTER, 0, 12);
}

void DisplaySystem::setAppMode(AppMode mode) {
    if (mode == AppMode::FACE) lv_screen_load(screen_face);
    else if (mode == AppMode::CLIMATE) lv_screen_load(screen_climate);
}

void DisplaySystem::updateFace(float x, float y) {
    if (lv_screen_active() != screen_face) return;
    int moveX = constrain(x / 2, -15, 15);
    int moveY = constrain(y / 2, -10, 10);
    lv_obj_set_pos(left_eye, -35 + moveX, moveY);
    lv_obj_set_pos(right_eye, 35 + moveX, moveY);
}

void DisplaySystem::updateClimate(float t, float h) {
    if (lv_screen_active() != screen_climate) return;
    lv_label_set_text_fmt(label_temp, "TEMP: %.1f C", t);
    lv_label_set_text_fmt(label_hum, "HUM: %.1f %%", h);
}

void DisplaySystem::updateUI() { lv_timer_handler(); }