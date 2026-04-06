package com.texaspoker.model;

/**
 * 游戏状态枚举
 */
public enum GameState {
    IDLE("idle"),
    PREFLOP("preflop"),
    FLOP("flop"),
    TURN("turn"),
    RIVER("river"),
    SHOWDOWN("showdown"),
    ENDED("ended");

    private final String value;

    GameState(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }
}
