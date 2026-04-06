<template>
  <div class="container">
    <div class="game-header">
      <div class="header-controls">
        <button id="btn-start" @click="startNewGame" :disabled="isGameActive">开始新游戏</button>
        <button id="btn-reset" @click="resetServer">重置服务器</button>
      </div>
      <h1>♠️ ♥️ 德州扑克 ♣️ ♦️</h1>
    </div>

    <div class="game-layout">
      <div class="poker-table">
        <!-- 获胜信息 -->
        <div v-if="showWinners" class="winners-section">
          <h2>🏆 获胜者 🏆</h2>
          <div id="winners-list">
            <div v-for="winner in winners" :key="winner.player_id" 
                 style="padding: 10px; margin: 5px 0; background-color: rgba(255, 215, 0, 0.2); border-radius: 5px;">
              <strong>{{ winner.player_name }}</strong> 赢得 <span style="color: #FFD700">{{ winner.amount }}</span> 筹码
              <span v-if="winner.hand_description" style="font-size: 0.9em; color: #66ccff">
                <br>{{ winner.hand_description }}
              </span>
            </div>
          </div>
        </div>

        <!-- 荷官区域 -->
        <div class="dealer-area">
          <div class="dealer-label">荷官</div>
          <div class="dealer-game-info">
            <div class="dealer-info-item">
              <span class="dealer-info-label">游戏状态</span>
              <span class="dealer-info-value">{{ gameState }}</span>
            </div>
            <div class="dealer-info-item">
              <span class="dealer-info-label">当前底池</span>
              <span class="dealer-info-value">{{ pot }}</span>
            </div>
            <div class="dealer-info-item">
              <span class="dealer-info-label">下注额</span>
              <span class="dealer-info-value">{{ currentBet }}</span>
            </div>
            <div class="dealer-info-item">
              <span class="dealer-info-label">行动玩家</span>
              <span class="dealer-info-value">{{ activePlayerName }}</span>
            </div>
          </div>
        </div>

        <!-- 公共牌区域 -->
        <div class="community-cards-area">
          <div class="community-cards">
            <div v-for="(card, index) in communityCards" :key="index"
                 :class="['card', card.color]">
              {{ card.symbol }}
            </div>
            <div v-for="i in placeholderCardsCount" :key="`placeholder-${i}`"
                 class="card placeholder">
              ?
            </div>
          </div>
        </div>

        <!-- 玩家座位 -->
        <div v-for="(player, index) in players" :key="player.id"
             :id="`seat-${index}`"
             :class="['player-seat', `seat-${index}`, 
                      { active: index === activePlayerIndex },
                      { winner: isWinner(player.id) },
                      { human: index === 0 },
                      { robot: index !== 0 }]">
          <div :class="['player-name', index === 0 ? 'player-human' : 'player-robot']">
            {{ player.name }} {{ getPositionLabel(index) }}
          </div>
          <div class="player-info-line">筹码: {{ player.stack }}</div>
          <div class="player-info-line">下注: {{ player.bet }}</div>
          <div class="player-hand">{{ getHandDisplay(player, index) }}</div>
          <div class="player-status">{{ player.status }}</div>
          <div v-if="player.hand_rank && isHandRevealed(player, index)" 
               class="player-hand-rank">
            {{ player.hand_description }}
          </div>
        </div>

        <!-- 用户操作面板 -->
        <div v-if="isHumanPlayerTurn" class="player-action-panel">
          <div class="action-buttons">
            <button id="btn-fold" @click="takeAction('fold')" :disabled="!canAct">弃牌</button>
            <button id="btn-check" @click="takeAction('check')" :disabled="!canAct">过牌</button>
            <button id="btn-call" @click="takeAction('call')" :disabled="!canAct">跟注</button>
            <button id="btn-bet" @click="showBetInput" :disabled="!canAct">下注</button>
            <button id="btn-raise" @click="showBetInput" :disabled="!canAct">加注</button>
          </div>
          <div v-if="showBetControls" class="bet-input-section">
            <label for="bet-amount">下注/加注额度:</label>
            <input type="number" id="bet-amount" v-model="betAmount" min="1" value="20">
            <button id="btn-confirm-bet" @click="confirmBetAction">确认下注</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import axios from 'axios'

const API_BASE_URL = '/api'

export default {
  name: 'GameView',
  data() {
    return {
      gameState: '等待游戏开始',
      pot: 0,
      currentBet: 0,
      activePlayerIndex: 0,
      communityCards: [],
      players: [],
      winners: [],
      showBetControls: false,
      betAmount: 20,
      updateInterval: null
    }
  },
  computed: {
    activePlayerName() {
      const player = this.players[this.activePlayerIndex]
      return player ? player.name : '-'
    },
    isGameActive() {
      return this.gameState !== 'idle' && this.gameState !== 'ended' && this.gameState !== 'showdown'
    },
    canAct() {
      return this.isGameActive && this.isHumanPlayerTurn
    },
    isHumanPlayerTurn() {
      const activePlayer = this.players[this.activePlayerIndex]
      return activePlayer && activePlayer.status === 'active' && this.activePlayerIndex === 0
    },
    placeholderCardsCount() {
      return Math.max(0, 5 - this.communityCards.length)
    },
    showWinners() {
      return this.winners && this.winners.length > 0
    }
  },
  methods: {
    async callApi(endpoint, method = 'GET', body = null) {
      const options = { method, headers: { 'Content-Type': 'application/json' } }
      if (body) options.body = JSON.stringify(body)
      
      try {
        const response = await axios({
          method: method.toLowerCase(),
          url: `${API_BASE_URL}${endpoint}`,
          data: body,
          headers: { 'Content-Type': 'application/json' }
        })
        return response.data
      } catch (error) {
        console.error(`API调用失败: ${error.message}`)
        return null
      }
    },
    
    async updateGameState() {
      const data = await this.callApi('/game/state?player_id=0')
      if (!data) return
      
      this.renderGameState(data)
      
      // 如果是机器人的回合，自动执行动作
      const activePlayerIndex = data.active_player_index
      if (activePlayerIndex > 0 && data.game_state !== 'ended' && data.game_state !== 'showdown') {
        const activePlayer = data.players[activePlayerIndex]
        if (activePlayer && activePlayer.status === 'active') {
          setTimeout(() => this.robotAI(activePlayerIndex, data), 1000)
        }
      }
    },
    
    renderGameState(state) {
      this.gameState = state.game_state
      this.pot = state.pot
      this.currentBet = state.current_bet
      this.activePlayerIndex = state.active_player_index
      this.communityCards = state.community_cards
      this.players = state.players
      
      if (state.winners && state.winners.length > 0) {
        this.winners = state.winners
      } else {
        this.winners = []
      }
    },
    
    getPositionLabel(index) {
      return index === 0 ? '(你)' : 
             index === 1 ? '(机器人-左)' :
             '(机器人-右，庄家)'
    },
    
    getHandDisplay(player, index) {
      if (!player.hand || player.hand.length === 0) return '??'
      
      const isShowdown = this.gameState === 'showdown' || this.gameState === 'ended'
      if (isShowdown || index === 0) {
        return player.hand.map(c => c.symbol).join(' ')
      }
      return '??'
    },
    
    isHandRevealed(player, index) {
      return (this.gameState === 'showdown' || this.gameState === 'ended' || index === 0) && 
             player.hand && player.hand.length > 0
    },
    
    isWinner(playerId) {
      return this.winners.some(w => w.player_id === playerId)
    },
    
    async startNewGame() {
      console.log('请求开始新游戏...')
      const data = await this.callApi('/game/start', 'POST')
      if (data) {
        console.log(`新游戏开始！玩家: ${data.players.join(', ')}`)
        this.updateGameState()
      }
    },
    
    async takeAction(action) {
      console.log(`执行动作: ${action}`)
      const data = await this.callApi('/game/action', 'POST', { action })
      if (data) {
        if (data.success) {
          console.log(`动作"${action}"成功。${data.message}`)
        } else {
          console.error(`动作失败: ${data.message}`)
        }
        this.updateGameState()
      }
    },
    
    showBetInput() {
      this.showBetControls = true
      console.log('请输入下注/加注额度。')
    },
    
    async confirmBetAction() {
      const amount = parseInt(this.betAmount)
      if (isNaN(amount) || amount <= 0) {
        console.error('请输入有效的正数金额。')
        return
      }
      console.log(`执行下注/加注: ${amount}`)
      const data = await this.callApi('/game/action', 'POST', { action: 'bet', amount })
      if (data) {
        if (data.success) {
          console.log(`下注"${amount}"成功。${data.message}`)
        } else {
          console.error(`下注失败: ${data.message}`)
        }
        this.showBetControls = false
        this.updateGameState()
      }
    },
    
    async resetServer() {
      const confirmed = confirm('这将重置后端所有游戏数据。确定吗？')
      if (!confirmed) return
      
      console.log('重置服务器...')
      const data = await this.callApi('/reset', 'POST')
      if (data) {
        console.log('服务器已重置。')
        this.winners = []
        this.updateGameState()
      }
    },
    
    calculateHandStrength(player, state) {
      if (!player.hand || player.hand.length < 2) return 0
      
      const card1 = player.hand[0]
      const card2 = player.hand[1]
      
      let strength = 0
      
      // 对子
      if (card1.value === card2.value) strength += 0.3
      
      // 同花
      if (card1.suit === card2.suit) strength += 0.2
      
      // 高牌
      strength += (Math.max(card1.value, card2.value) - 2) * 0.02
      
      // 连牌潜力
      const gap = Math.abs(card1.value - card2.value)
      if (gap <= 1) strength += 0.2
      else if (gap <= 2) strength += 0.1
      
      return Math.min(strength, 1)
    },
    
    async robotAI(playerIndex, state) {
      const player = state.players[playerIndex]
      if (!player || player.status !== 'active') return
      
      // 等待一段时间让玩家看到机器人思考
      await new Promise(resolve => setTimeout(resolve, 1500))
      
      // 简单的AI策略
      const callAmount = state.current_bet - player.bet
      const canCall = callAmount <= player.stack
      
      const handStrength = this.calculateHandStrength(player, state)
      const randomFactor = Math.random()
      
      let action = 'fold'
      let amount = 0
      
      if (handStrength > 0.7) {
        // 强牌：加注或跟注
        if (randomFactor < 0.7 && player.stack > state.current_bet * 2) {
          action = 'bet'
          amount = Math.min(player.stack, Math.max(state.current_bet * 2, 50))
        } else if (canCall) {
          action = 'call'
        } else {
          action = 'fold'
        }
      } else if (handStrength > 0.4) {
        // 中等牌：跟注或过牌
        if (state.current_bet === player.bet) {
          action = 'check'
        } else if (canCall) {
          action = 'call'
        } else {
          action = 'fold'
        }
      } else {
        // 弱牌：弃牌或过牌
        if (state.current_bet === player.bet) {
          action = 'check'
        } else if (callAmount <= player.stack * 0.1) {
          action = 'call'
        } else {
          action = 'fold'
        }
      }
      
      console.log(`机器人 ${player.name} 执行动作: ${action}${amount > 0 ? ' ' + amount : ''}`)
      
      const data = await this.callApi('/game/action', 'POST', { action, amount })
      if (data && data.success) {
        console.log(`机器人 ${player.name} ${action} 成功`)
      }
    }
  },
  mounted() {
    this.updateGameState()
    this.updateInterval = setInterval(() => {
      this.updateGameState()
    }, 3000)
  },
  beforeUnmount() {
    if (this.updateInterval) {
      clearInterval(this.updateInterval)
    }
  }
}
</script>

<style scoped>
</style>
