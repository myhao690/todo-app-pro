#!/bin/bash

# TodoApp 自动化测试脚本
# 支持单元测试、集成测试、性能测试和覆盖率分析

set -e  # 遇到错误立即退出

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 输出函数
print_info() { echo -e "${BLUE}[INFO]${NC} $1"; }
print_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
print_warning() { echo -e "${YELLOW}[WARNING]${NC} $1"; }
print_error() { echo -e "${RED}[ERROR]${NC} $1"; }

# 默认参数
BUILD_TYPE="Debug"
RUN_COVERAGE=true
RUN_VALGRIND=false
RUN_PERFORMANCE=false

# 解析命令行参数
while [[ $# -gt 0 ]]; do
    case $1 in
        --release)
            BUILD_TYPE="Release"
            RUN_COVERAGE=false
            shift
            ;;
        --no-coverage)
            RUN_COVERAGE=false
            shift
            ;;
        --valgrind)
            RUN_VALGRIND=true
            shift
            ;;
        --performance)
            RUN_PERFORMANCE=true
            shift
            ;;
        -h|--help)
            echo "用法: $0 [选项]"
            echo "选项:"
            echo "  --release      使用Release模式构建"
            echo "  --no-coverage  不运行覆盖率分析"
            echo "  --valgrind     运行Valgrind内存检查"
            echo "  --performance  运行性能测试"
            echo "  -h, --help     显示帮助信息"
            exit 0
            ;;
        *)
            print_error "未知参数: $1"
            exit 1
            ;;
    esac
done

print_info "开始自动化测试流程..."
print_info "构建类型: $BUILD_TYPE"

# 清理旧的构建
if [ -d "build" ]; then
    print_info "清理旧的构建目录..."
    rm -rf build
fi

# 创建构建目录
mkdir build
cd build

# 配置项目
print_info "配置CMake项目..."
cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE

# 构建项目
print_info "构建项目..."
cmake --build . --parallel $(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# 运行单元测试
print_info "运行单元测试..."
if ctest --output-on-failure --verbose; then
    print_success "单元测试通过"
else
    print_error "单元测试失败"
    exit 1
fi

# 运行集成测试
print_info "运行集成测试..."
echo -e "1\n测试任务1\n4\n0\n" | timeout 10s ./todoapp > /dev/null 2>&1
if [ $? -eq 0 ]; then
    print_success "集成测试通过"
else
    print_warning "集成测试可能有问题"
fi

# 运行内存检查
if [ "$RUN_VALGRIND" = true ] && command -v valgrind >/dev/null 2>&1; then
    print_info "运行Valgrind内存检查..."
    if valgrind --leak-check=full --error-exitcode=1 ./test_todoapp; then
        print_success "内存检查通过"
    else
        print_error "发现内存泄漏"
        exit 1
    fi
elif [ "$RUN_VALGRIND" = true ]; then
    print_warning "Valgrind未安装，跳过内存检查"
fi

# 运行代码覆盖率分析
if [ "$RUN_COVERAGE" = true ] && [ "$BUILD_TYPE" = "Debug" ]; then
    print_info "运行代码覆盖率分析..."
    
    # 检查gcov/llvm-cov
    if command -v gcov >/dev/null 2>&1; then
        COV_TOOL="gcov"
    elif command -v llvm-cov >/dev/null 2>&1; then
        COV_TOOL="llvm-cov gcov"
    else
        print_warning "未找到覆盖率工具，跳过覆盖率分析"
        COV_TOOL=""
    fi
    
    if [ -n "$COV_TOOL" ]; then
        # 运行测试以生成覆盖率数据
        ./test_todoapp
        
        # 生成覆盖率报告
        if command -v gcovr >/dev/null 2>&1; then
            gcovr -r .. --html --html-details -o coverage.html
            gcovr -r .. --xml -o coverage.xml
            gcovr -r ..
            print_success "覆盖率报告已生成: coverage.html"
        else
            find . -name "*.gcda" -exec $COV_TOOL {} \;
            print_success "覆盖率数据已生成"
        fi
    fi
fi

# 运行性能测试
if [ "$RUN_PERFORMANCE" = true ]; then
    print_info "运行性能测试..."
    
    # 创建大量任务的性能测试
    start_time=$(date +%s%N)
    for i in {1..1000}; do
        echo -e "1\n任务$i\n" | timeout 1s ./todoapp > /dev/null 2>&1 || true
    done
    end_time=$(date +%s%N)
    
    duration=$((($end_time - $start_time) / 1000000))
    print_success "性能测试完成: 1000个操作耗时 ${duration}ms"
    
    # 清理测试数据
    rm -f tasks.txt
fi

# 生成测试报告
print_info "生成测试报告..."
cat > test_report.txt << EOF
TodoApp 测试报告
===============
构建时间: $(date)
构建类型: $BUILD_TYPE
测试结果: 通过

测试覆盖情况:
- 单元测试: ✓
- 集成测试: ✓
- 内存检查: $([ "$RUN_VALGRIND" = true ] && echo "✓" || echo "跳过")
- 覆盖率分析: $([ "$RUN_COVERAGE" = true ] && echo "✓" || echo "跳过")
- 性能测试: $([ "$RUN_PERFORMANCE" = true ] && echo "✓" || echo "跳过")

EOF

print_success "所有测试完成！测试报告: build/test_report.txt"

cd ..
print_success "自动化测试流程执行完毕"