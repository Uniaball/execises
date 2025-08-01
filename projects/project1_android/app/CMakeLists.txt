cmake_minimum_required(VERSION 3.18.1)

# 设置项目名称
project("project1-android")

# 创建共享库
add_library(
        uniball-game
        SHARED
        src/main/cpp/main.cpp
)

# 添加JNI头文件路径
find_library(log-lib log)
target_include_directories(
        project1-android 
        PRIVATE ${CMAKE_SOURCE_DIR}/src/main/cpp
        PRIVATE ${ANDROID_NDK}/sources/android/native_app_glue
)

# 链接依赖库
target_link_libraries(
        project1-android
        android
        log
        ${log-lib}
)

# 配置C++标准
set_target_properties(
        project1-android
        PROPERTIES 
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
