
#include "widget.hpp"

#include <lvgl.h>



Widget * Widget::getActiveScreen() {
    return reinterpret_cast<Widget *>(lv_screen_active());
}
