<template>
  <div class="my-1">
    <v-card :elevation=3>
      <apexchart type="area" :options=options :series=series></apexchart>
    </v-card>
  </div>
</template>

<script>

  export default {
    name: 'Graph',
    props: {
      options : Object,
      series: Array
    }
  }
</script>

<style scoped>
</style>
