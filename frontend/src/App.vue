<template>
  <div id="app">
    <GameView />
  </div>
</template>

<script>
import GameView from './views/GameView.vue'

export default {
  name: 'App',
  components: {
    GameView
  }
}
</script>

<style>
#app {
  width: 100%;
  height: 100%;
}
</style>
