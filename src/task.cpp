#include "todoapp/task.h"
#include <iostream>

Task::Task(std::string title) 
    : title_(std::move(title))
    , done_(false) {
}

std::string Task::getTitle() const {
    return title_;
}

bool Task::isDone() const {
    return done_;
}

void Task::markDone() {
    done_ = true;
}

void Task::print() const {
    std::cout << (done_ ? "[✓] " : "[ ] ") << title_ << "\n";
}
