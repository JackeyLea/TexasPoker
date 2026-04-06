@echo off
chcp 65001 >nul
echo ========================================
echo 德州扑克游戏启动器
echo ========================================
echo.

REM 检查Python环境
echo 检查Python环境...
python --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ❌ 错误：未找到Python环境，请先安装Python 3.8+
    pause
    exit /b 1
)

REM 检查Node.js环境
echo 检查Node.js环境...
node --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ❌ 错误：未找到Node.js环境，请先安装Node.js 16+
    pause
    exit /b 1
)

echo ✅ 环境检查通过！
echo.

REM 安装前端依赖
echo 安装前端依赖...
cd frontend
if not exist "node_modules" (
    call npm install
    if %errorlevel% neq 0 (
        echo ❌ 错误：npm install 失败
        pause
        exit /b 1
    )
    echo ✅ 前端依赖安装完成！
) else (
    echo ✅ 前端依赖已安装，跳过...
)
cd ..

echo.
echo ========================================
echo 启动后端服务...
echo ========================================
start "德州扑克-后端" python texas_holdem_backend.py
timeout /t 3 /nobreak >nul

echo.
echo ========================================
echo 启动前端服务...
echo ========================================
cd frontend
start "德州扑克-前端" npm run dev
cd ..

timeout /t 5 /nobreak >nul

echo.
echo ========================================
echo 🎉 游戏启动成功！
echo ========================================
echo.
echo 前端地址: http://127.0.0.1:3000
echo 后端地址: http://127.0.0.1:5000
echo.
echo 提示：
echo - 如果前端页面无法访问，请等待几秒钟后刷新
echo - 关闭本窗口可停止所有服务
echo.
echo 按任意键退出启动器（服务将继续运行）...
pause >nul
