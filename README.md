# TexasPoker

B/S架构的德州扑克

## 🎯 版本选择

我们提供**两种后端实现**，可根据需求选择：

### Python版本（Flask）- `texas_holdem_backend.py`
- ✅ 代码简洁，快速开发
- ✅ 适合原型验证和AI集成
- ✅ 轻量级，易于修改

### Java版本（Spring Boot）
- ✅ 企业级架构，性能优秀
- ✅ 强类型系统，可维护性强
- ✅ 完善的生态和工具链
- ✅ 适合生产环境

**详细对比请查看 [VERSION_COMPARISON.md](VERSION_COMPARISON.md)**

---

## 📁 项目结构

### 前端（通用）
基于 Vue 3 + Vite 的现代前端应用，位于 `frontend/` 目录。

**注意**：传统H5版本已于2026年4月6日移除。

### 后端（双版本）
- **Python版本**：`texas_holdem_backend.py`（Flask）
- **Java版本**：`src/main/java/com/texaspoker/`（Spring Boot）

### 核心特性
- 完整的德州扑克游戏流程
- 机器人AI对手
- 手牌牌型判断（皇家同花顺~高牌）
- 胜负判定和筹码分配
- RESTful API设计

---

## 🚀 快速开始

### 选择Python版本

```bash
# 启动后端
python texas_holdem_backend.py

# 启动前端
cd frontend
npm install
npm run dev

# 访问 http://localhost:3000
```

**或一键启动**：双击 `start_game.bat` 或运行 `./start_game.sh`

### 选择Java版本

```bash
# 编译和启动
mvn spring-boot:run

# 启动前端
cd frontend
npm install
npm run dev

# 访问 http://localhost:3000
```

**或一键启动**：双击 `start_spring.bat` 或运行 `./start_spring.sh`

---

## 📊 版本对比

| 特性 | Python版本 | Java版本 |
|------|-----------|----------|
| **代码量** | 31.9KB | ~50KB |
| **启动速度** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ |
| **运行性能** | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ |
| **并发处理** | ⭐⭐ | ⭐⭐⭐⭐⭐ |
| **类型安全** | 动态类型 | 强类型 |
| **企业特性** | 需额外配置 | 内置支持 |
| **开发效率** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ |
| **可维护性** | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ |

**详细对比：[VERSION_COMPARISON.md](VERSION_COMPARISON.md)**

---

## 📚 文档清单

- [SPRING_BOOT_README.md](SPRING_BOOT_README.md) - Java版本使用说明
- [VERSION_COMPARISON.md](VERSION_COMPARISON.md) - 版本对比与选择指南
- [MIGRATION_GUIDE.md](MIGRATION_GUIDE.md) - Vue迁移指南
- [VUE_MIGRATION_SUMMARY.md](VUE_MIGRATION_SUMMARY.md) - Vue迁移总结
- [SPRING_BOOT_SUMMARY.md](SPRING_BOOT_SUMMARY.md) - Spring Boot完成总结

---

## 🛠️ 环境要求

### 通用
- **前端**：Node.js 16+，npm 7+

### Python版本
- Python 3.8+
- pip

### Java版本
- JDK 17+
- Maven 3.6+

---

## 🎮 游戏说明

### 座位布局
- **下方（座位0）**：人类玩家（你）
- **左侧（座位1）**：机器人1
- **右侧（座位2）**：机器人2（庄家）

### 操作按钮
- 弃牌 / 过牌 / 跟注 / 下注 / 加注

### 游戏规则
- 起始筹码：1000
- 小盲注：10，大盲注：20
- 标准德州扑克规则

---

## 📜 版本历史

### 2026.04.07
- ✅ 添加Spring Boot版本后端
- ✅ 双后端支持（Python/Java）

### 2026.04.06
- ✅ 移除H5版本，全面迁移到Vue 3
- ✅ 添加自动化启动脚本

### 2026.02.12
- ✅ 删除Qt版代码，基于Python+H5开发

### 2024.08.20
- ✅ 添加牌型检测和对比功能

---

## 🎯 TODO

- [ ] 添加单元测试（JUnit/pytest）
- [ ] 集成Swagger/OpenAPI文档
- [ ] WebSocket实时通信
- [ ] 多房间支持
- [ ] 用户认证系统
- [ ] 数据库集成
- [ ] Docker容器化

---

## 💡 选择建议

### 个人项目/快速开发 → **Python版本**
```bash
python texas_holdem_backend.py
```

### 企业应用/生产环境 → **Java版本**
```bash
mvn spring-boot:run
```

### 教学/学习 → **都可以**
- Python：入门简单，代码清晰
- Java：企业标准，生态完善

---

## 🎉 项目特色

1. **双后端支持**：Python + Java，满足不同需求
2. **现代前端**：Vue 3 + Vite，响应式设计
3. **完整功能**：从发牌到胜负判定，全流程覆盖
4. **AI对手**：智能机器人，自动决策
5. **文档完善**：详细的使用说明和对比指南
6. **易于扩展**：模块化设计，方便添加新功能

---

**项目完成度：⭐⭐⭐⭐⭐**  
**最后更新：2026年4月7日**  
**维护者：JackeyLea**
