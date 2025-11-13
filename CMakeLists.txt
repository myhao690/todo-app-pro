cmake_minimum_required(VERSION 3.20)
project(TodoApp VERSION 1.0.0)

# 使用 C++20 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 开启所有警告
add_compile_options(-Wall -Wextra)

# 包含头文件目录
include_directories(include)

# 创建可执行文件
add_executable(todoapp
    src/main.cpp
    src/task.cpp
)

message(STATUS "TodoApp 项目配置完成！")
