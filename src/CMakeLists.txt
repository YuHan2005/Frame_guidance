# 收集源码（也可以手动列出更稳）
file(GLOB_RECURSE FG_SOURCES CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(frame_guidance_lib ${FG_SOURCES})

# 头文件给到 PUBLIC，供 main 和 tests 使用
target_include_directories(frame_guidance_lib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(frame_guidance_lib
  PUBLIC
    frame_math          # <<< 关键：继承 math 的包含目录与 Eigen 依赖
    Eigen3::Eigen       # <<< 保险起见，直接也连上（可选，但推荐）
    ${OpenCV_LIBS}
)

# 常用编译选项
target_compile_features(frame_guidance_lib PUBLIC cxx_std_17)
target_compile_definitions(frame_guidance_lib PRIVATE $<$<CONFIG:Debug>:FG_DEBUG>)
