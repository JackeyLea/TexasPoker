package com.texaspoker.model;

/**
 * 花色枚举
 */
public enum Suit {
    SPADES("♠"),
    HEARTS("♥"),
    DIAMONDS("♦"),
    CLUBS("♣");

    private final String symbol;

    Suit(String symbol) {
        this.symbol = symbol;
    }

    public String getSymbol() {
        return symbol;
    }
}
