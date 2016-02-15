cmake_minimum_required(VERSION 3.3)
project(HabitatControl)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/TemperatureControl.cpp src/TemperatureControl.h src/Logging.cpp src/Logging.h src/RFComm.cpp src/RFComm.h)
add_executable(HabitatControl ${SOURCE_FILES})