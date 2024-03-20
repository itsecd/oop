cmake_minimum_required(VERSION 3.5)

project("base" CXX)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR
   CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
   CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options("-Wall" "-Weffc++" "-Wextra" "-Wpedantic")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
endif()

add_subdirectory("example1-ratio")
add_subdirectory("example2-ratio")

add_subdirectory("practice1-std-iostream")
add_subdirectory("practice2a-std-vector")
add_subdirectory("practice2b-std-random")
add_subdirectory("practice2c-sfml")
add_subdirectory("practice3-std-string")
add_subdirectory("practice4a-std-thread-account")
add_subdirectory("practice4b-std-thread-matrices")
