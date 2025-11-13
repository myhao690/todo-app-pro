#include "todoapp/task.h"
#include "todoapp/todo_manager.h"
#include <iostream>
#include <cassert>
#include <fstream>

void testTask() {
    std::cout << "🧪 测试 Task 类...\n";
    
    // 测试任务创建
    Task task("测试任务");
    assert(task.getTitle() == "测试任务");
    assert(!task.isDone());
    
    // 测试标记完成
    task.markDone();
    assert(task.isDone());
    
    std::cout << "✅ Task 类测试通过\n";
}

void testTodoManager() {
    std::cout << "🧪 测试 TodoManager 类...\n";
    
    // 清理可能存在的测试数据文件
    std::remove("tasks.txt");
    
    TodoManager manager;
    
    // 确保开始时任务数为0
    assert(manager.getTaskCount() == 0);
    
    // 测试添加任务
    manager.addTask("测试任务1");
    manager.addTask("测试任务2");
    assert(manager.getTaskCount() == 2);
    
    // 测试标记完成
    assert(manager.markTaskDone(0));
    
    // 测试删除任务
    assert(manager.removeTask(1));
    assert(manager.getTaskCount() == 1);
    
    // 测试无效索引
    assert(!manager.markTaskDone(10));
    assert(!manager.removeTask(10));
    
    // 测试清空
    manager.clear();
    assert(manager.getTaskCount() == 0);
    
    // 清理测试文件
    std::remove("tasks.txt");
    
    std::cout << "✅ TodoManager 类测试通过\n";
}

int main() {
    std::cout << "🚀 开始运行单元测试...\n\n";
    
    try {
        testTask();
        testTodoManager();
        
        std::cout << "\n🎉 所有测试通过！\n";
        return 0;
    } catch (const std::exception& e) {
        std::cout << "❌ 测试失败: " << e.what() << "\n";
        return 1;
    }
}