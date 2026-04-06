package com.texaspoker.model;

import lombok.Data;
import java.util.List;

@Data
public class HandEvaluation implements Comparable<HandEvaluation> {
    private final HandRank rank;
    private final List<Integer> values;
    private List<Card> hand;

    public HandEvaluation(HandRank rank, List<Integer> values, List<Card> hand) {
        this.rank = rank;
        this.values = values;
        this.hand = hand;
    }

    public HandEvaluation(HandRank rank, List<Integer> values) {
        this(rank, values, null);
    }

    @Override
    public int compareTo(HandEvaluation other) {
        if (this.rank.getValue() != other.rank.getValue()) {
            return Integer.compare(this.rank.getValue(), other.rank.getValue());
        }

        for (int i = 0; i < this.values.size(); i++) {
            if (i >= other.values.size()) {
                return 1;
            }
            if (!this.values.get(i).equals(other.values.get(i))) {
                return Integer.compare(this.values.get(i), other.values.get(i));
            }
        }
        return 0;
    }
}
