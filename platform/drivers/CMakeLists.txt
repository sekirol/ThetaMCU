cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME drivers)

set(PROJECT_NAMESPACE platform)

add_library(${PROJECT_NAME}
STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/clock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/error.c
)
add_library(${PROJECT_NAMESPACE}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} 
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    platform::stm32wb55
)
