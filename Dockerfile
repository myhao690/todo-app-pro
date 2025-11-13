# 多阶段构建：构建阶段
FROM ubuntu:22.04 AS builder

# 设置工作目录
WORKDIR /app

# 安装构建依赖
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

# 复制源代码
COPY CMakeLists.txt ./
COPY src/ ./src/
COPY include/ ./include/
COPY tests/ ./tests/

# 构建项目
RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build

# 运行测试
RUN cd build && ctest --output-on-failure

# 多阶段构建：运行阶段
FROM ubuntu:22.04

# 创建非root用户
RUN useradd -m -s /bin/bash todouser

# 设置工作目录
WORKDIR /home/todouser

# 从构建阶段复制可执行文件
COPY --from=builder /app/build/todoapp /usr/local/bin/todoapp

# 切换到非root用户
USER todouser

# 暴露数据卷用于持久化任务数据
VOLUME ["/home/todouser/data"]

# 设置环境变量
ENV TODOAPP_DATA_DIR=/home/todouser/data

# 健康检查
HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
    CMD echo "0" | todoapp > /dev/null || exit 1

# 默认命令
CMD ["todoapp"]