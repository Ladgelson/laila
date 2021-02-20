<template>
  <div id="app">
    <h1>LAILA - Lexical And sIntaticaL Analyser online</h1>
    <hr />
    <Painel/>
    <button v-on:click="addCode" type="submit" class="btn btn-primary">Enviar</button>
  </div>
</template>

<script>
import Painel from './components/Painel.vue'

export default {
  name: 'App',
  components: {
    Painel
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
