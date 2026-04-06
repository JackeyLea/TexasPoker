package com.texaspoker.service;

import com.texaspoker.model.*;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.stream.Collectors;

@Slf4j
@Service
public class PokerGameService {
    private List<Card> deck;
    private List<Player> players;
    private List<Card> communityCards;
    private int pot;
    private int currentBet;
    private int dealerPosition;
    private int activePlayerIndex;
    private GameState gameState;
    private boolean bettingRoundComplete;
    private final int smallBlind = 10;
    private final int bigBlind = 20;
    private List<Map<String, Object>> winners;
    private String gameId;

    public PokerGameService() {
        initializeGame();
    }

    private void initializeGame() {
        this.deck = new ArrayList<>();
        this.players = new ArrayList<>();
        this.communityCards = new ArrayList<>();
        this.pot = 0;
        this.currentBet = 0;
        this.dealerPosition = 0;
        this.activePlayerIndex = 0;
        this.gameState = GameState.IDLE;
        this.bettingRoundComplete = false;
        this.winners = new ArrayList<>();
        this.gameId = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyyMMdd_HHmmss"));

        createDeck();
        addPlayer("你", 1000, false);
        addPlayer("机器人1", 1000, true);
        addPlayer("机器人2", 1000, true);

        log.info("创建新游戏实例，游戏ID: {}", gameId);
    }

    private void createDeck() {
        deck.clear();
        for (Suit suit : Suit.values()) {
            for (Rank rank : Rank.values()) {
                deck.add(new Card(suit, rank));
            }
        }
        Collections.shuffle(deck);
        log.debug("创建并洗牌，剩余{}张牌", deck.size());
    }

    public Player addPlayer(String name, int initialStack, boolean isRobot) {
        int playerId = players.size();
        Player player = new Player(playerId, name, initialStack, isRobot);
        players.add(player);
        log.info("添加玩家: {} (ID: {}, {})", name, playerId, isRobot ? "机器人" : "人类");
        return player;
    }

    public void startNewHand() {
        if (players.size() < 2) {
            throw new IllegalStateException("至少需要2名玩家才能开始游戏");
        }

        communityCards.clear();
        pot = 0;
        currentBet = 0;
        bettingRoundComplete = false;
        winners.clear();
        createDeck();

        int activeCount = 0;
        for (Player player : players) {
            player.resetHand();
            if (player.getStatus() == PlayerStatus.ACTIVE) {
                activeCount++;
            }
        }

        if (activeCount < 2) {
            throw new IllegalStateException("活跃玩家不足2人");
        }

        for (int i = 0; i < 2; i++) {
            for (Player player : players) {
                if (player.getStatus() == PlayerStatus.ACTIVE) {
                    player.getHand().add(deck.remove(deck.size() - 1));
                }
            }
        }

        dealerPosition = 2;
        int sbIndex = findNextActivePlayer(dealerPosition);
        int bbIndex = findNextActivePlayer(sbIndex);

        Player sbPlayer = players.get(sbIndex);
        Player bbPlayer = players.get(bbIndex);

        if (sbPlayer.getStack() > 0) {
            int sbBet = Math.min(smallBlind, sbPlayer.getStack());
            placeBet(sbPlayer, sbBet);
        }

        if (bbPlayer.getStack() > 0) {
            int bbBet = Math.min(bigBlind, bbPlayer.getStack());
            placeBet(bbPlayer, bbBet);
        }

        currentBet = bigBlind;
        activePlayerIndex = findNextActivePlayer(bbIndex);
        gameState = GameState.PREFLOP;
    }

    private int findNextActivePlayer(int startIndex) {
        int index = (startIndex + 1) % players.size();
        while (index != startIndex) {
            if (players.get(index).getStatus() == PlayerStatus.ACTIVE) {
                return index;
            }
            index = (index + 1) % players.size();
        }
        return startIndex;
    }

    private void placeBet(Player player, int amount) {
        int actualAmount = Math.min(amount, player.getStack());
        player.setStack(player.getStack() - actualAmount);
        player.setBet(player.getBet() + actualAmount);
        pot += actualAmount;

        if (player.getStack() == 0 && actualAmount > 0) {
            player.setStatus(PlayerStatus.ALL_IN);
        }
    }

    private void advanceBettingRound() {
        switch (gameState) {
            case PREFLOP:
                burnCard();
                for (int i = 0; i < 3; i++) {
                    communityCards.add(deck.remove(deck.size() - 1));
                }
                gameState = GameState.FLOP;
                break;
            case FLOP:
                burnCard();
                communityCards.add(deck.remove(deck.size() - 1));
                gameState = GameState.TURN;
                break;
            case TURN:
                burnCard();
                communityCards.add(deck.remove(deck.size() - 1));
                gameState = GameState.RIVER;
                break;
            case RIVER:
                gameState = GameState.SHOWDOWN;
                evaluateAllHands();
                determineWinners();
                return;
        }

        currentBet = 0;
        for (Player player : players) {
            player.setBet(0);
            player.setHasActed(false);
        }

        activePlayerIndex = findNextActivePlayer(dealerPosition);
        bettingRoundComplete = false;
    }

    private void burnCard() {
        if (!deck.isEmpty()) {
            deck.remove(deck.size() - 1);
        }
    }

    public Map<String, Object> playerAction(int playerId, String action, int amount) {
        Player player = players.get(playerId);

        if (player.getStatus() != PlayerStatus.ACTIVE) {
            return createErrorResult("玩家不能行动");
        }

        if (playerId != activePlayerIndex) {
            return createErrorResult("不是该玩家的回合");
        }

        String message = "";
        switch (action) {
            case "fold":
                player.setStatus(PlayerStatus.FOLDED);
                message = player.getName() + " 弃牌了。";
                break;
            case "check":
                if (player.getBet() < currentBet) {
                    return createErrorResult("不能过牌");
                }
                message = player.getName() + " 过牌。";
                break;
            case "call":
                int callAmount = currentBet - player.getBet();
                if (callAmount > player.getStack()) {
                    callAmount = player.getStack();
                }
                placeBet(player, callAmount);
                message = player.getName() + " 跟注 " + callAmount + "。";
                break;
            case "bet":
                if (amount <= 0 || amount <= currentBet || amount > player.getStack()) {
                    return createErrorResult("下注不合法");
                }
                placeBet(player, amount - player.getBet());
                currentBet = amount;
                message = player.getName() + " 下注 " + amount + "。";
                break;
            default:
                return createErrorResult("未知动作");
        }

        player.setHasActed(true);
        Integer nextPlayerIndex = getNextActivePlayer(activePlayerIndex);
        if (nextPlayerIndex == null) {
            bettingRoundComplete = true;
        } else {
            activePlayerIndex = nextPlayerIndex;
        }

        if (checkBettingRoundComplete()) {
            bettingRoundComplete = true;
            advanceBettingRound();
            message += " 下注轮结束。";
        }

        Map<String, Object> result = new HashMap<>();
        result.put("success", true);
        result.put("message", message);
        return result;
    }

    private Integer getNextActivePlayer(int startIndex) {
        int index = (startIndex + 1) % players.size();
        int loopCount = 0;
        while (loopCount < players.size()) {
            if (players.get(index).getStatus() == PlayerStatus.ACTIVE) {
                return index;
            }
            index = (index + 1) % players.size();
            loopCount++;
        }
        return null;
    }

    private boolean checkBettingRoundComplete() {
        List<Player> activePlayers = players.stream()
            .filter(p -> p.getStatus() == PlayerStatus.ACTIVE)
            .collect(Collectors.toList());

        if (activePlayers.isEmpty()) {
            return true;
        }

        for (Player player : activePlayers) {
            if (!player.isHasActed()) {
                return false;
            }
        }

        int targetBet = activePlayers.stream().mapToInt(Player::getBet).max().orElse(0);
        for (Player player : activePlayers) {
            if (player.getBet() < targetBet && player.getStatus() != PlayerStatus.ALL_IN) {
                return false;
            }
        }

        return true;
    }

    private void evaluateAllHands() {
        for (Player player : players) {
            if (player.getStatus() != PlayerStatus.FOLDED && !player.getHand().isEmpty()) {
                List<Card> allCards = new ArrayList<>();
                allCards.addAll(player.getHand());
                allCards.addAll(communityCards);
                player.setHandEvaluation(evaluateBestHand(allCards));
            }
        }
    }

    public HandEvaluation evaluateBestHand(List<Card> cards) {
        if (cards.size() < 5) {
            throw new IllegalArgumentException("需要至少5张牌");
        }

        HandEvaluation bestHand = null;
        List<Card> bestHandCards = null;

        for (int i = 0; i < cards.size(); i++) {
            for (int j = i + 1; j < cards.size(); j++) {
                for (int k = j + 1; k < cards.size(); k++) {
                    for (int l = k + 1; l < cards.size(); l++) {
                        for (int m = l + 1; m < cards.size(); m++) {
                            List<Card> hand = Arrays.asList(
                                cards.get(i), cards.get(j), cards.get(k),
                                cards.get(l), cards.get(m)
                            );
                            HandEvaluation evaluation = evaluateHand(hand);
                            if (bestHand == null || evaluation.compareTo(bestHand) > 0) {
                                bestHand = evaluation;
                                bestHandCards = hand;
                            }
                        }
                    }
                }
            }
        }

        bestHand.setHand(bestHandCards);
        return bestHand;
    }

    public HandEvaluation evaluateHand(List<Card> cards) {
        cards.sort(Comparator.comparingInt(Card::getValue).reversed());
        List<Integer> values = cards.stream().map(Card::getValue).collect(Collectors.toList());
        List<Suit> suits = cards.stream().map(Card::getSuit).collect(Collectors.toList());

        boolean isFlush = suits.stream().distinct().count() == 1;

        boolean isStraight = false;
        int straightHigh = 0;

        Set<Integer> valueSet = new HashSet<>(values);
        if (values.contains(14)) {
            valueSet.add(1);
        }

        for (int high = 14; high > 4; high--) {
            boolean hasStraight = true;
            for (int v = high; v > high - 5; v--) {
                if (!valueSet.contains(v)) {
                    hasStraight = false;
                    break;
                }
            }
            if (hasStraight) {
                isStraight = true;
                straightHigh = high;
                break;
            }
        }

        Map<Integer, Long> valueCounts = values.stream()
            .collect(Collectors.groupingBy(v -> v, Collectors.counting()));

        List<Map.Entry<Integer, Long>> sortedCounts = valueCounts.entrySet().stream()
            .sorted((a, b) -> {
                int cmp = Long.compare(b.getValue(), a.getValue());
                if (cmp != 0) return cmp;
                return Integer.compare(b.getKey(), a.getKey());
            })
            .collect(Collectors.toList());

        if (isStraight && isFlush) {
            if (straightHigh == 14) {
                return new HandEvaluation(HandRank.ROYAL_FLUSH, Arrays.asList(straightHigh));
            }
            return new HandEvaluation(HandRank.STRAIGHT_FLUSH, Arrays.asList(straightHigh));
        }

        if (sortedCounts.get(0).getValue() == 4) {
            int fourValue = sortedCounts.get(0).getKey();
            int kicker = sortedCounts.get(1).getKey();
            return new HandEvaluation(HandRank.FOUR_OF_A_KIND, Arrays.asList(fourValue, kicker));
        }

        if (sortedCounts.get(0).getValue() == 3 && sortedCounts.size() > 1 && sortedCounts.get(1).getValue() >= 2) {
            int threeValue = sortedCounts.get(0).getKey();
            int pairValue = sortedCounts.get(1).getKey();
            return new HandEvaluation(HandRank.FULL_HOUSE, Arrays.asList(threeValue, pairValue));
        }

        if (isFlush) {
            return new HandEvaluation(HandRank.FLUSH, values);
        }

        if (isStraight) {
            return new HandEvaluation(HandRank.STRAIGHT, Arrays.asList(straightHigh));
        }

        if (sortedCounts.get(0).getValue() == 3) {
            int threeValue = sortedCounts.get(0).getKey();
            List<Integer> kickers = values.stream()
                .filter(v -> v != threeValue)
                .sorted(Comparator.reverseOrder())
                .limit(2)
                .collect(Collectors.toList());
            List<Integer> result = new ArrayList<>();
            result.add(threeValue);
            result.addAll(kickers);
            return new HandEvaluation(HandRank.THREE_OF_A_KIND, result);
        }

        if (sortedCounts.get(0).getValue() == 2 && sortedCounts.size() > 1 && sortedCounts.get(1).getValue() == 2) {
            List<Integer> pairs = Arrays.asList(sortedCounts.get(0).getKey(), sortedCounts.get(1).getKey());
            pairs.sort(Comparator.reverseOrder());
            int kicker = sortedCounts.size() > 2 ? sortedCounts.get(2).getKey() : 0;
            return new HandEvaluation(HandRank.TWO_PAIR, Arrays.asList(pairs.get(0), pairs.get(1), kicker));
        }

        if (sortedCounts.get(0).getValue() == 2) {
            int pairValue = sortedCounts.get(0).getKey();
            List<Integer> kickers = values.stream()
                .filter(v -> v != pairValue)
                .sorted(Comparator.reverseOrder())
                .limit(3)
                .collect(Collectors.toList());
            List<Integer> result = new ArrayList<>();
            result.add(pairValue);
            result.addAll(kickers);
            return new HandEvaluation(HandRank.ONE_PAIR, result);
        }

        List<Integer> highCards = values.stream().limit(5).collect(Collectors.toList());
        return new HandEvaluation(HandRank.HIGH_CARD, highCards);
    }

    private void determineWinners() {
        List<Player> activePlayers = players.stream()
            .filter(p -> p.getStatus() != PlayerStatus.FOLDED)
            .collect(Collectors.toList());

        winners.clear();

        if (activePlayers.isEmpty()) {
            gameState = GameState.ENDED;
            return;
        }

        if (activePlayers.size() == 1) {
            Player winner = activePlayers.get(0);
            winner.setStack(winner.getStack() + pot);
            addWinner(winner, pot);
            pot = 0;
            gameState = GameState.ENDED;
            return;
        }

        HandEvaluation bestHand = null;
        List<Player> winningPlayers = new ArrayList<>();

        for (Player player : activePlayers) {
            if (player.getHandEvaluation() != null) {
                if (bestHand == null || player.getHandEvaluation().compareTo(bestHand) > 0) {
                    bestHand = player.getHandEvaluation();
                    winningPlayers.clear();
                    winningPlayers.add(player);
                } else if (player.getHandEvaluation().compareTo(bestHand) == 0) {
                    winningPlayers.add(player);
                }
            }
        }

        int share = pot / winningPlayers.size();
        int remainder = pot % winningPlayers.size();

        for (int i = 0; i < winningPlayers.size(); i++) {
            Player player = winningPlayers.get(i);
            int amount = share + (i < remainder ? 1 : 0);
            player.setStack(player.getStack() + amount);
            addWinner(player, amount);
        }

        pot = 0;
        gameState = GameState.ENDED;
    }

    private void addWinner(Player player, int amount) {
        Map<String, Object> winnerInfo = new HashMap<>();
        winnerInfo.put("player_id", player.getId());
        winnerInfo.put("player_name", player.getName());
        winnerInfo.put("amount", amount);
        winnerInfo.put("hand_rank", player.getHandEvaluation() != null ? 
            player.getHandEvaluation().getRank().getDescription() : null);
        winners.add(winnerInfo);
    }

    private Map<String, Object> createErrorResult(String message) {
        Map<String, Object> result = new HashMap<>();
        result.put("success", false);
        result.put("error", message);
        return result;
    }

    public Map<String, Object> getGameState(Integer forPlayerId) {
        boolean revealHandToAll = (gameState == GameState.SHOWDOWN || gameState == GameState.ENDED);
        
        List<Map<String, Object>> playersData = new ArrayList<>();
        for (int i = 0; i < players.size(); i++) {
            Player player = players.get(i);
            boolean reveal = revealHandToAll || (forPlayerId != null && i == forPlayerId);
            playersData.add(convertPlayerToMap(player, reveal));
        }

        Map<String, Object> result = new HashMap<>();
        result.put("game_state", gameState.getValue());
        result.put("pot", pot);
        result.put("current_bet", currentBet);
        result.put("dealer_position", dealerPosition);
        result.put("active_player_index", activePlayerIndex);
        result.put("community_cards", convertCardsToMap(communityCards));
        result.put("players", playersData);
        result.put("game_id", gameId);

        if (gameState == GameState.ENDED && !winners.isEmpty()) {
            result.put("winners", winners);
        }

        return result;
    }

    private Map<String, Object> convertPlayerToMap(Player player, boolean revealHand) {
        Map<String, Object> map = new HashMap<>();
        map.put("id", player.getId());
        map.put("name", player.getName());
        map.put("stack", player.getStack());
        map.put("bet", player.getBet());
        map.put("status", player.getStatus().getValue());

        if (revealHand && !player.getHand().isEmpty()) {
            map.put("hand", convertCardsToMap(player.getHand()));
            if (player.getHandEvaluation() != null) {
                map.put("hand_rank", player.getHandEvaluation().getRank().name());
                map.put("hand_description", player.getHandEvaluation().getRank().getDescription());
            }
        } else {
            map.put("hand", new ArrayList<>());
        }

        return map;
    }

    private List<Map<String, Object>> convertCardsToMap(List<Card> cards) {
        List<Map<String, Object>> result = new ArrayList<>();
        for (Card card : cards) {
            Map<String, Object> cardMap = new HashMap<>();
            cardMap.put("suit", card.getSuit().name());
            cardMap.put("rank", card.getRank().name());
            cardMap.put("symbol", card.getSymbol());
            cardMap.put("color", card.getColor());
            cardMap.put("value", card.getValue());
            result.add(cardMap);
        }
        return result;
    }

    public Map<String, Object> robotAction(int playerId) {
        Player player = players.get(playerId);

        if (!player.isRobot() || player.getStatus() != PlayerStatus.ACTIVE) {
            return createErrorResult("不是机器人玩家或不能行动");
        }

        double handStrength = calculateHandStrength(player);
        int callAmount = currentBet - player.getBet();
        boolean canCall = callAmount <= player.getStack();

        Random random = new Random();
        double randomFactor = random.nextDouble();

        String action = "fold";
        int amount = 0;

        if (handStrength > 0.7) {
            if (randomFactor < 0.7 && player.getStack() > currentBet * 2) {
                action = "bet";
                amount = Math.min(player.getStack(), Math.max(currentBet * 2, 50));
            } else if (canCall) {
                action = "call";
            }
        } else if (handStrength > 0.4) {
            if (currentBet == player.getBet()) {
                action = "check";
            } else if (canCall) {
                action = "call";
            }
        } else {
            if (currentBet == player.getBet()) {
                action = "check";
            } else if (callAmount <= player.getStack() * 0.1) {
                action = "call";
            }
        }

        log.info("机器人 {} AI决策: {}, 金额: {}", player.getName(), action, amount);
        return playerAction(playerId, action, amount);
    }

    private double calculateHandStrength(Player player) {
        if (player.getHand().size() < 2) {
            return 0.0;
        }

        Card card1 = player.getHand().get(0);
        Card card2 = player.getHand().get(1);

        double strength = 0.0;

        if (card1.getValue() == card2.getValue()) {
            strength += 0.3;
        }

        if (card1.getSuit() == card2.getSuit()) {
            strength += 0.2;
        }

        strength += (Math.max(card1.getValue(), card2.getValue()) - 2) * 0.02;

        int gap = Math.abs(card1.getValue() - card2.getValue());
        if (gap <= 1) {
            strength += 0.2;
        } else if (gap <= 2) {
            strength += 0.1;
        }

        return Math.min(strength, 1.0);
    }

    public void resetGame() {
        initializeGame();
        log.info("游戏已重置");
    }
}
