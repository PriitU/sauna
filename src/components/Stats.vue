<template>
  <div>
    <v-card class="my-1">
      <h3>Last update <small>({{ series[0].timeFromUpdate }} min ago)</small>:<br />{{series[0].latestUpdateTime.toLocaleString()}}</h3>

      <h3>Sauna: {{ series[0].latest }} C</h3>
      <h3>Air: {{ series[1].latest }} C</h3>
      <h3>Water: {{ series[2].latest }} C</h3>
    </v-card>
  </div>
</template>

<script>

  export default {
    name: 'Stats',
    props: ['series']
  }
</script>

<style scoped>
</style>
