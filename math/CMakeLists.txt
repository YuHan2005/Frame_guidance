file(GLOB_RECURSE MATH_SOURCES CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(frame_math ${MATH_SOURCES})

target_include_directories(frame_math
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}     # <-- 加上 OpenCV 的头文件目录
)

target_link_libraries(frame_math
  PUBLIC
    Eigen3::Eigen              # 已在根 CMakeLists find_package(Eigen3 REQUIRED)
    ${OpenCV_LIBS}             # <-- 链接 OpenCV（core/imgproc/highgui 等）
)
