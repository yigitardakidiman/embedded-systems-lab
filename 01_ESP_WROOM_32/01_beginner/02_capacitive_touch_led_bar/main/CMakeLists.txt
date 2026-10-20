idf_component_register(SRCS "main.c"
                       INCLUDE_DIRS "."
                       REQUIRES driver esp_driver_gpio esp_driver_touch_sens)

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-error=cpp" "-Wno-cpp")
