cmake_minimum_required(VERSION 3.20)

## Set firmware name
#set(FIRMWARE_NAME __CHANGEME__)
project(${FIRMWARE_NAME})

set(CMAKE_CXX_STANDARD 17)

include(cmake/CPM.cmake)
CPMAddPackage("gh:electro-smith/libDaisy#master")
CPMAddPackage("gh:electro-smith/DaisySP#master")

set(LINKER_SCRIPT ${libdaisy_SOURCE_DIR}/core/STM32H750IB_flash.lds)

add_executable(${FIRMWARE_NAME} src/main.cpp)

target_link_libraries(${FIRMWARE_NAME} PRIVATE daisy DaisySP)

set_target_properties(${FIRMWARE_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    SUFFIX ".elf"
    LINK_DEPENDS ${LINKER_SCRIPT}
)

target_link_options(${FIRMWARE_NAME} PUBLIC
    -T ${LINKER_SCRIPT}
    -Wl,-Map=${FIRMWARE_NAME}.map,--cref
    -Wl,--check-sections
    -Wl,--unresolved-symbols=report-all
    -Wl,--warn-common
    -Wl,--warn-section-align
    -Wl,--print-memory-usage
)

add_custom_command(TARGET ${FIRMWARE_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
    ARGS -O ihex
    -S ${FIRMWARE_NAME}.elf
    ${FIRMWARE_NAME}.hex
    BYPRODUCTS
    ${FIRMWARE_NAME}.hex
    COMMENT "Generating HEX image"
VERBATIM)

add_custom_command(TARGET ${FIRMWARE_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
    ARGS -O binary
    -S ${FIRMWARE_NAME}.elf
    ${FIRMWARE_NAME}.bin
    BYPRODUCTS
    ${FIRMWARE_NAME}.bin
    COMMENT "Generating binary image"
VERBATIM)
