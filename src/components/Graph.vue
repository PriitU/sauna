<template>
  <div>
    <apexchart width=100% type="area" :options="options" :series="series"></apexchart>
  </div>
</template>

<script>
import axios from 'axios';

  export default {
    name: 'Graph',
    data() {
      return {
        options: {
          chart: {
            id: 'sauna'
          },
          xaxis: {
            type: 'datetime',
          }
        },
        series: [
          {
            name: 'Sauna',
            data: [[1589278068000,30],
                  [1590278068000,40],
                  [1591278068000,45],
                  [1592278068000,50],
                  [1593278068000,49],
                  [1594278068000,60],
                  [1595278068000,70],
                  [1596278068000,91]]
          },{
            name: 'Air',
            data: [[1589278068000,14],
                  [1590278068000,15],
                  [1591278068000,14],
                  [1592278068000,18],
                  [1593278068000,21],
                  [1594278068000,22],
                  [1595278068000,25],
                  [1596278068000,20]]
          },{
            name: 'Water',
            data: [[1589278068000,10],
                  [1590278068000,12],
                  [1591278068000,15],
                  [1592278068000,14],
                  [1593278068000,19],
                  [1594278068000,20],
                  [1595278068000,18],
                  [1596278068000,19]]
          }
        ]
      }
    },
    created() {
      axios.get(process.env.VUE_APP_ROOT_API + '/dev/saun-test')
        .then(res => {
          this.data = res.data;
          const saunaData = res.data.map(s => {return {'x': s.timestamp, 'y': s.sauna}});
          const airData = res.data.map(s => {return {'x': s.timestamp, 'y': s.air}});
          const waterData = res.data.map(s => {return {'x': s.timestamp, 'y': s.water}});
          const humidityData = res.data.map(s => {return {'x': s.timestamp, 'y': s.humidity}});
          const uvData = res.data.map(s => {return {'x': s.timestamp, 'y': s.uv}});
          const airPressureData = res.data.map(s => {return {'x': s.timestamp, 'y': s.airPressure}});
          console.log(saunaData);
          console.log(airData);
          console.log(waterData);
          console.log(humidityData);
          console.log(uvData);
          console.log(airPressureData);
          //this.series = [{
          //  data: res.data.sauna
          //}]
        })
        .catch(err => console.log(err));
    }
  }
</script>

<style scoped>

</style>
