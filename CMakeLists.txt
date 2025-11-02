cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Pico SDK ----
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_wifi_provision C CXX ASM)
pico_sdk_init()

# ---- Optional: path to pico-examples (you already had this) ----
set(PICO_EXAMPLES_PATH "$ENV{HOME}/pico/pico-examples" CACHE PATH "Path to the pico-examples repository")

# ============================================
# pico-littlefs (submodule lives at libs/pico-littlefs)
# ============================================
set(PICO_LFS_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/pico-littlefs")

if(EXISTS "${PICO_LFS_DIR}")
    message(STATUS "Found pico-littlefs at: ${PICO_LFS_DIR}")
    if(EXISTS "${PICO_LFS_DIR}/CMakeLists.txt")
        # If your submodule has CMake, bring in its targets (preferred)
        add_subdirectory(${PICO_LFS_DIR})
    endif()
else()
    message(WARNING "libs/pico-littlefs not found. Did you run: git submodule update --init --recursive ?")
endif()

# ============================================
# Your executable and sources
# ============================================
add_executable(pico_wifi_provision
    src/main.cpp
    # Keep using the DHCP example C source for now
    ${PICO_EXAMPLES_PATH}/pico_w/wifi/access_point/dhcpserver/dhcpserver.c
)

# DHCP example include path
target_include_directories(pico_wifi_provision PRIVATE
    ${PICO_EXAMPLES_PATH}/pico_w/wifi/access_point/dhcpserver
)

# stdio transports
pico_enable_stdio_usb(pico_wifi_provision 1)
pico_enable_stdio_uart(pico_wifi_provision 0)

# Core Pico + WiFi
target_link_libraries(pico_wifi_provision
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
)

# ============================================
# Link pico-littlefs (targets and/or headers)
# ============================================
# Try common exported target names
set(_pico_lfs_targets pico_littlefs pico_lfs littlefs)
set(_linked_lfs FALSE)
foreach(_t IN LISTS _pico_lfs_targets)
    if(TARGET ${_t})
        target_link_libraries(pico_wifi_provision PRIVATE ${_t})
        message(STATUS "Linked pico-littlefs target: ${_t}")
        set(_linked_lfs TRUE)
        break()
    endif()
endforeach()

# If no target exported, expose likely include dirs so headers resolve
if(EXISTS "${PICO_LFS_DIR}" AND NOT _linked_lfs)
    target_include_directories(pico_wifi_provision PRIVATE
        ${PICO_LFS_DIR}
        ${PICO_LFS_DIR}/include
        ${PICO_LFS_DIR}/src
        ${PICO_LFS_DIR}/littlefs
    )
    message(STATUS "No pico-littlefs CMake target found; added include paths only.")
endif()

# C++ standard
target_compile_features(pico_wifi_provision PRIVATE cxx_std_17)

# UF2 / bin / hex outputs
pico_add_extra_outputs(pico_wifi_provision)

