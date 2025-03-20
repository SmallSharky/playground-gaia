
#include "placement_new.hpp"

#include "hello_widget.hpp"

#include <lvgl.h>

#include <../src/core/lv_obj_class_private.h>
#include <../src/misc/lv_event_private.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(HelloWidget, LOG_LEVEL_INF);


namespace
{
    struct HelloWidgetClass
    {
        static void onEvent(const lv_obj_class_t *class_p, lv_event_t *event_p)
        {
            auto& event = *event_p;
            switch (event.code) {
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