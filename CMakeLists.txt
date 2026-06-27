cmake_minimum_required(VERSION 3.28)

project(ThetaMCU
        LANGUAGES C CXX ASM)

set(CMAKE_EXECUTABLE_SUFFIX .elf)

# Флаги ядра
set(${PROJECT_NAME}_CPU_FLAGS
    -mcpu=cortex-m4
    -mfpu=fpv5-sp-d16
    -mfloat-abi=hard
    -mthumb
)
add_compile_options(${${PROJECT_NAME}_CPU_FLAGS})

# Устанавливаем папки с h-ками
set(${PROJECT_NAME}_INC
    ${CMAKE_CURRENT_SOURCE_DIR}/app/inc
)

# Устанавливаем компилируемые файлы
set(${PROJECT_NAME}_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/app/src/main.c
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INC})

# Устанавливаются путь куда будет помещаться elf-файл
set_target_properties(${PROJECT_NAME}
   PROPERTIES
   ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}"
   LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}"
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}"
)

add_subdirectory(platform/stm32wb55)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    platform::stm32wb55
)

set(ASM_DEFS )

set(C_DEFS )

set(CPP_DEFS )

set(COMMON_FLAGS
    -fdiagnostics-color
)

set(ASM_FLAGS ${COMMON_FLAGS} -x assembler-with-cpp)

set(C_FLAGS
    ${COMMON_FLAGS}
    -ffunction-sections
    -fdata-sections
    -Wall
    -fstack-usage
)

set(CPP_FLAGS
    ${COMMON_FLAGS}
    -fno-exceptions
    -fno-rtti
    -fno-use-cxa-atexit
)

# Опции компилятора
target_compile_options(${PROJECT_NAME} PUBLIC
    $<$<COMPILE_LANGUAGE:ASM>:${${PROJECT_NAME}_CPU_FLAGS} ${ASM_FLAGS}>
    $<$<COMPILE_LANGUAGE:C>:${${PROJECT_NAME}_CPU_FLAGS} -std=gnu11 ${C_FLAGS}>
    $<$<COMPILE_LANGUAGE:CXX>:${${PROJECT_NAME}_CPU_FLAGS} -std=gnu++17 ${C_FLAGS} ${CPP_FLAGS}>
    $<$<CONFIG:Debug>:-O0;-g3>
    $<$<CONFIG:Release>:-O0>
)

# Макроопределения
target_compile_definitions(${PROJECT_NAME} PUBLIC
    $<$<COMPILE_LANGUAGE:ASM>:${ASM_DEFS}>
    $<$<COMPILE_LANGUAGE:C>:${C_DEFS}>
    $<$<COMPILE_LANGUAGE:CXX>:${CPP_DEFS}>
    $<$<CONFIG:Debug>:
       DEBUG
    >
    $<$<CONFIG:Release>:
       RELEASE
    >
)

# Устанавливаем флаги линкера
target_link_options(${PROJECT_NAME} PUBLIC SHELL:
    -T${CMAKE_CURRENT_SOURCE_DIR}/platform/stm32wb55/linker/stm32wb55xx_flash_cm4.ld
    -L${CMAKE_CURRENT_SOURCE_DIR}/platform/stm32wb55/linker
    ${${PROJECT_NAME}_CPU_FLAGS}
    --specs=nosys.specs -Wl,--gc-sections -static -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group -Wl,-Map=${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}.map
)

# Генерация list-файла
add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD COMMAND
    ${CMAKE_OBJDUMP} -h -S ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX} > ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}.list
)

# Генерация hex-файла
add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD COMMAND
    ${CMAKE_OBJCOPY} -O ihex ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX} ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}.hex
)

# Генерация bin-файла
add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD COMMAND
    ${CMAKE_OBJCOPY} -O binary ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX} ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}.bin
)

# Вывод размера секций
add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD COMMAND
    ${CMAKE_SIZE} --format=berkeley "${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX}"
)