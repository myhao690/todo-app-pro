cmake_minimum_required(VERSION 3.20)
project(TodoApp VERSION 1.0.0)

# 使用 C++20 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 生成 compile_commands.json 用于 VS Code IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 开启所有警告
add_compile_options(-Wall -Wextra -Wpedantic)

# 包含头文件目录
include_directories(include)

# 设置编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -O0)
    # 启用代码覆盖率
    if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_compile_options(--coverage)
        add_link_options(--coverage)
    endif()
    message(STATUS "构建模式: Debug (启用覆盖率)")
else()
    add_compile_options(-O3)
    message(STATUS "构建模式: Release")
endif()

# 创建可执行文件
add_executable(todoapp
    src/main.cpp
    src/task.cpp
    src/todo_manager.cpp
)

# 启用测试
enable_testing()

# 创建测试可执行文件
add_executable(test_todoapp
    tests/test_main.cpp
    src/task.cpp
    src/todo_manager.cpp
)

# 添加测试
add_test(NAME unit_tests COMMAND test_todoapp)

# 设置测试属性
set_tests_properties(unit_tests PROPERTIES
    TIMEOUT 30
    PASS_REGULAR_EXPRESSION "所有测试通过"
    FAIL_REGULAR_EXPRESSION "测试失败"
)

# 添加内存泄漏测试 (如果有valgrind)
find_program(VALGRIND_EXECUTABLE valgrind)
if(VALGRIND_EXECUTABLE)
    add_test(NAME memory_leak_test 
        COMMAND ${VALGRIND_EXECUTABLE} --error-exitcode=1 --leak-check=full ./test_todoapp)
    set_tests_properties(memory_leak_test PROPERTIES TIMEOUT 60)
endif()

# 安装目标
install(TARGETS todoapp DESTINATION bin)

# CPack配置
set(CPACK_PACKAGE_NAME "TodoApp")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION "现代C++待办事项管理器")
set(CPACK_PACKAGE_CONTACT "myhao690 <17713051689@163.com>")
include(CPack)

message(STATUS "TodoApp 项目配置完成！")
