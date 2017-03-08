
cmake_minimum_required(VERSION 3.2.3)
project(interpolation)

#Qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)
#Qt5

file(GLOB SOURCE_FILES "*.cpp" "*.h")
add_executable(visuliser ${SOURCE_FILES})

target_link_libraries(visuliser
Qt5::Widgets
)
