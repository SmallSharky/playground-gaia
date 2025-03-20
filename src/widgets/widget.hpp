#pragma once


#include <../src/core/lv_obj_private.h>



class Widget {
    lv_obj_t lvObj;
public:
    static Widget * getActiveScreen();
};