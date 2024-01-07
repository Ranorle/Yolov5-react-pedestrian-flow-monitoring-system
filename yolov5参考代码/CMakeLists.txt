cmake_minimum_required(VERSION 3.5)

PROJECT(yolov5)

set(SNPE_INC ${PROJECT_SOURCE_DIR}/inc/snpe/include/zdl)

set(SOURCE ${PROJECT_SOURCE_DIR}/src)

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(
    ${PROJECT_SOURCE_DIR}/inc
    ${SNPE_INC}
    ${OpenCV_INCLUDE_DIRS}
)

link_directories(
    ${PROJECT_SOURCE_DIR}/libs
)

add_definitions(-DUSE_MODEL_FILE)

add_executable(${PROJECT_NAME}
    ${SOURCE}/main.cpp
    ${SOURCE}/TS_YoloClassification.cpp
    ${SOURCE}/time_utility.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/libs/aarch/libSNPE.so
    ${OpenCV_LIBS}
)
