<template>
  <div>
    <v-card class="mx-auto mt-3 center">
      <h2>Last update: {{series[0].latestUpdateTime}}</h2>
      <h2>Sauna: {{ series[0].latest }} C</h2>
      <h2>Air: {{ series[1].latest }} C</h2>
      <h2>Water: {{ series[2].latest }} C</h2>
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
.center {
  width: 90%;
}
</style>
