cmake_minimum_required( VERSION 3.0 )

project( playground_win32 )   # name | 项目名称

## 判断编译器
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
# using Clang
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
# using GCC
    set(CMAKE_C_FLAGS "-finput-charset=UTF-8 -fexec-charset=GBK")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
# using Intel C++
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
# using Visual Studio C++
    set(CMAKE_C_FLAGS "/source-charset:utf-8 /execution-charset:GBK")
endif()

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)   # build type | 构建方式
ENDIF()

MESSAGE("Build Type:" ${CMAKE_BUILD_TYPE})

include_directories('./')

set(SOURCES 
    main.cpp
    onPaint.cpp 
    onTimer.cpp )

add_executable(playground_win32 ${SOURCES})

