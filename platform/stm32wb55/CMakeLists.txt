cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME stm32wb55)

set(PROJECT_NAMESPACE platform)

add_library(${PROJECT_NAME}
STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/system_stm32wbxx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32wbxx_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/syscalls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/sysmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_rcc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_ll_rcc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_rcc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_flash_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_hsem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_dma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_dma_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_pwr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_pwr_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_cortex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_exti.c
)
add_library(${PROJECT_NAMESPACE}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} 
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32WBxx_HAL_Driver/Inc/Legacy
)

target_compile_definitions(${PROJECT_NAME}
PUBLIC
    STM32WB55xx
    USE_HAL_DRIVER
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
)
