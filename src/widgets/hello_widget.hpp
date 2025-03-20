#pragma once


#include "widget.hpp"



class HelloWidget: Widget {
    HelloWidget() noexcept;
    
public:
    HelloWidget(const HelloWidget&) = delete;
    HelloWidget(HelloWidget&&) = default;
    ~HelloWidget();

    void doSomething();


    static HelloWidget * create(Widget * parent);
};