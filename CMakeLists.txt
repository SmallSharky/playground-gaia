cmake_minimum_required(VERSION 3.24)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(lvgl_display_app)



# add_subdirectory(thirdparty/kikuchan/pngle)

FILE(GLOB app_sources src/*.c src/*.cpp src/*.h src/*.hpp)
target_sources(app PRIVATE ${app_sources})

target_link_libraries(app PRIVATE zephyr_interface)
