cmake_minimum_required(VERSION 3.22.1)

# 设置项目名称
project("project1_android")

# 设置编码选项
add_compile_options(-U_CRT_STDIO_ISO_WIDE_SPECIFIERS)
add_compile_options(-Wno-invalid-source-encoding)

# 创建共享库
add_library(
        project1_android
        SHARED
        src/main/cpp/main.cpp
)

# 添加JNI头文件路径
find_library(log-lib log)
target_include_directories(
        project1_android 
        PRIVATE ${CMAKE_SOURCE_DIR}/src/main/cpp
        PRIVATE ${ANDROID_NDK}/sources/android/native_app_glue
)

# 链接依赖库
target_link_libraries(
        project1_android
        android
        log
        ${log-lib}
)

# 配置C++标准
set_target_properties(
        project1_android
        PROPERTIES 
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
