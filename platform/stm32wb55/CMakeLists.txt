cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME stm32wb55)

set(PROJECT_NAMESPACE platform)

project(${PROJECT_NAME}
        DESCRIPTION "STM32WB55 specific code"
        LANGUAGES C CXX ASM)

add_library(${PROJECT_NAME}
STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/system_stm32wbxx.c
)
add_library(${PROJECT_NAMESPACE}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} 
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Inc/Legacy
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
)
