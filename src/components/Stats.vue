<template>
  <div>
    <v-card class="my-1">
      <h3>Last update: {{series[0].latestUpdateTime}}</h3>
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
