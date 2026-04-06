package com.texaspoker.model;

/**
 * 手牌牌型等级
 */
public enum HandRank {
    HIGH_CARD(0, "高牌"),
    ONE_PAIR(1, "一对"),
    TWO_PAIR(2, "两对"),
    THREE_OF_A_KIND(3, "三条"),
    STRAIGHT(4, "顺子"),
    FLUSH(5, "同花"),
    FULL_HOUSE(6, "葫芦"),
    FOUR_OF_A_KIND(7, "四条"),
    STRAIGHT_FLUSH(8, "同花顺"),
    ROYAL_FLUSH(9, "皇家同花顺");

    private final int value;
    private final String description;

    HandRank(int value, String description) {
        this.value = value;
        this.description = description;
    }

    public int getValue() {
        return value;
    }

    public String getDescription() {
        return description;
    }
}
