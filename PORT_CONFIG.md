# 端口配置说明

## 当前端口配置（Spring Boot版本）

### 后端服务
- **端口**: 8081
- **用途**: Spring Boot应用
- **API地址**: http://localhost:8081/api

### 前端服务
- **端口**: 3000
- **用途**: Vue开发服务器
- **访问地址**: http://localhost:3000

### 端口映射关系
```
前端(3000) → 代理 → 后端(8081)
浏览器 → http://localhost:3000 → Vue应用 → API请求 → http://localhost:8081/api
```

## 配置文件位置

### 后端端口配置
文件: `src/main/resources/application.properties`
```properties
server.port=8081
```

### 前端代理配置
文件: `frontend/vite.config.js`
```javascript
proxy: {
  '/api': {
    target: 'http://127.0.0.1:8081',  // 后端端口
    changeOrigin: true
  }
}
```

## 端口变更历史

### 2026.04.07
- **后端**: 8080 → 8081（避免端口冲突）
- **前端**: 保持3000不变
- **原因**: 8080端口被其他应用占用

### 2026.04.06
- **后端**: Python版本使用5000
- **前端**: 保持3000不变
- **原因**: Flask默认端口

## 如何检查端口占用

### Windows
```bash
# 查看端口占用
netstat -ano | findstr :8081

# 查看进程详情
tasklist | findstr <PID>

# 终止进程
taskkill /PID <PID> /F
```

### Linux/Mac
```bash
# 查看端口占用
lsof -i :8081

# 终止进程
kill -9 <PID>
```

## 常见问题解决

### 问题1: ECONNREFUSED 127.0.0.1:5000
**原因**: 前端配置仍指向Python后端（5000端口）

**解决**:
1. 更新 `frontend/vite.config.js`
2. 将 `target: 'http://127.0.0.1:5000'` 改为 `target: 'http://127.0.0.1:8081'`
3. 重启前端服务: `npm run dev`

### 问题2: Port 8081 was already in use
**原因**: 8081端口被其他应用占用

**解决**:
1. 检查占用进程: `netstat -ano | findstr :8081`
2. 终止占用进程，或
3. 修改后端端口:
   - 编辑 `application.properties`
   - 修改 `server.port=8082`
   - 更新前端 `vite.config.js`
   - 重启前后端服务

### 问题3: CORS跨域错误
**原因**: 前端端口与后端端口不匹配

**解决**:
1. 确保 `vite.config.js` 中 `changeOrigin: true`
2. 检查Controller中是否有 `@CrossOrigin(origins = "*")`
3. 确认前后端端口配置正确

## 快速检查清单

如果游戏无法连接，请检查：

- [ ] 后端是否启动？ (端口8081)
- [ ] 前端是否启动？ (端口3000)
- [ ] 前端代理配置是否正确？ (指向8081)
- [ ] 浏览器控制台是否有错误？
- [ ] API测试脚本是否正常运行？

## API测试

运行测试脚本:
```bash
test_api.bat  # Windows
./test_api.sh  # Linux/Mac (需要创建)
```

预期输出:
```json
{
  "name": "德州扑克游戏服务器",
  "version": "1.0.0",
  "java_version": "17.0.x",
  "framework": "Spring Boot 3.2.0"
}
```

## 端口映射表

| 服务 | 端口 | 用途 | 配置文件 |
|------|------|------|----------|
| Spring Boot | 8081 | 后端API | application.properties |
| Vue Dev | 3000 | 前端开发 | vite.config.js |
| Flask (Python) | 5000 | Python后端 | - |
| Vue Build | 80/443 | 生产环境 | nginx/apache |

## 生产环境建议

### 开发环境
- 后端: 8081
- 前端: 3000
- 代理: vite.config.js

### 生产环境
- 后端: 8080/8081
- 前端: 80 (HTTP) / 443 (HTTPS)
- 代理: Nginx/Apache反向代理

示例Nginx配置:
```nginx
server {
    listen 80;
    server_name your-domain.com;

    location /api {
        proxy_pass http://localhost:8081;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }

    location / {
        root /path/to/frontend/dist;
        try_files $uri $uri/ /index.html;
    }
}
```

---

**最后更新**: 2026-04-07  
**当前端口**: 后端8081，前端3000
