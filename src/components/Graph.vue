<template>
  <div>
    <apexchart width=100% type="area" :options=options :series=series></apexchart>
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
