include(FetchContent)

# 拉取 GoogleTest（离线环境可改为本地路径）
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# 避免把 gtest 自己的测试也编上
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 例：相机测试
add_executable(test_detect detect_test.cpp)
target_link_libraries(test_detect PRIVATE gtest_main frame_guidance_lib)
add_test(NAME test_detect COMMAND test_detect)
