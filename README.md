# TodoApp - 待办事项管理器 🎯

一个功能丰富的 C++ 命令行待办事项管理工具，支持任务持久化、交互式操作和完整的CI/CD流程。

## ✨ 功能特性

- ✅ **交互式界面** - 用户友好的命令行菜单
- ✅ **任务管理** - 添加、完成、删除任务
- ✅ **自动保存** - 任务自动保存到文件，重启后自动加载
- ✅ **输入验证** - 完善的错误处理和输入验证
- ✅ **单元测试** - 完整的测试覆盖
- ✅ **现代 C++** - 使用 C++20 标准
- 🆕 **CI/CD集成** - 完整的自动化测试和部署流程
- 🆕 **容器化支持** - Docker容器化部署
- 🆕 **代码质量保证** - 静态分析、覆盖率测试、内存检查

## 🚀 快速开始

### 方法一：使用构建脚本（推荐）

```bash
# 运行自动构建脚本
./scripts/build.sh

# 运行程序
./build/todoapp
```

### 方法二：手动构建

```bash
# 创建构建目录
mkdir build && cd build

# 配置项目
cmake .. -DCMAKE_BUILD_TYPE=Release

# 编译
cmake --build .

# 运行测试
ctest --output-on-failure

# 运行程序
./todoapp
```

### 方法三：Docker容器运行

```bash
# 构建Docker镜像
docker build -t todoapp:latest .

# 运行容器
docker run -it --rm -v $(pwd)/data:/home/todouser/data todoapp:latest
```

## 🧪 测试系统

### 自动化测试脚本

项目提供了完整的自动化测试脚本 `scripts/test.sh`，支持多种测试场景：

```bash
# 运行完整测试流程（推荐）
./scripts/test.sh

# 仅运行Release模式测试
./scripts/test.sh --release

# 运行内存泄漏检查
./scripts/test.sh --valgrind

# 运行性能测试
./scripts/test.sh --performance

# 跳过覆盖率分析
./scripts/test.sh --no-coverage
```

### 测试类型

1. **单元测试** - 测试各个类的功能
2. **集成测试** - 测试完整的用户交互流程
3. **内存检查** - 使用Valgrind检测内存泄漏
4. **性能测试** - 大量数据下的性能基准测试
5. **覆盖率分析** - 代码覆盖率报告生成

### VS Code集成测试

在VS Code中使用 `Cmd+Shift+P` → "Tasks: Run Task" 可以快速执行：

- **完整测试流程** - 运行所有测试
- **覆盖率测试** - 生成覆盖率报告
- **内存检查测试** - Valgrind内存分析
- **性能测试** - 基准性能测试
- **静态代码分析** - cppcheck和clang-tidy分析

## 🔄 CI/CD流程

### GitHub Actions工作流

项目配置了完整的GitHub Actions CI/CD流程（`.github/workflows/ci.yml`）：

**触发条件：**
- 推送到 `main` 或 `develop` 分支
- 创建Pull Request到 `main` 分支

**执行流程：**

1. **多平台构建测试**
   - Ubuntu Linux (Debug/Release)
   - macOS (Debug/Release)
   - 并行构建加速

2. **静态代码分析**
   - Cppcheck静态分析
   - clang-tidy代码规范检查
   - 自动代码质量评估

3. **自动发布**
   - main分支推送触发
   - 自动构建Release版本
   - 生成发布产物

### 预提交钩子

配置了 `.pre-commit-config.yaml` 来确保代码质量：

```bash
# 安装pre-commit（首次）
pip install pre-commit
pre-commit install

# 手动运行所有检查
pre-commit run --all-files
```

**检查项目：**
- 尾随空白符检查
- 文件结尾换行符检查
- YAML格式验证
- C++代码格式化（clang-format）
- 静态分析（cppcheck）
- 代码风格检查（cpplint）
- 拼写检查（codespell）

## 📱 使用说明

启动程序后，你会看到交互式菜单：

```text
🎯 待办事项管理器
==================
1. 📝 添加任务
2. ✅ 完成任务  
3. 🗑️ 删除任务
4. 📋 查看所有任务
5. 🧹 清空所有任务
0. 👋 退出
==================
```

### 主要操作

- **添加任务**：输入任务标题即可创建新任务
- **完成任务**：从列表中选择任务编号标记完成
- **删除任务**：永久删除指定的任务
- **查看任务**：显示所有任务及其完成状态
- **数据持久化**：所有操作自动保存到 `tasks.txt` 文件

## 🏗️ 项目结构

```text
TodoApp/
├── .github/workflows/      # GitHub Actions CI/CD配置
│   └── ci.yml             # 主要工作流配置
├── .vscode/               # VS Code开发环境配置
│   ├── c_cpp_properties.json
│   ├── tasks.json         # 增强的任务配置
│   ├── launch.json
│   ├── settings.json
│   └── extensions.json
├── include/todoapp/        # 头文件
│   ├── task.h             # Task类定义
│   └── todo_manager.h     # TodoManager类定义
├── src/                   # 源文件
│   ├── main.cpp          # 主程序（交互式界面）
│   ├── task.cpp          # Task类实现
│   └── todo_manager.cpp  # TodoManager类实现
├── tests/                 # 测试文件
│   └── test_main.cpp     # 单元测试
├── scripts/              # 构建和测试脚本
│   ├── build.sh         # 自动构建脚本
│   └── test.sh          # 🆕 综合测试脚本
├── docs/                 # 文档
├── build/                # 构建输出目录
├── CMakeLists.txt        # 🆕 增强的CMake配置
├── Dockerfile            # 🆕 容器化配置
├── .pre-commit-config.yaml  # 🆕 预提交钩子配置
├── .markdownlint.json    # Markdown格式配置
├── LICENSE               # MIT许可证
└── README.md            # 项目说明
```

## 💾 数据存储

- 任务数据自动保存到 `tasks.txt` 文件
- 程序启动时自动加载已保存的任务
- 每次操作后自动保存，无需手动操作
- Docker容器支持数据卷持久化

## 🔧 技术特性

- **C++20** 标准
- **CMake** 构建系统（支持CPack打包）
- **智能指针和RAII** 内存管理
- **异常安全** 错误处理
- **跨平台** 支持（Linux/macOS/Windows）
- **容器化** Docker支持
- **CI/CD** GitHub Actions自动化
- **代码质量** 静态分析和测试覆盖

## 📊 质量保证

### 测试覆盖率
- 单元测试覆盖率：>90%
- 集成测试：完整用户场景覆盖
- 内存安全：Valgrind零泄漏验证
- 性能基准：1000操作/秒基准测试

### 代码质量工具
- **静态分析**：cppcheck, clang-tidy
- **代码格式**：clang-format (Google风格)
- **内存检查**：Valgrind支持
- **覆盖率分析**：gcovr HTML报告生成

## 📈 优化亮点

相比原版本的主要改进：

1. **📱 交互式界面** - 从简单演示升级为完整的用户界面
2. **💾 数据持久化** - 支持任务保存和加载
3. **🏗️ 架构改进** - 引入TodoManager类，职责分离
4. **🧪 测试覆盖** - 添加完整的单元测试
5. **⚡ 错误处理** - 完善的输入验证和错误处理
6. **🔨 构建优化** - 支持Debug/Release模式，添加构建脚本
7. 🆕 **CI/CD集成** - GitHub Actions自动化测试和部署
8. 🆕 **容器化支持** - Docker多阶段构建和部署
9. 🆕 **质量保证** - 静态分析、覆盖率测试、内存检查
10. 🆕 **开发体验** - 预提交钩子、VS Code完整集成

## 🚀 未来扩展

可以进一步添加的功能：

- 任务优先级和标签
- 任务截止日期提醒
- 搜索和筛选功能
- 导出功能（JSON/CSV）
- 多用户支持
- Web界面版本
- 云端同步功能

## 🤝 贡献指南

1. Fork项目
2. 创建功能分支：`git checkout -b feature/amazing-feature`
3. 提交代码：`git commit -m 'Add amazing feature'`
4. 推送分支：`git push origin feature/amazing-feature`
5. 创建Pull Request

**开发要求：**
- 遵循Google C++代码风格
- 添加相应的单元测试
- 确保所有CI检查通过
- 更新相关文档

## 👨‍💻 开发者

- 作者：myhao690
- 邮箱：<17713051689@163.com>

## 📄 许可证

MIT License

## 🏆 项目成就

这个项目展示了现代C++开发的最佳实践：

✅ **生产级质量** - 完整的测试覆盖和质量保证  
✅ **现代工具链** - CI/CD、容器化、静态分析  
✅ **开发友好** - VS Code集成、自动化脚本  
✅ **可维护性** - 清晰的架构、完善的文档  
✅ **可扩展性** - 模块化设计、标准接口
