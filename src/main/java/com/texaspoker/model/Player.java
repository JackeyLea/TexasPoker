package com.texaspoker.model;

import lombok.Data;
import java.util.ArrayList;
import java.util.List;

@Data
public class Player {
    private int id;
    private String name;
    private int stack;
    private List<Card> hand;
    private int bet;
    private PlayerStatus status;
    private boolean hasActed;
    private HandEvaluation handEvaluation;
    private boolean isRobot;

    public Player(int id, String name, int initialStack, boolean isRobot) {
        this.id = id;
        this.name = name;
        this.stack = initialStack;
        this.hand = new ArrayList<>();
        this.bet = 0;
        this.status = PlayerStatus.ACTIVE;
        this.hasActed = false;
        this.handEvaluation = null;
        this.isRobot = isRobot;
    }

    public void resetHand() {
        this.hand.clear();
        this.bet = 0;
        this.status = this.stack > 0 ? PlayerStatus.ACTIVE : PlayerStatus.BUSTED;
        this.hasActed = false;
        this.handEvaluation = null;
    }
}
