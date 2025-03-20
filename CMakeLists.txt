cmake_minimum_required(VERSION 3.24)


find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(lvgl_display_app)



# add_subdirectory(thirdparty/kikuchan/pngle)

FILE(GLOB_RECURSE app_sources src/*.c src/*.cpp src/*.h src/*.hpp)
target_sources(app PRIVATE ${app_sources})
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(app PRIVATE zephyr_interface)
