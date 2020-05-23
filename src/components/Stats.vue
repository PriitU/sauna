<template>
  <div>
    <h2>Sauna: {{ series[0].latest }} C</h2>
    <h2>Air: {{ series[1].latest }} C</h2>
    <h2>Water: {{ series[2].latest }} C</h2>
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
