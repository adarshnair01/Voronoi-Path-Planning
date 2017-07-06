cmake_minimum_required(VERSION 2.8)

project(mocmaes)

# Find the Shark libraries and includes
# set Shark_DIR to the proper location of Shark
find_package(Shark REQUIRED)
find_package(OpenCV REQUIRED)
include(${SHARK_USE_FILE})

# Executable
add_executable(mocmaes mocmaes.cpp)
target_link_libraries(mocmaes ${SHARK_LIBRARIES} ${OpenCV_LIBS})
