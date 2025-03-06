cmake_minimum_required(VERSION 3.10)
project(DNN_Face_Detect)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Add the executable
add_executable(dnn_face_detect source.cpp)

# Link OpenCV libraries
target_include_directories(dnn_face_detect PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(dnn_face_detect PRIVATE ${OpenCV_LIBS})