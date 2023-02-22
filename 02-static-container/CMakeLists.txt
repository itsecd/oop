cmake_minimum_required(VERSION 3.11)

project(static_container CXX)

set(CMAKE_CXX_STANDARD 23)

# Включаем высокий уровень предупреждений для MSVC
if(MSVC)
    # Включаем высокий уровень предупреждений
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

add_executable(static_container "static_container.cc")
