<template>
  <div>
    <apexchart width=100% type="area" :options="options" :series="series"></apexchart>
  </div>
</template>

<script>
import axios from 'axios';

  export default {
    name: 'Graph',
    data: function() {
      return {
        options: {
          chart: {
            id: 'sauna'
          },
          xaxis: {
            type: 'datetime',
          }
        },
        series: [{
          name: 'Sauna',
          data: [/*[1589278068000,30],
                [1590278068000,40],
                [1591278068000,45],
                [1592278068000,50],
                [1593278068000,49],
                [1594278068000,60],
                [1595278068000,70],
                [1596278068000,91]*/]
        }]
      }
    },
    created() {
      axios.get(process.env.VUE_APP_ROOT_API + '/dev/saun-test')
        .then(res => {
          //this.data = res.data;
          this.series = [{
            data: res.data.sauna
          }]
        })
        .catch(err => console.log(err));
    }
  }
</script>

<style scoped>

</style>
