#include "todoapp/todo_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>

const std::string TodoManager::DEFAULT_FILENAME = "tasks.txt";

TodoManager::TodoManager() {
    // 尝试从默认文件加载任务
    loadFromFile(DEFAULT_FILENAME);
}

void TodoManager::addTask(const std::string& title) {
    if (title.empty()) {
        std::cout << "❌ 任务标题不能为空！\n";
        return;
    }
    
    tasks_.emplace_back(title);
    std::cout << "✅ 任务已添加：" << title << "\n";
    saveToFile(DEFAULT_FILENAME); // 自动保存
}

bool TodoManager::markTaskDone(size_t index) {
    if (index >= tasks_.size()) {
        std::cout << "❌ 无效的任务编号！\n";
        return false;
    }
    
    tasks_[index].markDone();
    std::cout << "✅ 任务已完成：" << tasks_[index].getTitle() << "\n";
    saveToFile(DEFAULT_FILENAME); // 自动保存
    return true;
}

bool TodoManager::removeTask(size_t index) {
    if (index >= tasks_.size()) {
        std::cout << "❌ 无效的任务编号！\n";
        return false;
    }
    
    std::string title = tasks_[index].getTitle();
    tasks_.erase(tasks_.begin() + index);
    std::cout << "🗑️ 任务已删除：" << title << "\n";
    saveToFile(DEFAULT_FILENAME); // 自动保存
    return true;
}

void TodoManager::printAllTasks() const {
    if (tasks_.empty()) {
        std::cout << "📝 暂无任务\n";
        return;
    }
    
    std::cout << "📋 任务列表：\n";
    for (size_t i = 0; i < tasks_.size(); ++i) {
        std::cout << (i + 1) << ". ";
        tasks_[i].print();
    }
}

size_t TodoManager::getTaskCount() const {
    return tasks_.size();
}

bool TodoManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    for (const auto& task : tasks_) {
        file << (task.isDone() ? "1" : "0") << "|" << task.getTitle() << "\n";
    }
    
    return true;
}

bool TodoManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false; // 文件不存在是正常情况
    }
    
    tasks_.clear();
    std::string line;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        size_t pos = line.find('|');
        if (pos == std::string::npos) continue;
        
        bool isDone = (line[0] == '1');
        std::string title = line.substr(pos + 1);
        
        Task task(title);
        if (isDone) {
            task.markDone();
        }
        tasks_.push_back(task);
    }
    
    return true;
}

void TodoManager::clear() {
    tasks_.clear();
    std::cout << "🧹 所有任务已清空\n";
    saveToFile(DEFAULT_FILENAME); // 自动保存
}