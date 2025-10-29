cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(blink C CXX ASM)
pico_sdk_init()

# ---- Configure path to pico-examples (Option B) ----
# You can override this at configure time:
#   cmake -DPICO_EXAMPLES_PATH=/absolute/path/to/pico-examples ..
set(PICO_EXAMPLES_PATH "$ENV{HOME}/pico/pico-examples" CACHE PATH "Path to the pico-examples repository")

add_executable(blink
    main.cpp
    # bring in the DHCP server source directly from pico-examples
    ${PICO_EXAMPLES_PATH}/pico_w/wifi/access_point/dhcpserver/dhcpserver.c
)

# Make the dhcpserver headers visible
target_include_directories(blink PRIVATE
    ${PICO_EXAMPLES_PATH}/pico_w/wifi/access_point/dhcpserver
)

# Enable at least one stdio transport if you want to see printf()
pico_enable_stdio_usb(blink 1)   # set to 0 if you prefer UART
pico_enable_stdio_uart(blink 0)  # set to 1 if you prefer UART

# Link stdlib + CYW43 with lwIP (required for AP mode)
target_link_libraries(blink
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
)

# Optional: request a newer C++ standard if you like
target_compile_features(blink PRIVATE cxx_std_17)

pico_add_extra_outputs(blink)

