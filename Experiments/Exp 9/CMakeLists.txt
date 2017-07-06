cmake_minimum_required(VERSION 2.8)

project(main)

# Find the Shark libraries and includes
# set Shark_DIR to the proper location of Shark
find_package(Shark REQUIRED)
find_package(OpenCV REQUIRED)
include(${SHARK_USE_FILE})

# Executable
add_executable(main main.cpp)
target_link_libraries(main ${SHARK_LIBRARIES} ${OpenCV_LIBS})
