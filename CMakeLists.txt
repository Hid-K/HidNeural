cmake_minimum_required(VERSION 2.8)
project(MachineVision)
find_package(OpenCV REQUIRED)
find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(DCMAKE_BUILD_TYPE, Debug)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
add_library(HidNeural STATIC ./HidNeural.cpp)

add_executable(${PROJECT_NAME} main.cpp)

# set_target_properties(${PROJECT_NAME} PROPERTIES
# MACOSX_BUNDLE ON
# MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME}"
# )

# set_target_properties(${PROJECT_NAME} PROPERTIES
#   MACOSX_BUNDLE TRUE
#   MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
# )


target_link_libraries(${PROJECT_NAME} HidNeural)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})