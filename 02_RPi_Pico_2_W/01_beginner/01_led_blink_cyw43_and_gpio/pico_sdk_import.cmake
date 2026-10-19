# This is a copy of <PICO_SDK_PATH>/external/pico_sdk_import.cmake

# This can be used in an external project to use a version of the Raspberry Pi Pico SDK, that is not embedded in the
# current tree. You can either set PICO_SDK_PATH in your environment, or pass -DPICO_SDK_PATH=/path/to/pico-sdk
# to your CMake configure line.

if (DEFINED ENV{PICO_SDK_PATH} AND (NOT PICO_SDK_PATH))
    set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
    message("Using PICO_SDK_PATH from environment ('${PICO_SDK_PATH}')")
endif ()

if (DEFINED PICO_SDK_PATH)
    # Check if the path actually exists
    if (NOT EXISTS "${PICO_SDK_PATH}")
        message(FATAL_ERROR "Directory specified by PICO_SDK_PATH does not exist: ${PICO_SDK_PATH}")
    endif ()
    set(PICO_SDK_PATH "${PICO_SDK_PATH}" CACHE PATH "Path to the Raspberry Pi Pico SDK")
elseif (PICO_SDK_FETCH_FROM_GIT)
    include(FetchContent)
    FetchContent_Declare(
            pico_sdk
            GIT_REPOSITORY https://github.com/raspberrypi/pico-sdk
            GIT_TAG master
    )
    message("Downloading Raspberry Pi Pico SDK")
    FetchContent_MakeAvailable(pico_sdk)
    set(PICO_SDK_PATH ${pico_sdk_SOURCE_DIR} CACHE PATH "Path to the Raspberry Pi Pico SDK")
else ()
    message(FATAL_ERROR "PICO_SDK_PATH is not set and PICO_SDK_FETCH_FROM_GIT is not enabled")
endif ()

set(PICO_SDK_PATH "${PICO_SDK_PATH}" CACHE PATH "Path to the Raspberry Pi Pico SDK")

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

