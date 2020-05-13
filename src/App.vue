<template>
  <div id="app">
    <Header />
    <Graph />
  </div>
</template>

<script>
import Header from './components/layout/Header';
import Graph from './components/Graph';
import axios from 'axios';

export default {
  name: 'App',
  components: {
    Header,
    Graph
  },
  created() {
    console.log(process.env.VUE_APP_ROOT_API)
    axios.get(process.env.VUE_APP_ROOT_API + '/dev/saun-test')
      .then(res => {
        this.data = res.data;
        console.log(this.data);
        })
      .catch(err => console.log(err));
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
}
</style>
