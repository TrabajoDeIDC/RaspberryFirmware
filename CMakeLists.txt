cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(PicoMeasure C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_EXAMPLES_PATH ${Project_SOURCE_DIR})
set(PICO_BOARD pico_w)


file(GLOB_RECURSE C_FILES ${CMAKE_SOURCE_DIR}/src/*.c)

pico_sdk_init()

add_executable(PicoMeasure ${C_FILES})

pico_enable_stdio_usb(PicoMeasure 1)
pico_enable_stdio_uart(PicoMeasure 0)

pico_add_extra_outputs(PicoMeasure)

target_include_directories(PicoMeasure PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(PicoMeasure pico_cyw43_arch_lwip_threadsafe_background pico_stdlib)
