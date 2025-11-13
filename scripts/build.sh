#!/bin/bash

# TodoApp 构建脚本
echo "🔨 开始构建 TodoApp..."

# 创建构建目录
if [ ! -d "build" ]; then
    mkdir build
fi

cd build

# 配置项目
echo "⚙️ 配置项目..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# 编译
echo "🔧 编译项目..."
cmake --build .

# 运行测试
echo "🧪 运行测试..."
ctest --output-on-failure

echo "✅ 构建完成！"
echo ""
echo "运行方式："
echo "  ./build/todoapp        # 运行主程序"
echo "  ./build/test_todoapp   # 运行测试"
echo "  ctest                  # 在build目录中运行测试"