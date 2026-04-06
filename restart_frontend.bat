@echo off
echo ========================================
echo 重启Vue前端服务
echo ========================================
echo.

cd /d "d:\JackeyLea\TexasPoker\frontend"

echo 正在启动Vue开发服务器...
echo 端口: 3000 (前端)
echo API代理: 8081 (Spring Boot后端)
echo.

npm run dev

if %errorlevel% neq 0 (
    echo ❌ 启动失败
    pause
    exit /b 1
)
