@echo off
echo 测试Spring Boot API...
echo =======================
echo.

timeout /t 15 /nobreak >nul

echo 1. 测试应用信息API...
curl -s http://localhost:8081/api/info
echo.
echo.

echo 2. 测试游戏状态API...
curl -s "http://localhost:8081/api/game/state?player_id=0"
echo.
echo.

echo 3. 测试开始游戏API...
curl -s -X POST http://localhost:8081/api/game/start
echo.
echo.

echo API测试完成！
echo.
echo 如果以上测试正常输出JSON数据，说明Spring Boot服务运行成功！
pause
