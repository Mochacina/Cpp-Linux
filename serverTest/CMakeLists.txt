cmake_minimum_required(VERSION 3.0.0)
project(curlhttplib VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_TOOLCHAIN_FILE /opt/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "")

find_package(httplib CONFIG REQUIRED)
target_link_libraries(main PRIVATE httplib::httplib)

add_executable(curlhttplib curlHttplib.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
