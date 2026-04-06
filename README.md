# TexasPoker

B/S架构的德州扑克

## 结构

### 前端

#### 传统H5版本（原版）
一个独立的 HTML 页面（`index.html`），包含游戏界面，并通过 Fetch API 与后端通信。

#### Vue版本（推荐）
基于 Vue 3 + Vite 的现代前端应用，位于 `frontend/` 目录下，提供更好的开发体验和性能。

### 后端

一个基于 Flask 的 Python 服务器（`texas_holdem_backend.py`），负责管理游戏状态、逻辑判断，并提供 RESTful API。

实现了扑克牌、玩家、游戏状态等完整的数据模型。包含了发牌、下注轮次管理、玩家动作处理、游戏阶段推进、扑克手牌排名算法、牌力比较和胜者判定逻辑等核心逻辑。

## 环境

- Python 3.8+
- Node.js 16+ (Vue版本)
- Windows/Linux/macOS

## 运行

### H5版本
```bash
# 后端
python texas_holdem_backend.py

# 前端：双击打开 index.html
```

### Vue版本（推荐）
```bash
# 1. 启动后端
python texas_holdem_backend.py

# 2. 在另一个终端，启动前端
cd frontend
npm install
npm run dev

# 访问 http://127.0.0.1:3000
```

## Vue版本特性

- ✅ 完整的德州扑克游戏流程
- ✅ 组件化架构，代码更清晰
- ✅ 响应式数据绑定，自动更新UI
- ✅ 更好的开发体验（热重载、调试工具）
- ✅ 现代化构建工具（Vite）
- ✅ 与原版功能完全兼容

## TODO

- 身份验证：当前后端默认是当前行动玩家在操作。实际应用中需要为每个连接分配会话或玩家ID。
- 多房间/游戏实例：当前后端只有一个全局游戏实例。可以扩展为支持多个并发的牌桌。
- 更多功能：如玩家加入/退出、观战、聊天、下注历史、筹码动画等。
- PWA支持：将Vue版本升级为渐进式Web应用