#include "todoapp/todo_manager.h"
#include <iostream>
#include <string>
#include <limits>

void showMenu()
{
    std::cout << "\n🎯 待办事项管理器\n";
    std::cout << "==================\n";
    std::cout << "1. 📝 添加任务\n";
    std::cout << "2. ✅ 完成任务\n";
    std::cout << "3. 🗑️  删除任务\n";
    std::cout << "4. 📋 查看所有任务\n";
    std::cout << "5. 🧹 清空所有任务\n";
    std::cout << "0. 👋 退出\n";
    std::cout << "==================\n";
    std::cout << "请选择操作 (0-5): ";
}

int getChoice()
{
    int choice;
    while (!(std::cin >> choice) || choice < 0 || choice > 5)
    {
        std::cout << "❌ 无效输入！请输入 0-5 之间的数字: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(); // 清除换行符
    return choice;
}

std::string getTaskTitle()
{
    std::cout << "请输入任务标题: ";
    std::string title;
    std::getline(std::cin, title);
    return title;
}

size_t getTaskIndex(const TodoManager &manager)
{
    if (manager.getTaskCount() == 0)
    {
        std::cout << "❌ 当前没有任务！\n";
        return SIZE_MAX;
    }

    std::cout << "请输入任务编号 (1-" << manager.getTaskCount() << "): ";
    size_t index;
    while (!(std::cin >> index) || index == 0 || index > manager.getTaskCount())
    {
        std::cout << "❌ 无效编号！请输入 1-" << manager.getTaskCount() << " 之间的数字: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(); // 清除换行符
    return index - 1;  // 转换为0基索引
}

int main()
{
    std::cout << "🎯 欢迎使用待办事项管理器！\n";

    TodoManager manager;

    // 如果有已保存的任务，显示欢迎信息
    if (manager.getTaskCount() > 0)
    {
        std::cout << "📂 已加载 " << manager.getTaskCount() << " 个已保存的任务\n";
    }

    int choice;
    do
    {
        showMenu();
        choice = getChoice();

        switch (choice)
        {
        case 1:
        { // 添加任务
            std::string title = getTaskTitle();
            manager.addTask(title);
            break;
        }

        case 2:
        { // 完成任务
            manager.printAllTasks();
            if (manager.getTaskCount() > 0)
            {
                size_t index = getTaskIndex(manager);
                if (index != SIZE_MAX)
                {
                    manager.markTaskDone(index);
                }
            }
            break;
        }

        case 3:
        { // 删除任务
            manager.printAllTasks();
            if (manager.getTaskCount() > 0)
            {
                size_t index = getTaskIndex(manager);
                if (index != SIZE_MAX)
                {
                    manager.removeTask(index);
                }
            }
            break;
        }

        case 4:
        { // 查看所有任务
            manager.printAllTasks();
            break;
        }

        case 5:
        { // 清空所有任务
            std::cout << "⚠️ 确定要清空所有任务吗？(y/N): ";
            std::string confirm;
            std::getline(std::cin, confirm);
            if (confirm == "y" || confirm == "Y" || confirm == "yes")
            {
                manager.clear();
            }
            else
            {
                std::cout << "❌ 操作已取消\n";
            }
            break;
        }

        case 0: // 退出
            std::cout << "👋 谢谢使用，再见！\n";
            break;
        }

        if (choice != 0)
        {
            std::cout << "\n按回车键继续...";
            std::cin.get();
        }

    } while (choice != 0);

    return 0;
}
