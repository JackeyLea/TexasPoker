#!/bin/bash

echo "========================================"
echo "德州扑克游戏启动器"
echo "========================================"
echo ""

# 检查Python环境
echo "检查Python环境..."
if ! command -v python3 &> /dev/null && ! command -v python &> /dev/null; then
    echo "❌ 错误：未找到Python环境，请先安装Python 3.8+"
    exit 1
fi

# 检查Node.js环境
echo "检查Node.js环境..."
if ! command -v node &> /dev/null; then
    echo "❌ 错误：未找到Node.js环境，请先安装Node.js 16+"
    exit 1
fi

echo "✅ 环境检查通过！"
echo ""

# 确定Python命令
PYTHON_CMD="python3"
if ! command -v python3 &> /dev/null; then
    PYTHON_CMD="python"
fi

# 安装前端依赖
echo "安装前端依赖..."
cd frontend
if [ ! -d "node_modules" ]; then
    npm install
    if [ $? -ne 0 ]; then
        echo "❌ 错误：npm install 失败"
        exit 1
    fi
    echo "✅ 前端依赖安装完成！"
else
    echo "✅ 前端依赖已安装，跳过..."
fi
cd ..

echo ""
echo "========================================"
echo "启动后端服务..."
echo "========================================"
$PYTHON_CMD texas_holdem_backend.py &
BACKEND_PID=$!
sleep 3

echo ""
echo "========================================"
echo "启动前端服务..."
echo "========================================"
cd frontend
npm run dev &
FRONTEND_PID=$!
cd ..

sleep 5

echo ""
echo "========================================"
echo "🎉 游戏启动成功！"
echo "========================================"
echo ""
echo "前端地址: http://127.0.0.1:3000"
echo "后端地址: http://127.0.0.1:5000"
echo ""
echo "提示："
echo "- 如果前端页面无法访问，请等待几秒钟后刷新"
echo "- 按 Ctrl+C 可停止所有服务"
echo ""

# 等待用户中断
trap "kill $BACKEND_PID $FRONTEND_PID 2>/dev/null; exit" INT
wait
