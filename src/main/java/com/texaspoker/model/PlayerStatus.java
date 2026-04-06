package com.texaspoker.model;

/**
 * 玩家状态
 */
public enum PlayerStatus {
    ACTIVE("active"),
    FOLDED("folded"),
    ALL_IN("all_in"),
    BUSTED("busted");

    private final String value;

    PlayerStatus(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }
}
