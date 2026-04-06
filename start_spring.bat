@echo off
echo ========================================
echo 德州扑克 - Spring Boot版本
echo ========================================
echo.

REM 检查Java环境
echo 检查Java环境...
java -version >nul 2>&1
if %errorlevel% neq 0 (
    echo ❌ 错误：未找到Java环境，请先安装JDK 17+
    pause
    exit /b 1
)

REM 检查Maven环境
echo 检查Maven环境...
mvn -version >nul 2>&1
if %errorlevel% neq 0 (
    echo ❌ 错误：未找到Maven环境，请先安装Maven 3.6+
    pause
    exit /b 1
)

echo ✅ 环境检查通过！
echo.

REM 检查是否已编译
if not exist "target\texas-poker-backend-1.0.0.jar" (
    echo 未找到编译后的jar包，开始编译...
    call mvn clean compile
    if %errorlevel% neq 0 (
        echo ❌ 编译失败
        pause
        exit /b 1
    )
    echo ✅ 编译完成！
    echo.
)

REM 启动应用
echo ========================================
echo 启动Spring Boot应用...
echo ========================================
echo.
echo 应用将运行在: http://localhost:8080
echo API文档: http://localhost:8080/api/info
echo.
echo 按 Ctrl+C 停止服务
echo.

java -jar target\texas-poker-backend-1.0.0.jar

if %errorlevel% neq 0 (
    echo ❌ 启动失败，尝试使用Maven运行...
    mvn spring-boot:run
)

pause
