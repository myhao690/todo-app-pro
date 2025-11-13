#pragma once
#include <string>

/**
 * @brief 待办任务类
 * 表示一个待办事项，包含标题和完成状态
 */
class Task {
public:
    // 构造函数
    explicit Task(std::string title);
    
    // 获取任务标题
    std::string getTitle() const;
    
    // 检查是否完成
    bool isDone() const;
    
    // 标记为完成
    void markDone();
    
    // 打印任务信息
    void print() const;

private:
    std::string title_;
    bool done_;
};
