cmake_minimum_required(VERSION 3.13)

# Hazir derlenmis Pico araclari (picotool ve pioasm)
file(TO_CMAKE_PATH "$ENV{USERPROFILE}/.pico-sdk" PICO_SDK_TOOLS_ROOT)
if (EXISTS "${PICO_SDK_TOOLS_ROOT}/picotool/2.3.1/picotool/picotool.exe")
    set(PICOTOOL_EXECUTABLE "${PICO_SDK_TOOLS_ROOT}/picotool/2.3.1/picotool/picotool.exe" CACHE FILEPATH "Path to picotool" FORCE)
endif()
if (EXISTS "${PICO_SDK_TOOLS_ROOT}/tools/2.3.1/pioasm/pioasm.exe")
    set(PIOASM_EXECUTABLE "${PICO_SDK_TOOLS_ROOT}/tools/2.3.1/pioasm/pioasm.exe" CACHE FILEPATH "Path to pioasm" FORCE)
endif()

# Pico 2 W karti (RP2350 + CYW43439)
set(PICO_BOARD pico2_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(01_led_blink_cyw43_and_gpio C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(01_led_blink_cyw43_and_gpio
    main.c
)

# USB uzerinden seri terminal ciktisi
pico_enable_stdio_usb(01_led_blink_cyw43_and_gpio 1)
pico_enable_stdio_uart(01_led_blink_cyw43_and_gpio 0)

# Kutuphane baglantilari (Pico Standart Kutuphane + CYW43 Dahili LED)
target_link_libraries(01_led_blink_cyw43_and_gpio
    pico_stdlib
    pico_cyw43_arch_none
)

pico_add_extra_outputs(01_led_blink_cyw43_and_gpio)
