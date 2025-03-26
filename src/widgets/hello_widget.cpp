
#include "placement_new.hpp"

#include "hello_widget.hpp"

#include <lvgl.h>

#include <../src/core/lv_obj_class_private.h>
#include <../src/misc/lv_event_private.h>
#include <../src/core/lv_obj_event.h>
#include <../src/draw/lv_draw_private.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(HelloWidget, LOG_LEVEL_INF);



template<typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

template<typename T>
T min(T a, T b) {
    return a < b ? a : b;
}


void my_custom_widget_draw(lv_event_t * e);

namespace
{
    struct HelloWidgetClass
    {
        static void onEvent(const lv_obj_class_t *class_p, lv_event_t *event_p)
        {
            auto& event = *event_p;
            switch (event.code) {
                // LV_EVENT_PRESSED,             /**< Widget has been pressed */
                // LV_EVENT_PRESSING,            /**< Widget is being pressed (sent continuously while pressing)*/
                // LV_EVENT_PRESS_LOST,          /**< Widget is still being pressed but slid cursor/finger off Widget */
                // LV_EVENT_SHORT_CLICKED,       /**< Widget was pressed for a short period of time, then released. Not sent if scrolled. */
                // LV_EVENT_SINGLE_CLICKED,      /**< Sent for first short click within a small distance and short time */
                // LV_EVENT_DOUBLE_CLICKED,      /**< Sent for second short click within small distance and short time */
                // LV_EVENT_TRIPLE_CLICKED,      /**< Sent for third short click within small distance and short time */
                // LV_EVENT_LONG_PRESSED,        /**< Object has been pressed for at least `long_press_time`.  Not sent if scrolled. */
                // LV_EVENT_LONG_PRESSED_REPEAT, /**< Sent after `long_press_time` in every `long_press_repeat_time` ms.  Not sent if scrolled. */
                // LV_EVENT_CLICKED,             /**< Sent on release if not scrolled (regardless to long press)*/
                // LV_EVENT_RELEASED,            /**< Sent in every cases when Widget has been released */
                // LV_EVENT_SCROLL_BEGIN,        /**< Scrolling begins. The event parameter is a pointer to the animation of the scroll. Can be modified */
                // LV_EVENT_SCROLL_THROW_BEGIN,
                // LV_EVENT_SCROLL_END,          /**< Scrolling ends */
                // LV_EVENT_SCROLL,              /**< Scrolling */
                case LV_EVENT_PRESSED: {
                    LOG_INF("LV_EVENT_PRESSED");
                    break;
                }
                case LV_EVENT_PRESSING: {
                    LOG_INF("LV_EVENT_PRESSING");
                    break;
                }
                case LV_EVENT_PRESS_LOST: {
                    LOG_INF("LV_EVENT_PRESS_LOST");
                    break;
                }
                case LV_EVENT_SHORT_CLICKED: {
                    LOG_INF("LV_EVENT_SHORT_CLICKED");
                    break;
                }
                case LV_EVENT_SINGLE_CLICKED: {
                    LOG_INF("LV_EVENT_SINGLE_CLICKED");
                    break;
                }
                case LV_EVENT_DOUBLE_CLICKED: {
                    LOG_INF("LV_EVENT_DOUBLE_CLICKED");
                    break;
                }
                case LV_EVENT_TRIPLE_CLICKED: {
                    LOG_INF("LV_EVENT_TRIPLE_CLICKED");
                    break;
                }
                case LV_EVENT_LONG_PRESSED: {
                    LOG_INF("LV_EVENT_LONG_PRESSED");
                    break;
                }
                case LV_EVENT_LONG_PRESSED_REPEAT: {
                    LOG_INF("LV_EVENT_LONG_PRESSED_REPEAT");
                    break;
                }
                case LV_EVENT_CLICKED: {
                    LOG_INF("LV_EVENT_CLICKED");
                    break;
                }
                case LV_EVENT_RELEASED: {
                    LOG_INF("LV_EVENT_RELEASED");
                    break;
                }
                case LV_EVENT_SCROLL_BEGIN: {
                    LOG_INF("LV_EVENT_SCROLL_BEGIN");
                    break;
                }
                case LV_EVENT_SCROLL_THROW_BEGIN: {
                    LOG_INF("LV_EVENT_SCROLL_THROW_BEGIN");
                    break;
                }
                case LV_EVENT_SCROLL_END: {
                    LOG_INF("LV_EVENT_SCROLL_END");
                    break;
                }
                case LV_EVENT_SCROLL: {
                    LOG_INF("LV_EVENT_SCROLL");
                    break;
                }
                case LV_EVENT_GESTURE: {
                    LOG_INF("LV_EVENT_GESTURE");
                    break;
                }
                case LV_EVENT_KEY: {
                    LOG_INF("LV_EVENT_KEY");
                    break;
                }
                case LV_EVENT_FOCUSED: {
                    LOG_INF("LV_EVENT_FOCUSED");
                    break;
                }
                case LV_EVENT_DEFOCUSED: {
                    LOG_INF("LV_EVENT_DEFOCUSED");
                    break;
                }
                case LV_EVENT_LEAVE: {
                    LOG_INF("LV_EVENT_LEAVE");
                    break;
                }
                case LV_EVENT_HIT_TEST: {
                    LOG_INF("LV_EVENT_HIT_TEST");
                    break;
                }
                case LV_EVENT_INDEV_RESET: {
                    LOG_INF("LV_EVENT_INDEV_RESET");
                    break;
                }
                case LV_EVENT_HOVER_OVER: {
                    LOG_INF("LV_EVENT_HOVER_OVER");
                    break;
                }
                case LV_EVENT_HOVER_LEAVE: {
                    LOG_INF("LV_EVENT_HOVER_LEAVE");
                    break;
                }
                case LV_EVENT_COVER_CHECK: {
                    LOG_INF("LV_EVENT_COVER_CHECK");
                    break;
                }
                case LV_EVENT_REFR_EXT_DRAW_SIZE:  /**< Get required extra draw area around Widget (e.g. for shadow). The event parameter is `int32_t *` to store the size. */
                {
                    LOG_INF("LV_EVENT_REFR_EXT_DRAW_SIZE");
                    break;
                }
                case LV_EVENT_DRAW_MAIN_BEGIN:     /**< Starting the main drawing phase */
                 {
                    LOG_INF("LV_EVENT_DRAW_MAIN_BEGIN");
                    break;
                }
                case LV_EVENT_DRAW_MAIN:           /**< Perform the main drawing */
                 {
                    LOG_INF("LV_EVENT_DRAW_MAIN");
                    my_custom_widget_draw(event_p);
                    break;
                }
                case LV_EVENT_DRAW_MAIN_END:       /**< Finishing the main drawing phase */
                 {
                    LOG_INF("LV_EVENT_DRAW_MAIN_END");
                    break;
                }
                case LV_EVENT_DRAW_POST_BEGIN:     /**< Starting the post draw phase (when all children are drawn)*/
                 {
                    LOG_INF("LV_EVENT_DRAW_POST_BEGIN");
                    break;
                }
                case LV_EVENT_DRAW_POST:           /**< Perform the post draw phase (when all children are drawn)*/
                 {
                    LOG_INF("LV_EVENT_DRAW_POST");
                    break;
                }
                case LV_EVENT_DRAW_POST_END: {
                    LOG_INF("LV_EVENT_DRAW_POST_END");
                    break;
                }
                case LV_EVENT_LAYOUT_CHANGED: {
                    LOG_INF("LV_EVENT_LAYOUT_CHANGED");
                    break;
                }
                case LV_EVENT_STYLE_CHANGED: {
                    LOG_INF("LV_EVENT_STYLE_CHANGED");
                    break;
                }
                case LV_EVENT_SIZE_CHANGED: {
                    LOG_INF("LV_EVENT_SIZE_CHANGED");
                    break;
                }
                case LV_EVENT_GET_SELF_SIZE: {
                    LOG_INF("LV_EVENT_GET_SELF_SIZE");
                    break;
                }
                default: {
                    LOG_INF("EVT: %u", static_cast<uint32_t>(event.code));
                    break;
                }
            };

        }
        static constexpr lv_obj_class_t lvClass{
            .base_class = &lv_obj_class,
            .event_cb = HelloWidgetClass::onEvent,
            .width_def = LV_PCT(100), // LV_DPI_DEF * 2,
            .height_def = LV_SIZE_CONTENT,
            .instance_size = sizeof(HelloWidget),
        };
    };
}

HelloWidget::HelloWidget() noexcept
{
    auto thisAsLVp = reinterpret_cast<lv_obj_t *>(this);
    lv_obj_set_width(thisAsLVp, 100);
    lv_obj_set_height(thisAsLVp, 100);
    lv_obj_align(thisAsLVp, LV_ALIGN_BOTTOM_LEFT, 0, 0);
}

HelloWidget::~HelloWidget(){

}



HelloWidget *HelloWidget::create(Widget *parent)
{
    auto ptr = lv_obj_class_create_obj(&HelloWidgetClass::lvClass, reinterpret_cast<lv_obj_t *>(parent));
    lv_obj_class_init_obj(ptr);
    HelloWidget *ret = new(ptr) HelloWidget;
    return ret;
}

void HelloWidget::doSomething() {
    LOG_INF("Something");
}


// static void custom_widget_draw(lv_event_t * e) {
//     lv_obj_t * obj = lv_event_get_target(e);
//     lv_draw_ctx_t * draw_ctx = lv_event_get_draw_task(e);

//     // Get the draw descriptor
//     lv_draw_rect_dsc_t draw_dsc;
//     lv_draw_rect_dsc_init(&draw_dsc);

//     // Get the draw area (clipped)
//     const lv_area_t * draw_area = lv_event_get_param(e);  // Optional, or use object's coords
//     lv_area_t coords;
//     lv_obj_get_coords(obj, &coords);

//     // Calculate width and height of the drawing area
//     lv_coord_t width = lv_area_get_width(&coords);
//     lv_coord_t height = lv_area_get_height(&coords);

//     // Allocate buffer for random data (simulate pixels)
//     uint8_t * buffer = lv_mem_alloc(width * height);
//     if(!buffer) return; // Handle allocation failure

//     // Fill the buffer with random data
//     for(int i = 0; i < width * height; i++) {
//         buffer[i] = rand() % 256;
//     }

//     // Optional: visualize the buffer by drawing it pixel by pixel
//     // (LVGL has no "draw raw buffer" API, so we simulate by colored rectangles)
//     for(int y = 0; y < height; y++) {
//         for(int x = 0; x < width; x++) {
//             uint8_t pixel = buffer[y * width + x];
//             lv_color_t color = lv_color_make(pixel, pixel, pixel);  // Grayscale visualization
//             lv_area_t pixel_area = {coords.x1 + x, coords.y1 + y, coords.x1 + x, coords.y1 + y};
//             draw_dsc.bg_color = color;
//             lv_draw_rect(draw_ctx, &draw_dsc, &pixel_area);
//         }
//     }

//     lv_mem_free(buffer);
// }


void actual_draw(lv_layer_t * layer, lv_area_t * obj_area) {
    lv_area_t intersection;
    intersection.x1 = max(layer->buf_area.x1, obj_area->x1);
    intersection.y1 = max(layer->buf_area.y1, obj_area->y1);
    intersection.x2 = min(layer->buf_area.x2, obj_area->x2);
    intersection.y2 = min(layer->buf_area.y2, obj_area->y2);
    LOG_INF("Layer area is (%d, %d) - (%d, %d)", layer->buf_area.x1, layer->buf_area.y1, layer->buf_area.x2, layer->buf_area.y2);
    LOG_INF("Object area is (%d, %d) - (%d, %d)", obj_area->x1, obj_area->y1, obj_area->x2, obj_area->y2);
    LOG_INF("Intersection: (%d, %d) - (%d, %d)", intersection.x1, intersection.y1, intersection.x2, intersection.y2);
    LOG_INF("Intersection size is %d x %d", intersection.x2 - intersection.x1, intersection.y2 - intersection.y1);
    lv_area_t patch_area;
    patch_area.x1 = intersection.x1 - layer->buf_area.x1;
    patch_area.y1 = intersection.y1 - layer->buf_area.y1;
    patch_area.x2 = patch_area.x1 + (intersection.x2 - intersection.x1);
    patch_area.y2 = patch_area.y1 + (intersection.y2 - intersection.y1);
    LOG_INF("Patch area is (%d, %d) - (%d, %d)", patch_area.x1, patch_area.y1, patch_area.x2, patch_area.y2);


    for (int y = patch_area.y1; y <= patch_area.y2; y++) {
        for (int x = patch_area.x1; x <= patch_area.x2; x++) {
            int x_color = x * 255 / (patch_area.x2 - patch_area.x1);
            int y_color = y * 255 / (patch_area.y2 - patch_area.y1);
            lv_color32_t color = lv_color32_make(x_color, y_color, 0, 255);
            // Calculate the pixel index in the buffer
            int index = (y * layer->draw_buf->header.w) + x;
            lv_color32_t * buf = reinterpret_cast<lv_color32_t *>(layer->draw_buf->data);
            buf[index] = color;
        }
    }

}

void my_custom_widget_draw(lv_event_t * e) {
    // lv_obj_t * obj = reinterpret_cast<lv_obj_t *>(lv_event_get_target(e));
    lv_layer_t * layer = lv_event_get_layer(e);
    // lv_layer_t * layer = nullptr;

    lv_obj_t * obj = reinterpret_cast<lv_obj_t *>(lv_event_get_current_target(e));
    // lv_obj_t * obj = nullptr;
    LOG_INF("Draw object %p on layer %p", obj, layer);
    actual_draw(layer, &obj->coords);

    // layer->draw_buf;
    // lv_draw_task_t * task = lv_event_get_draw_task(e);
    // auto dsc = task->draw_dsc;

    // Get the object area
    // lv_area_t coords;
    // lv_obj_get_coords(obj, &coords);

    // lv_coord_t width = lv_area_get_width(&coords);
    // lv_coord_t height = lv_area_get_height(&coords);

    // // Check if we have access to the draw buffer
    // if( && draw_ctx->buf->buf) {
    //     lv_color_t * buf = (lv_color_t *)draw_ctx->buf->buf;
    //     lv_coord_t buf_width = draw_ctx->buf->width;

    //     for(int y = coords.y1; y <= coords.y2; y++) {
    //         for(int x = coords.x1; x <= coords.x2; x++) {
    //             // Calculate the pixel index in the buffer
    //             int index = y * buf_width + x;

    //             // Fill with random color
    //             lv_color_t color = lv_color_make(rand() % 256, rand() % 256, rand() % 256);
    //             buf[index] = color;
    //         }
    //     }
    // }
}
