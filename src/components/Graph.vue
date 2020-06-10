<template>
  <div class="mx-auto my-2 center">
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
  .center {
    margin: auto;
    width: 90%;
  }
</style>
