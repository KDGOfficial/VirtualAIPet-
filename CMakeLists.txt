cmake_minimum_required(VERSION 3.16)
project(VirtualAIPet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_ONNX "Enable ONNX Runtime support (if available)" OFF)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/third_party)

file(GLOB SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_executable(VirtualAIPet ${SOURCES})

target_link_libraries(VirtualAIPet PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

if (WIN32)
  target_compile_definitions(VirtualAIPet PRIVATE PLATFORM_WINDOWS)
  target_link_libraries(VirtualAIPet PRIVATE Ole32)
elseif(UNIX)
  target_compile_definitions(VirtualAIPet PRIVATE PLATFORM_UNIX)
  find_package(Threads REQUIRED)
  target_link_libraries(VirtualAIPet PRIVATE Threads::Threads)
endif()

if(ENABLE_ONNX)
  message(STATUS "Trying to enable ONNX Runtime support")
  find_path(ONNXRUNTIME_INCLUDE_DIR onnxruntime_c_api.h)
  find_library(ONNXRUNTIME_LIBRARY NAMES onnxruntime libonnxruntime)
  if(ONNXRUNTIME_INCLUDE_DIR AND ONNXRUNTIME_LIBRARY)
    message(STATUS "ONNX Runtime found")
    target_compile_definitions(VirtualAIPet PRIVATE ENABLE_ONNX_RUNTIME)
    target_include_directories(VirtualAIPet PRIVATE ${ONNXRUNTIME_INCLUDE_DIR})
    target_link_libraries(VirtualAIPet PRIVATE ${ONNXRUNTIME_LIBRARY})
  else()
    message(WARNING "ONNX Runtime not found — build will proceed without ONNX")
  endif()
endif()