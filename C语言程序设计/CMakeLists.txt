cmake_minimum_required( VERSION 3.0 )

project( Clanguage_homework )   # name | 项目名称

## 判断编译器
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
# using Clang
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
# using GCC
    set(CMAKE_C_FLAGS "-std=c99 -finput-charset=UTF-8 -fexec-charset=GBK")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
# using Intel C++
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
# using Visual Studio C++
    set(CMAKE_C_FLAGS "/TC /Za /source-charset:utf-8 /execution-charset:GBK")
endif()

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)   # build type | 构建方式
ENDIF()

MESSAGE("Build Type:" ${CMAKE_BUILD_TYPE})

include_directories('${PROJECT_SOURCE_DIR}/classTest')
include_directories('${PROJECT_SOURCE_DIR}/homework')
include_directories('${PROJECT_SOURCE_DIR}/others')

# setup sources in classTest/
# 设置 classTest 文件夹下的源代码

set(CLASSTESTS 
    classTest/Apr3rd.c
    classTest/Apr10th.c
    classTest/Apr17th.c
    classTest/Apr24th.c
    classTest/May8th.c
    classTest/May15th.c
    classTest/May22nd.c
)

add_library(classTest ${CLASSTESTS})

# setup sources in homework/
# 设置 homework 文件夹下的源代码

set(HOMEWORKS
    homework/Mar6th.c
    homework/Mar13th.c
    homework/Mar20th.c
    homework/Mar27th.c
    homework/Apr4th.c
    homework/Apr10th.c
    homework/Apr17th.c
    homework/May8th.c
    homework/May15th.c
    homework/May22nd.c
)

add_library(homeWork ${HOMEWORKS})

# setup sources in others/
# 设置 others 文件夹下的源代码

set(OTHERS
    others/1.c
    others/findASpecialCollection.c
    others/findSaddlePoint.c
    others/pdfRenamer.c
    others/rational_number.c
    others/sortTest.c
)

add_library(others ${OTHERS})
add_library(strings strings.c)

# set main source
# 设置主程序
add_executable(Clanguage_homework main.c)

# link sources to main
# 把其他程序连接到主程序
target_link_libraries(Clanguage_homework
    PUBLIC
        classTest
        homeWork
        others
        strings
)

#[[
set_property(TARGET
    Clanguage_homework
    classTest
    homeWork
    others
    PROPERTY C_STANDARD 99)
]]