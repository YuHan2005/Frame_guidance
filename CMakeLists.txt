cmake_minimum_required(VERSION 3.16)
project(FrameGuidance CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#这句话必须有，不然美发用clang提供的命令补全
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTS "Build unit/integration tests" ON)

# 依赖（按需）
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

# 编译业务库
add_subdirectory(math)
add_subdirectory(src)


# 主程序（可以暂时留空，或先不编译）
add_executable(frame_guidance main.cpp)
target_link_libraries(frame_guidance PRIVATE frame_guidance_lib)
target_compile_definitions(frame_guidance PRIVATE FG_VERSION="0.1.0")

# 测试
if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(src/test)
endif()
