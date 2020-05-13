<template>
  <div id="app">
    <Header />
    <Graph />
  </div>
</template>

<script>
import Header from './components/layout/Header';
import Graph from './components/Graph';

export default {
  name: 'App',
  components: {
    Header,
    Graph
  },
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}
</style>
