cmake_minimum_required(VERSION 3.16)
project(nanogit CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(nanogit
    src/main.cpp
    src/repository.cpp
    src/commands/init.cpp
)

target_include_directories(nanogit PRIVATE src)

target_link_libraries(nanogit PRIVATE
    ZLIB::ZLIB
    OpenSSL::Crypto
)