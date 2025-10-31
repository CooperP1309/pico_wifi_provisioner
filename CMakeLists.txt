cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_wifi_provision C CXX ASM)
pico_sdk_init()

# ---- Configure path to pico-examples (Option B) ----
# You can override this at configure time:
#   cmake -DPICO_EXAMPLES_PATH=/absolute/path/to/pico-examples ..
set(PICO_EXAMPLES_PATH "$ENV{HOME}/pico/pico-examples" CACHE PATH "Path to the pico-examples repository")

add_executable(pico_wifi_provision
    main.cpp
    # adding the source code of sdk packages (note: I imported pico_lfs separately)
    ${PICO_EXAMPLES_PATH}/pico_w/wifi/access_point/dhcpserver/dhcpserver.c	
)

# Including the source space of the dhcp server directory
target_include_directories(pico_wifi_provision PRIVATE
    ${PICO_EXAMPLES_PATH}/pico_w/wifi/access_point/dhcpserver
)

# ---- INCLUDING OF litteFS ----
add_subdirectory(libs/pico-lfs)

#target_link_libraries(pico_wifi_provision PRIVATE pico-lfs)

target_compile_definitions(pico_wifi_provision PRIVATE
  LFS_THREADSAFE=1
  LFS_NO_DEBUG=1
)

# ---- DONE INCLUDING litteFS ----

# Enable at least one stdio transport if you want to see printf()
pico_enable_stdio_usb(pico_wifi_provision 1)   # set to 0 if you prefer UART
pico_enable_stdio_uart(pico_wifi_provision 0)  # set to 1 if you prefer UART

# Link stdlib + CYW43 with lwIP (required for AP mode)
target_link_libraries(pico_wifi_provision
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    pico-lfs 
)

# Optional: request a newer C++ standard if you like
target_compile_features(pico_wifi_provision PRIVATE cxx_std_17)

pico_add_extra_outputs(pico_wifi_provision)

