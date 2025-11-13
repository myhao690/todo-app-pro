#include "todoapp/task.h"
#include <iostream>

int main() {
    std::cout << "🎯 欢迎使用待办事项管理器！\n\n";
    
    // 创建几个示例任务
    Task task1("学习 C++");
    Task task2("完成项目");
    Task task3("写测试代码");
    
    std::cout << "📋 当前任务列表：\n";
    task1.print();
    task2.print();
    task3.print();
    
    std::cout << "\n正在完成第一个任务...\n";
    task1.markDone();
    
    std::cout << "\n📋 更新后的任务列表：\n";
    task1.print();
    task2.print();
    task3.print();
    
    std::cout << "\n✅ 程序运行成功！\n";
    return 0;
}
