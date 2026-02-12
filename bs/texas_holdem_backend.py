from flask import Flask, request, jsonify
from flask_cors import CORS
import random
from enum import Enum
from typing import List, Dict, Any, Optional, Tuple

app = Flask(__name__)
CORS(app)  # 允许跨域请求，以便前端访问

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

    def to_dict(self) -> Dict[str, Any]:
        return {
            "suit": self.suit.name,
            "rank": self.rank.name,
            "symbol": self.symbol,
            "color": self.color,
            "value": self.value
        }

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

    def to_dict(self, reveal_hand: bool = False) -> Dict[str, Any]:
        """转换为字典，用于API返回。reveal_hand控制是否暴露手牌。"""
        return {
            "id": self.id,
            "name": self.name,
            "stack": self.stack,
            "bet": self.bet,
            "status": self.status,
            "hand": [card.to_dict() for card in self.hand] if reveal_hand else []
        }

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
        self._create_deck()

    def _create_deck(self) -> None:
        """创建一副52张牌"""
        self.deck = [Card(suit, rank) for suit in Suit for rank in Rank]
        random.shuffle(self.deck)

    def add_player(self, name: str) -> Player:
        """添加玩家"""
        player_id = len(self.players)
        player = Player(name, player_id)
        self.players.append(player)
        return player

    def start_new_hand(self) -> None:
        """开始新的一手牌"""
        if len(self.players) < 2:
            raise ValueError("至少需要2名玩家才能开始游戏")
        # 重置状态
        self.community_cards = []
        self.pot = 0
        self.current_bet = 0
        self.betting_round_complete = False
        self._create_deck()
        for player in self.players:
            player.hand = []
            player.bet = 0
            player.status = "active"
            player.has_acted = False
        # 发手牌
        for _ in range(2):
            for player in self.players:
                player.hand.append(self.deck.pop())
        # 确定庄家和小盲、大盲位置
        self.dealer_position = (self.dealer_position + 1) % len(self.players)
        sb_index = (self.dealer_position + 1) % len(self.players)
        bb_index = (self.dealer_position + 2) % len(self.players)
        # 收取盲注
        self._place_bet(self.players[sb_index], self.small_blind)
        self._place_bet(self.players[bb_index], self.big_blind)
        self.current_bet = self.big_blind
        # 设置行动玩家（大盲位下一位）
        self.active_player_index = (bb_index + 1) % len(self.players)
        self.game_state = "preflop"

    def _place_bet(self, player: Player, amount: int) -> bool:
        """玩家下注。返回是否成功。"""
        actual_amount = min(amount, player.stack)
        player.stack -= actual_amount
        player.bet += actual_amount
        self.pot += actual_amount
        if player.stack == 0 and actual_amount > 0:
            player.status = "all_in"
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
        elif self.game_state == "flop":
            # 发转牌
            self._burn_card()
            self.community_cards.append(self.deck.pop())
            self.game_state = "turn"
        elif self.game_state == "turn":
            # 发河牌
            self._burn_card()
            self.community_cards.append(self.deck.pop())
            self.game_state = "river"
        elif self.game_state == "river":
            self.game_state = "showdown"
            self._determine_winner()
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
        # 条件1: 所有未弃牌/全下的玩家都已行动
        # 条件2: 所有未弃牌/全下的玩家下注额相等
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
            return {"success": False, "message": "玩家不能行动"}
        if player_id != self.active_player_index:
            return {"success": False, "message": "不是该玩家的回合"}

        message = ""
        if action == "fold":
            player.status = "folded"
            message = f"{player.name} 弃牌了。"

        elif action == "check":
            if player.bet < self.current_bet:
                return {"success": False, "message": "不能过牌，必须跟注或加注"}
            message = f"{player.name} 过牌。"

        elif action == "call":
            call_amount = self.current_bet - player.bet
            if call_amount > player.stack:
                call_amount = player.stack
            self._place_bet(player, call_amount)
            message = f"{player.name} 跟注 {call_amount}。"

        elif action == "bet":
            if amount <= 0:
                return {"success": False, "message": "下注额必须为正数"}
            if amount <= self.current_bet:
                return {"success": False, "message": "加注额必须大于当前下注额"}
            if amount > player.stack:
                return {"success": False, "message": "筹码不足"}
            self._place_bet(player, amount - player.bet)
            self.current_bet = amount
            message = f"{player.name} 下注 {amount}。"

        else:
            return {"success": False, "message": f"未知动作: {action}"}

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

        return {"success": True, "message": message}

    def _determine_winner(self) -> None:
        """简易的胜者判断（仅比较手牌类型，不处理分池）"""
        active_players = [p for p in self.players if p.status != "folded"]
        if not active_players:
            return
        if len(active_players) == 1:
            winner = active_players[0]
            winner.stack += self.pot
            self.pot = 0
            self.game_state = "ended"
            return
        # 此处应实现完整的扑克手牌排名逻辑。
        # 为简化，我们随机选择一个赢家。
        import random
        winner = random.choice(active_players)
        winner.stack += self.pot
        self.pot = 0
        self.game_state = "ended"

    def get_state(self, for_player_id: Optional[int] = None) -> Dict[str, Any]:
        """获取游戏状态。for_player_id用于决定向哪个玩家显示手牌。"""
        reveal_hand_to_all = (self.game_state == "showdown" or self.game_state == "ended")
        players_data = []
        for i, player in enumerate(self.players):
            reveal = (reveal_hand_to_all or i == for_player_id)
            players_data.append(player.to_dict(reveal_hand=reveal))
        return {
            "game_state": self.game_state,
            "pot": self.pot,
            "current_bet": self.current_bet,
            "dealer_position": self.dealer_position,
            "active_player_index": self.active_player_index,
            "community_cards": [card.to_dict() for card in self.community_cards],
            "players": players_data
        }

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
            "players": [p.name for p in game.players]
        })
    except Exception as e:
        return jsonify({"success": False, "error": str(e)}), 400

@app.route('/api/game/action', methods=['POST'])
def player_action():
    """玩家执行动作"""
    data = request.get_json()
    if not data:
        return jsonify({"success": False, "error": "需要JSON数据"}), 400
    action = data.get('action')
    amount = data.get('amount', 0)
    # 在真实应用中，这里需要身份验证。此处我们假设是当前行动玩家在操作。
    try:
        result = game.player_action(game.active_player_index, action, amount)
        return jsonify(result)
    except Exception as e:
        return jsonify({"success": False, "error": str(e)}), 400

@app.route('/api/reset', methods=['POST'])
def reset_game():
    """重置游戏（用于调试）"""
    global game
    game = PokerGame()
    game.add_player("玩家A")
    game.add_player("玩家B")
    game.add_player("玩家C")
    return jsonify({"success": True, "message": "游戏已重置"})

# ========== 主程序 ==========
if __name__ == '__main__':
    print("德州扑克后端服务器启动...")
    print("前端界面预计运行在: http://127.0.0.1:5000")
    print("API基础URL: http://127.0.0.1:5000/api")
    app.run(debug=True, port=5000)
