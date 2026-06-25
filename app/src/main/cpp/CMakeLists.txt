cmake_minimum_required(VERSION 3.22.1)
project("akironlauncher")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(DOBBY_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dobby/libdobby.a)

if(NOT EXISTS ${DOBBY_LIB_PATH})
    message(FATAL_ERROR "libdobby.a not found at ${DOBBY_LIB_PATH}")
endif()

add_library(dobby STATIC IMPORTED)
set_target_properties(dobby PROPERTIES
    IMPORTED_LOCATION ${DOBBY_LIB_PATH}
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/dobby/include
)

add_library(${CMAKE_PROJECT_NAME} SHARED
    main.cpp
     KittyMemory/KittyMemory.cpp
     KittyMemory/KittyUtils.cpp
     KittyMemory/MemoryBackup.cpp
     KittyMemory/MemoryPatch.cpp
     LocalPlayer/LocalPlayer.cpp
     include/Wrench.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/AkironPatch
)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    -ffast-math
    -fPIC
    -O2
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    ANDROID=1
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    android
    log
    dl
    m
    z
    dobby
)