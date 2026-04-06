#!/bin/bash

echo "========================================"
echo "德州扑克 - Spring Boot版本"
echo "========================================"
echo ""

# 检查Java环境
echo "检查Java环境..."
if ! command -v java &> /dev/null; then
    echo "❌ 错误：未找到Java环境，请先安装JDK 17+"
    exit 1
fi

# 检查Maven环境
echo "检查Maven环境..."
if ! command -v mvn &> /dev/null; then
    echo "❌ 错误：未找到Maven环境，请先安装Maven 3.6+"
    exit 1
fi

echo "✅ 环境检查通过！"
echo ""

# 检查是否已编译
if [ ! -f "target/texas-poker-backend-1.0.0.jar" ]; then
    echo "未找到编译后的jar包，开始编译..."
    mvn clean compile
    if [ $? -ne 0 ]; then
        echo "❌ 编译失败"
        exit 1
    fi
    echo "✅ 编译完成！"
    echo ""
fi

# 启动应用
echo "========================================"
echo "启动Spring Boot应用..."
echo "========================================"
echo ""
echo "应用将运行在: http://localhost:8080"
echo "API文档: http://localhost:8080/api/info"
echo ""
echo "按 Ctrl+C 停止服务"
echo ""

java -jar target/texas-poker-backend-1.0.0.jar

if [ $? -ne 0 ]; then
    echo "❌ 启动失败，尝试使用Maven运行..."
    mvn spring-boot:run
fi
