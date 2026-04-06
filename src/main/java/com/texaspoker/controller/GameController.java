package com.texaspoker.controller;

import com.texaspoker.service.PokerGameService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.Map;

@Slf4j
@RestController
@RequestMapping("/api")
@CrossOrigin(origins = "*")
public class GameController {

    @Autowired
    private PokerGameService gameService;

    @GetMapping("/info")
    public ResponseEntity<Map<String, Object>> getAppInfo() {
        Map<String, Object> info = new HashMap<>();
        info.put("name", "德州扑克游戏服务器");
        info.put("version", "1.0.0");
        info.put("java_version", System.getProperty("java.version"));
        info.put("framework", "Spring Boot 3.2.0");
        info.put("description", "德州扑克游戏后端API - Spring Boot版本");
        return ResponseEntity.ok(info);
    }

    @GetMapping("/game/state")
    public ResponseEntity<Map<String, Object>> getGameState(@RequestParam(required = false) Integer playerId) {
        try {
            Map<String, Object> state = gameService.getGameState(playerId);
            return ResponseEntity.ok(state);
        } catch (Exception e) {
            log.error("获取游戏状态失败", e);
            return ResponseEntity.badRequest().body(createErrorResponse(e.getMessage()));
        }
    }

    @PostMapping("/game/start")
    public ResponseEntity<Map<String, Object>> startGame() {
        try {
            gameService.startNewHand();
            Map<String, Object> response = new HashMap<>();
            response.put("success", true);
            response.put("message", "新牌局开始！");
            return ResponseEntity.ok(response);
        } catch (Exception e) {
            log.error("开始游戏失败", e);
            return ResponseEntity.badRequest().body(createErrorResponse(e.getMessage()));
        }
    }

    @PostMapping("/game/action")
    public ResponseEntity<Map<String, Object>> playerAction(@RequestBody Map<String, Object> request) {
        try {
            String action = (String) request.get("action");
            Integer amount = request.containsKey("amount") ? (Integer) request.get("amount") : 0;

            if (action == null) {
                return ResponseEntity.badRequest().body(createErrorResponse("需要动作类型"));
            }

            Map<String, Object> result = gameService.playerAction(
                gameService.getGameState(null).get("active_player_index") != null ? 
                (Integer) gameService.getGameState(null).get("active_player_index") : 0,
                action,
                amount
            );

            return ResponseEntity.ok(result);
        } catch (Exception e) {
            log.error("玩家动作执行失败", e);
            return ResponseEntity.badRequest().body(createErrorResponse(e.getMessage()));
        }
    }

    @PostMapping("/game/robot_action")
    public ResponseEntity<Map<String, Object>> robotAction(@RequestBody Map<String, Object> request) {
        try {
            Integer playerId = (Integer) request.get("player_id");
            if (playerId == null) {
                return ResponseEntity.badRequest().body(createErrorResponse("需要玩家ID"));
            }

            Map<String, Object> result = gameService.robotAction(playerId);
            return ResponseEntity.ok(result);
        } catch (Exception e) {
            log.error("机器人动作执行失败", e);
            return ResponseEntity.badRequest().body(createErrorResponse(e.getMessage()));
        }
    }

    @PostMapping("/reset")
    public ResponseEntity<Map<String, Object>> resetGame() {
        try {
            gameService.resetGame();
            Map<String, Object> response = new HashMap<>();
            response.put("success", true);
            response.put("message", "游戏已重置");
            return ResponseEntity.ok(response);
        } catch (Exception e) {
            log.error("重置游戏失败", e);
            return ResponseEntity.badRequest().body(createErrorResponse(e.getMessage()));
        }
    }

    @GetMapping("/health")
    public ResponseEntity<Map<String, Object>> healthCheck() {
        Map<String, Object> health = new HashMap<>();
        health.put("status", "healthy");
        health.put("timestamp", System.currentTimeMillis());
        return ResponseEntity.ok(health);
    }

    private Map<String, Object> createErrorResponse(String message) {
        Map<String, Object> error = new HashMap<>();
        error.put("success", false);
        error.put("error", message);
        return error;
    }
}
