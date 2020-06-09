<template>
  <div class="center">
    <apexchart type="area" :options=options :series=series></apexchart>
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
    padding: 10px;
    background: #f5f5f5;
  }
</style>
