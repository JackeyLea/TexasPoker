"""
德州扑克游戏后端
"""

# !/bin/python3
# -*- coding: UTF-8 -*-

from flask import Flask, request, jsonify
from flask_cors import CORS
import random
import sys
from enum import Enum
from typing import List, Dict, Any, Optional, Tuple
from collections import Counter
import itertools
import logging
from datetime import datetime

# 配置日志
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    handlers=[
        logging.StreamHandler(sys.stdout),
        logging.FileHandler('poker_game.log')
    ]
)
logger = logging.getLogger(__name__)

app = Flask(__name__)
CORS(app)  # 允许跨域请求

# 应用信息
APP_INFO = {
    "name": "德州扑克游戏服务器",
    "version": "3.0.0",
    "python_version": f"{sys.version_info.major}.{sys.version_info.minor}.{sys.version_info.micro}",
    "author": "AI编程助手",
    "description": "德州扑克游戏后端API，包含完整胜负判断功能"
}

# ========== 数据模型定义 ==========
class Suit(Enum):
    """花色"""
    SPADES = "♠"
    HEARTS = "♥"
    DIAMONDS = "♦"
    CLUBS = "♣"

class Rank(Enum):
    """点数"""
    TWO = ("2", 2)
    THREE = ("3", 3)
    FOUR = ("4", 4)
    FIVE = ("5", 5)
    SIX = ("6", 6)
    SEVEN = ("7", 7)
    EIGHT = ("8", 8)
    NINE = ("9", 9)
    TEN = ("10", 10)
    JACK = ("J", 11)
    QUEEN = ("Q", 12)
    KING = ("K", 13)
    ACE = ("A", 14)

    def __init__(self, symbol: str, value: int):
        self.symbol = symbol
        self.value = value

class Card:
    """单张扑克牌"""
    def __init__(self, suit: Suit, rank: Rank):
        self.suit = suit
        self.rank = rank
        self.symbol = f"{rank.symbol}{suit.value}"
        self.color = "red" if suit in [Suit.HEARTS, Suit.DIAMONDS] else "black"
        self.value = rank.value
    
    def __repr__(self):
        return self.symbol

    def to_dict(self) -> Dict[str, Any]:
        return {
            "suit": self.suit.name,
            "rank": self.rank.name,
            "symbol": self.symbol,
            "color": self.color,
            "value": self.value
        }

class HandRank(Enum):
    """手牌牌型等级"""
    HIGH_CARD = 0        # 高牌
    ONE_PAIR = 1         # 一对
    TWO_PAIR = 2         # 两对
    THREE_OF_A_KIND = 3  # 三条
    STRAIGHT = 4         # 顺子
    FLUSH = 5            # 同花
    FULL_HOUSE = 6       # 葫芦
    FOUR_OF_A_KIND = 7   # 四条
    STRAIGHT_FLUSH = 8   # 同花顺
    ROYAL_FLUSH = 9      # 皇家同花顺

class HandEvaluation:
    """手牌评估结果"""
    def __init__(self, rank: HandRank, values: List[int], hand: List[Card] = None):
        self.rank = rank
        self.values = values  # 用于比较的值列表，从主比较值到次比较值
        self.hand = hand or []  # 组成最佳牌的5张牌
    
    def __lt__(self, other) -> bool:
        """小于比较，用于排序"""
        if self.rank.value != other.rank.value:
            return self.rank.value < other.rank.value
        for i in range(len(self.values)):
            if i >= len(other.values):
                return False
            if self.values[i] != other.values[i]:
                return self.values[i] < other.values[i]
        return False
    
    def __eq__(self, other) -> bool:
        """等于比较"""
        if self.rank.value != other.rank.value:
            return False
        for i in range(min(len(self.values), len(other.values))):
            if self.values[i] != other.values[i]:
                return False
        return True
    
    def __gt__(self, other) -> bool:
        return not self.__lt__(other) and not self.__eq__(other)
    
    def __repr__(self):
        return f"{self.rank.name}: {self.values}"

class Player:
    """玩家"""
    def __init__(self, name: str, player_id: int, initial_stack: int = 1000):
        self.id = player_id
        self.name = name
        self.stack = initial_stack
        self.hand: List[Card] = []
        self.bet = 0
        self.status = "active"  # active, folded, all_in, busted
        self.has_acted = False
        self.hand_evaluation: Optional[HandEvaluation] = None
    
    def to_dict(self, reveal_hand: bool = False) -> Dict[str, Any]:
        """转换为字典，用于API返回。reveal_hand控制是否暴露手牌。"""
        result = {
            "id": self.id,
            "name": self.name,
            "stack": self.stack,
            "bet": self.bet,
            "status": self.status,
            "hand": [card.to_dict() for card in self.hand] if reveal_hand else []
        }
        if reveal_hand and self.hand_evaluation:
            result["hand_rank"] = self.hand_evaluation.rank.name
            result["hand_description"] = get_hand_description(self.hand_evaluation)
        return result

class PokerGame:
    """德州扑克游戏主逻辑"""
    def __init__(self):
        self.deck: List[Card] = []
        self.players: List[Player] = []
        self.community_cards: List[Card] = []
        self.pot = 0
        self.current_bet = 0
        self.dealer_position = 0
        self.active_player_index = 0
        self.game_state = "idle"  # idle, preflop, flop, turn, river, showdown, ended
        self.betting_round_complete = False
        self.small_blind = 10
        self.big_blind = 20
        self.winners: List[Tuple[Player, int]] = []  # 获胜玩家及赢得的筹码
        self.game_id = datetime.now().strftime("%Y%m%d_%H%M%S")
        self._create_deck()
        logger.info(f"创建新游戏实例，游戏ID: {self.game_id}")
    
    def _create_deck(self) -> None:
        """创建一副52张牌"""
        self.deck = [Card(suit, rank) for suit in Suit for rank in Rank]
        random.shuffle(self.deck)
        logger.debug(f"创建并洗牌，剩余{len(self.deck)}张牌")
    
    def add_player(self, name: str) -> Player:
        """添加玩家"""
        player_id = len(self.players)
        player = Player(name, player_id)
        self.players.append(player)
        logger.info(f"添加玩家: {name} (ID: {player_id})")
        return player
    
    def start_new_hand(self) -> None:
        """开始新的一手牌"""
        if len(self.players) < 2:
            error_msg = "至少需要2名玩家才能开始游戏"
            logger.error(error_msg)
            raise ValueError(error_msg)
        
        # 重置状态
        self.community_cards = []
        self.pot = 0
        self.current_bet = 0
        self.betting_round_complete = False
        self.winners = []
        self._create_deck()
        
        active_count = 0
        for player in self.players:
            player.hand = []
            player.bet = 0
            player.status = "active" if player.stack > 0 else "busted"
            player.has_acted = False
            player.hand_evaluation = None
            if player.status == "active":
                active_count += 1
        
        if active_count < 2:
            error_msg = f"活跃玩家不足2人 (当前: {active_count})"
            logger.error(error_msg)
            raise ValueError(error_msg)
        
        # 发手牌
        for _ in range(2):
            for player in self.players:
                if player.status == "active":
                    player.hand.append(self.deck.pop())
        
        # 确定庄家和小盲、大盲位置
        active_players = [p for p in self.players if p.status == "active"]
        
        # 找到下一个活跃玩家作为庄家
        for _ in range(len(self.players)):
            self.dealer_position = (self.dealer_position + 1) % len(self.players)
            if self.players[self.dealer_position].status == "active":
                break
        
        # 找到小盲和大盲位置
        sb_index = self._find_next_active_player(self.dealer_position)
        bb_index = self._find_next_active_player(sb_index)
        
        # 收取盲注
        sb_player = self.players[sb_index]
        bb_player = self.players[bb_index]
        
        if sb_player.stack > 0:
            sb_bet = min(self.small_blind, sb_player.stack)
            self._place_bet(sb_player, sb_bet)
            logger.info(f"小盲 {sb_player.name} 下注 {sb_bet}")
        
        if bb_player.stack > 0:
            bb_bet = min(self.big_blind, bb_player.stack)
            self._place_bet(bb_player, bb_bet)
            logger.info(f"大盲 {bb_player.name} 下注 {bb_bet}")
        
        self.current_bet = self.big_blind
        # 设置行动玩家（大盲位下一位活跃玩家）
        self.active_player_index = self._find_next_active_player(bb_index)
        self.game_state = "preflop"
        
        # 记录游戏开始
        player_names = [p.name for p in self.players if p.status == "active"]
        logger.info(f"新牌局开始，活跃玩家: {', '.join(player_names)}")
        logger.info(f"庄家: {self.players[self.dealer_position].name}, "
                   f"小盲: {sb_player.name}, 大盲: {bb_player.name}")
    
    def _find_next_active_player(self, start_index: int) -> int:
        """从start_index开始找到下一个活跃玩家"""
        index = (start_index + 1) % len(self.players)
        while index != start_index:
            if self.players[index].status == "active":
                return index
            index = (index + 1) % len(self.players)
        return start_index
    
    def _place_bet(self, player: Player, amount: int) -> bool:
        """玩家下注。返回是否成功。"""
        actual_amount = min(amount, player.stack)
        player.stack -= actual_amount
        player.bet += actual_amount
        self.pot += actual_amount
        if player.stack == 0 and actual_amount > 0:
            player.status = "all_in"
            logger.info(f"玩家 {player.name} 全下")
        return actual_amount == amount
    
    def _get_next_active_player(self, start_index: int) -> Optional[int]:
        """获取下一个未弃牌且未全下的玩家索引。如果一圈结束返回None。"""
        index = (start_index + 1) % len(self.players)
        loop_count = 0
        while loop_count < len(self.players):
            player = self.players[index]
            if player.status == "active":
                return index
            index = (index + 1) % len(self.players)
            loop_count += 1
        return None
    
    def _advance_betting_round(self) -> None:
        """推进到下一条街（翻牌、转牌、河牌）或进入摊牌"""
        if self.game_state == "preflop":
            # 发三张翻牌
            self._burn_card()
            for _ in range(3):
                self.community_cards.append(self.deck.pop())
            self.game_state = "flop"
            logger.info(f"翻牌: {[str(card) for card in self.community_cards]}")
        
        elif self.game_state == "flop":
            # 发转牌
            self._burn_card()
            self.community_cards.append(self.deck.pop())
            self.game_state = "turn"
            logger.info(f"转牌: {self.community_cards[-1]}")
        
        elif self.game_state == "turn":
            # 发河牌
            self._burn_card()
            self.community_cards.append(self.deck.pop())
            self.game_state = "river"
            logger.info(f"河牌: {self.community_cards[-1]}")
        
        elif self.game_state == "river":
            self.game_state = "showdown"
            logger.info("进入摊牌阶段")
            self._evaluate_all_hands()
            self._determine_winners()
            return
        
        # 重置下注轮状态
        self.current_bet = 0
        for player in self.players:
            player.bet = 0
            player.has_acted = False
        
        # 设置行动玩家为庄家下一位
        self.active_player_index = (self.dealer_position + 1) % len(self.players)
        # 如果该玩家已弃牌或全下，则找到下一个活跃玩家
        next_player = self._get_next_active_player(self.active_player_index - 1)
        if next_player is not None:
            self.active_player_index = next_player
        self.betting_round_complete = False
    
    def _burn_card(self) -> None:
        """烧一张牌"""
        if self.deck:
            self.deck.pop()
    
    def _check_betting_round_complete(self) -> bool:
        """检查当前下注轮是否完成"""
        active_players = [p for p in self.players if p.status == "active"]
        if not active_players:
            return True
        for player in active_players:
            if not player.has_acted:
                return False
        target_bet = max(p.bet for p in active_players)
        for player in active_players:
            if player.bet < target_bet and player.status != "all_in":
                return False
        return True
    
    def player_action(self, player_id: int, action: str, amount: int = 0) -> Dict[str, Any]:
        """处理玩家动作。返回结果信息。"""
        player = self.players[player_id]
        
        if player.status != "active":
            error_msg = f"玩家 {player.name} 不能行动 (状态: {player.status})"
            logger.warning(error_msg)
            return {"success": False, "message": error_msg}
        
        if player_id != self.active_player_index:
            error_msg = f"不是玩家 {player.name} 的回合，当前行动玩家: {self.players[self.active_player_index].name}"
            logger.warning(error_msg)
            return {"success": False, "message": error_msg}

        message = ""
        if action == "fold":
            player.status = "folded"
            message = f"{player.name} 弃牌了。"
            logger.info(f"玩家 {player.name} 弃牌")

        elif action == "check":
            if player.bet < self.current_bet:
                error_msg = f"玩家 {player.name} 不能过牌，必须跟注或加注"
                logger.warning(error_msg)
                return {"success": False, "message": error_msg}
            message = f"{player.name} 过牌。"
            logger.info(f"玩家 {player.name} 过牌")

        elif action == "call":
            call_amount = self.current_bet - player.bet
            if call_amount > player.stack:
                call_amount = player.stack
            self._place_bet(player, call_amount)
            message = f"{player.name} 跟注 {call_amount}。"
            logger.info(f"玩家 {player.name} 跟注 {call_amount}")

        elif action == "bet":
            if amount <= 0:
                error_msg = f"下注额必须为正数: {amount}"
                logger.warning(error_msg)
                return {"success": False, "message": error_msg}
            if amount <= self.current_bet:
                error_msg = f"加注额必须大于当前下注额: {amount} <= {self.current_bet}"
                logger.warning(error_msg)
                return {"success": False, "message": error_msg}
            if amount > player.stack:
                error_msg = f"筹码不足: {amount} > {player.stack}"
                logger.warning(error_msg)
                return {"success": False, "message": error_msg}
            self._place_bet(player, amount - player.bet)
            self.current_bet = amount
            message = f"{player.name} 下注 {amount}。"
            logger.info(f"玩家 {player.name} 下注 {amount}")

        else:
            error_msg = f"未知动作: {action}"
            logger.warning(error_msg)
            return {"success": False, "message": error_msg}

        player.has_acted = True
        # 寻找下一个行动玩家
        next_player_index = self._get_next_active_player(self.active_player_index)
        if next_player_index is None:
            self.betting_round_complete = True
        else:
            self.active_player_index = next_player_index

        # 如果下注轮结束，推进游戏
        if self._check_betting_round_complete():
            self.betting_round_complete = True
            self._advance_betting_round()
            message += " 下注轮结束。"
            logger.info(f"下注轮结束，进入 {self.game_state}")

        return {"success": True, "message": message}
    
    def _evaluate_all_hands(self) -> None:
        """评估所有未弃牌玩家的最佳手牌"""
        for player in self.players:
            if player.status != "folded" and player.hand:
                player.hand_evaluation = self.evaluate_best_hand(player.hand + self.community_cards)
                logger.debug(f"玩家 {player.name} 手牌评估: {player.hand_evaluation}")
    
    def evaluate_best_hand(self, cards: List[Card]) -> HandEvaluation:
        """从7张牌中找出最佳的5张牌组合"""
        if len(cards) < 5:
            raise ValueError("需要至少5张牌来评估")
        
        best_hand = None
        # 尝试所有5张牌的组合
        for combo in itertools.combinations(cards, 5):
            hand_eval = self.evaluate_hand(list(combo))
            if best_hand is None or hand_eval > best_hand:
                best_hand = hand_eval
                best_hand.hand = list(combo)
        
        return best_hand
    
    def evaluate_hand(self, cards: List[Card]) -> HandEvaluation:
        """评估5张牌的牌力"""
        if len(cards) != 5:
            raise ValueError("需要恰好5张牌")
        
        # 按点数排序（从高到低）
        cards.sort(key=lambda c: c.value, reverse=True)
        values = [c.value for c in cards]
        suits = [c.suit for c in cards]
        
        # 检查是否同花
        is_flush = len(set(suits)) == 1
        
        # 检查是否顺子
        is_straight = False
        straight_high = 0
        
        # 处理A可以作为1的特殊情况
        value_set = set(values)
        if 14 in value_set:  # 有A
            value_set.add(1)  # 添加A作为1的情况
        
        # 检查顺子
        for high in range(14, 4, -1):
            if all(v in value_set for v in range(high, high-5, -1)):
                is_straight = True
                straight_high = high
                break
        
        # 计算点数频率
        value_counts = Counter(values)
        most_common = value_counts.most_common()
        
        # 判断牌型
        if is_straight and is_flush:
            # 同花顺
            if straight_high == 14:  # A, K, Q, J, 10
                return HandEvaluation(HandRank.ROYAL_FLUSH, [straight_high])
            return HandEvaluation(HandRank.STRAIGHT_FLUSH, [straight_high])
        
        if most_common[0][1] == 4:
            # 四条
            four_of_a_kind_value = most_common[0][0]
            kicker = most_common[1][0]
            return HandEvaluation(HandRank.FOUR_OF_A_KIND, [four_of_a_kind_value, kicker])
        
        if most_common[0][1] == 3 and len(most_common) >= 2 and most_common[1][1] >= 2:
            # 葫芦
            three_of_a_kind_value = most_common[0][0]
            pair_value = most_common[1][0]
            return HandEvaluation(HandRank.FULL_HOUSE, [three_of_a_kind_value, pair_value])
        
        if is_flush:
            # 同花
            return HandEvaluation(HandRank.FLUSH, values)
        
        if is_straight:
            # 顺子
            return HandEvaluation(HandRank.STRAIGHT, [straight_high])
        
        if most_common[0][1] == 3:
            # 三条
            three_of_a_kind_value = most_common[0][0]
            kickers = sorted([v for v in values if v != three_of_a_kind_value], reverse=True)
            return HandEvaluation(HandRank.THREE_OF_A_KIND, [three_of_a_kind_value] + kickers[:2])
        
        if most_common[0][1] == 2 and len(most_common) >= 2 and most_common[1][1] == 2:
            # 两对
            pairs = sorted([most_common[0][0], most_common[1][0]], reverse=True)
            kicker = most_common[2][0] if len(most_common) > 2 else 0
            return HandEvaluation(HandRank.TWO_PAIR, pairs + [kicker])
        
        if most_common[0][1] == 2:
            # 一对
            pair_value = most_common[0][0]
            kickers = sorted([v for v in values if v != pair_value], reverse=True)
            return HandEvaluation(HandRank.ONE_PAIR, [pair_value] + kickers[:3])
        
        # 高牌
        return HandEvaluation(HandRank.HIGH_CARD, values[:5])
    
    def _determine_winners(self) -> None:
        """确定获胜者并分配底池"""
        # 找出所有未弃牌的玩家
        active_players = [p for p in self.players if p.status != "folded"]
        
        if not active_players:
            self.game_state = "ended"
            return
        
        if len(active_players) == 1:
            winner = active_players[0]
            winner.stack += self.pot
            self.winners = [(winner, self.pot)]
            self.pot = 0
            self.game_state = "ended"
            logger.info(f"玩家 {winner.name} 获胜，赢得 {self.pot} 筹码")
            return
        
        # 找出最佳手牌
        best_hand = None
        winning_players = []
        
        for player in active_players:
            if player.hand_evaluation is not None:
                if best_hand is None or player.hand_evaluation > best_hand:
                    best_hand = player.hand_evaluation
                    winning_players = [player]
                elif player.hand_evaluation == best_hand:
                    winning_players.append(player)
        
        if not winning_players:
            share = self.pot // len(active_players)
            for player in active_players:
                player.stack += share
            self.winners = [(player, share) for player in active_players]
        else:
            share = self.pot // len(winning_players)
            remainder = self.pot % len(winning_players)
            
            for i, player in enumerate(winning_players):
                amount = share + (1 if i < remainder else 0)
                player.stack += amount
                self.winners.append((player, amount))
        
        self.pot = 0
        self.game_state = "ended"
        winner_names = [p.name for p in winning_players]
        logger.info(f"获胜玩家: {', '.join(winner_names)}，手牌: {best_hand}")
    
    def get_state(self, for_player_id: Optional[int] = None) -> Dict[str, Any]:
        """获取游戏状态。for_player_id用于决定向哪个玩家显示手牌。"""
        reveal_hand_to_all = (self.game_state == "showdown" or self.game_state == "ended")
        players_data = []
        for i, player in enumerate(self.players):
            reveal = (reveal_hand_to_all or i == for_player_id)
            players_data.append(player.to_dict(reveal_hand=reveal))
        
        result = {
            "game_state": self.game_state,
            "pot": self.pot,
            "current_bet": self.current_bet,
            "dealer_position": self.dealer_position,
            "active_player_index": self.active_player_index,
            "community_cards": [card.to_dict() for card in self.community_cards],
            "players": players_data
        }
        
        if self.game_state == "ended" and self.winners:
            result["winners"] = [
                {
                    "player_id": player.id,
                    "player_name": player.name,
                    "amount": amount,
                    "hand_rank": player.hand_evaluation.rank.name if player.hand_evaluation else None,
                    "hand_description": get_hand_description(player.hand_evaluation) if player.hand_evaluation else None
                }
                for player, amount in self.winners
            ]
        
        return result

def get_hand_description(hand_eval: HandEvaluation) -> str:
    """获取手牌类型的文字描述"""
    if not hand_eval:
        return "无手牌"
    
    rank_names = {
        HandRank.HIGH_CARD: "高牌",
        HandRank.ONE_PAIR: "一对",
        HandRank.TWO_PAIR: "两对",
        HandRank.THREE_OF_A_KIND: "三条",
        HandRank.STRAIGHT: "顺子",
        HandRank.FLUSH: "同花",
        HandRank.FULL_HOUSE: "葫芦",
        HandRank.FOUR_OF_A_KIND: "四条",
        HandRank.STRAIGHT_FLUSH: "同花顺",
        HandRank.ROYAL_FLUSH: "皇家同花顺"
    }
    
    return rank_names.get(hand_eval.rank, "未知牌型")

# ========== 全局游戏实例 ==========
game = PokerGame()
# 添加几个示例玩家
game.add_player("玩家A")
game.add_player("玩家B")
game.add_player("玩家C")

# ========== Flask API 路由 ==========
@app.route('/')
def index():
    return "德州扑克后端API已运行。请使用前端界面进行交互。"

@app.route('/api/info', methods=['GET'])
def get_app_info():
    """获取应用信息"""
    return jsonify(APP_INFO)

@app.route('/api/game/state', methods=['GET'])
def get_game_state():
    """获取当前游戏状态"""
    return jsonify(game.get_state())

@app.route('/api/game/start', methods=['POST'])
def start_game():
    """开始新的一手牌"""
    try:
        game.start_new_hand()
        return jsonify({
            "success": True,
            "message": "新牌局开始！",
            "players": [p.name for p in game.players if p.status == "active"]
        })
    except Exception as e:
        logger.error(f"开始游戏失败: {str(e)}")
        return jsonify({"success": False, "error": str(e)}), 400

@app.route('/api/game/action', methods=['POST'])
def player_action():
    """玩家执行动作"""
    data = request.get_json()
    if not data:
        return jsonify({"success": False, "error": "需要JSON数据"}), 400
    
    action = data.get('action')
    amount = data.get('amount', 0)
    
    if not action:
        return jsonify({"success": False, "error": "需要动作类型"}), 400
    
    try:
        result = game.player_action(game.active_player_index, action, amount)
        return jsonify(result)
    except Exception as e:
        logger.error(f"玩家动作执行失败: {str(e)}")
        return jsonify({"success": False, "error": str(e)}), 400

@app.route('/api/reset', methods=['POST'])
def reset_game():
    """重置游戏（用于调试）"""
    global game
    game = PokerGame()
    game.add_player("玩家A")
    game.add_player("玩家B")
    game.add_player("玩家C")
    logger.info("游戏已重置")
    return jsonify({"success": True, "message": "游戏已重置"})

@app.route('/api/health', methods=['GET'])
def health_check():
    """健康检查"""
    return jsonify({
        "status": "healthy",
        "game_state": game.game_state,
        "active_players": len([p for p in game.players if p.status == "active"])
    })

# ========== 主程序 ==========
if __name__ == '__main__':
    print("=" * 50)
    print("德州扑克后端服务器启动...")
    print(f"应用名称: {APP_INFO['name']}")
    print(f"版本: {APP_INFO['version']}")
    print(f"Python版本: {APP_INFO['python_version']}")
    print(f"游戏ID: {game.game_id}")
    print("=" * 50)
    print("前端界面预计运行在: http://127.0.0.1:5000")
    print("API基础URL: http://127.0.0.1:5000/api")
    print("可用接口:")
    print("  GET  /api/info         - 获取应用信息")
    print("  GET  /api/game/state   - 获取游戏状态")
    print("  POST /api/game/start   - 开始新游戏")
    print("  POST /api/game/action  - 玩家动作")
    print("  POST /api/reset        - 重置游戏")
    print("  GET  /api/health       - 健康检查")
    print("=" * 50)
    
    try:
        app.run(debug=True, host='0.0.0.0', port=5000)
    except Exception as e:
        logger.error(f"服务器启动失败: {str(e)}")
        sys.exit(1)
