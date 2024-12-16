cmake_minimum_required(VERSION 3.30)
project(lab3-builder)

set(OPENSSL_ROOT_DIR "C:/vcpkg/installed/x64-windows")
find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab3-builder main.cpp)
target_link_libraries(lab3-builder OpenSSL::SSL OpenSSL::Crypto)