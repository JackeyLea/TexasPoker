# 德州扑克 - Spring Boot版本

基于Spring Boot 3.2.0重写的德州扑克游戏后端。

## 技术栈

- **框架**：Spring Boot 3.2.0
- **语言**：Java 17
- **构建工具**：Maven
- **日志**：SLF4J + Logback

## 项目结构

```
src/main/java/com/texaspoker/
├── TexasPokerApplication.java      # 应用入口
├── model/                          # 数据模型
│   ├── Suit.java                   # 花色
│   ├── Rank.java                   # 点数
│   ├── Card.java                   # 扑克牌
│   ├── HandRank.java               # 牌型等级
│   ├── HandEvaluation.java         # 手牌评估
│   ├── PlayerStatus.java           # 玩家状态
│   ├── Player.java                 # 玩家
│   └── GameState.java              # 游戏状态
├── service/                        # 业务逻辑
│   └── PokerGameService.java       # 游戏服务
└── controller/                     # API控制器
    └── GameController.java         # 游戏API

src/main/resources/
└── application.properties          # 配置文件
```

## API接口

### 获取应用信息
```
GET /api/info
```

### 获取游戏状态
```
GET /api/game/state?player_id=0
```

### 开始新游戏
```
POST /api/game/start
```

### 玩家动作
```
POST /api/game/action
Content-Type: application/json

{
  "action": "bet",
  "amount": 50
}
```

### 机器人动作
```
POST /api/game/robot_action
Content-Type: application/json

{
  "player_id": 1
}
```

### 重置游戏
```
POST /api/reset
```

### 健康检查
```
GET /api/health
```

## 运行方式

### 1. 编译和运行

```bash
# 编译
mvn clean compile

# 打包
mvn clean package

# 运行
java -jar target/texas-poker-backend-1.0.0.jar

# 或使用Maven运行
mvn spring-boot:run
```

### 2. 使用启动脚本

```bash
# Windows
start_spring.bat

# Linux/Mac
./start_spring.sh
```

应用将运行在 http://localhost:8080

## 与Python版本的区别

### 1. 类型安全
- Java强类型系统，编译时检查
- 使用枚举代替字符串常量
- Lombok自动生成getter/setter

### 2. 性能优化
- 使用Stream API进行集合操作
- 优化的牌型判断算法
- 更高效的内存管理

### 3. 架构改进
- 清晰的MVC分层
- 依赖注入（DI）
- AOP日志记录

### 4. API改进
- 统一的响应格式
- 更好的错误处理
- RESTful设计

### 5. 配置管理
- 集中式配置（application.properties）
- 环境区分（dev/prod）
- 日志管理

## 配置说明

在 `src/main/resources/application.properties` 中可配置：

```properties
# 服务器端口
server.port=8080

# 日志级别
logging.level.com.texaspoker=INFO

# 应用信息
app.name=德州扑克游戏服务器
```

## 开发建议

### 1. 添加新功能
- Model: 定义数据模型
- Service: 实现业务逻辑
- Controller: 提供API接口

### 2. 测试
```bash
# 运行测试
mvn test
```

### 3. 调试
- 使用Spring Boot DevTools（可选）
- IDE断点调试
- 日志输出

## 与前端集成

### Vue前端配置
修改 `frontend/vite.config.js`：

```javascript
proxy: {
  '/api': {
    target: 'http://127.0.0.1:8080',  // Spring Boot端口
    changeOrigin: true
  }
}
```

### 启动顺序
1. 启动Spring Boot后端（端口8080）
2. 启动Vue前端（端口3000）
3. 访问 http://localhost:3000

## 版本信息

- **Java**: 17
- **Spring Boot**: 3.2.0
- **Maven**: 3.6+

## TODO

- [ ] 添加单元测试
- [ ] 集成Swagger/OpenAPI文档
- [ ] 添加WebSocket支持
- [ ] 实现多房间功能
- [ ] 添加用户认证
- [ ] 集成数据库

## 许可证

与主项目保持一致
