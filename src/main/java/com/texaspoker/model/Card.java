package com.texaspoker.model;

import lombok.Data;

/**
 * 扑克牌
 */
@Data
public class Card {
    private final Suit suit;
    private final Rank rank;
    private final String symbol;
    private final String color;
    private final int value;

    public Card(Suit suit, Rank rank) {
        this.suit = suit;
        this.rank = rank;
        this.symbol = rank.getSymbol() + suit.getSymbol();
        this.color = (suit == Suit.HEARTS || suit == Suit.DIAMONDS) ? "red" : "black";
        this.value = rank.getValue();
    }

    @Override
    public String toString() {
        return symbol;
    }
}
