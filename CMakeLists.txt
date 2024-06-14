cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(PicoMeasure C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_EXAMPLES_PATH ${Project_SOURCE_DIR})
set(PICO_BOARD pico_w)


file(GLOB_RECURSE C_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/lib/picoSensors/*.c
	)

pico_sdk_init()

add_executable(picoMeasure ${C_FILES})

pico_enable_stdio_usb(picoMeasure 1)
pico_enable_stdio_uart(picoMeasure 0)

pico_add_extra_outputs(picoMeasure)

target_include_directories(picoMeasure PRIVATE 
	${CMAKE_SOURCE_DIR}/inc
	${CMAKE_SOURCE_DIR}/lib/picoSensors/inc
	)
target_link_libraries(picoMeasure pico_cyw43_arch_lwip_threadsafe_background pico_stdlib)
