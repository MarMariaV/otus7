cmake_minimum_required(VERSION 3.16)
project(otus7)

set(CMAKE_CXX_STANDARD 17)

add_executable(otus7 bulk.cpp bulk_class.cpp observer.h)

if (MSVC)
    target_compile_options(otus7 PRIVATE
            /W4
            )
else ()
    target_compile_options(otus7 PRIVATE
            -Wall -Wextra -pedantic
            )
endif()
