<template>
  <div id="app">
    <Header />
    <Stats  v-bind:series="series"/>
    <Graph :options="options" :series="series" />
  </div>
</template>

<script>
import axios from 'axios';
import Header from './components/layout/Header';
import Graph from './components/Graph';
import Stats from './components/Stats';
// import json from '../data.json';

export default {
  name: 'App',
  components: {
    Header,
    Stats,
    Graph
  },
  data() {
    return {
      options: {
        chart: {
          id: 'sauna',
          zoom: {
            autoScaleYaxis: true
          }
        },
        stroke: {
          show: true,
          curve: 'smooth',
          lineCap: 'butt',
          colors: undefined,
          width: 2,
          dashArray: 0,
        },
        colors: ['#FCBA03','#00E396','#008FFB'],
        xaxis: {
          type: 'datetime',
          tickAmount: 6
        },
        dataLabels: {
          enabled: false
        },
        legend: {
          position: 'top',
          horizontalAlign: 'left'
        },
        tooltip: {
          x: {
            format: 'dd MMM yyyy HH:mm:ss'
          }
        }
      },
      series: [
        {
          name: 'Sauna',
          data: []
        },{
          name: 'Air',
          data: []
        },{
          name: 'Water',
          data: []
        }
      ]
    }
  },
  created() {
    // this.series = [{
    //   name: 'Sauna',
    //   data: json.map(s => {return {'x': s.timestamp, 'y': s.sauna}})
    // },{
    //   name: 'Air',
    //   data: json.map(s => {return {'x': s.timestamp, 'y': s.air}})
    // },{
    //   name: 'Water',
    //   data: json.map(s => {return {'x': s.timestamp, 'y': s.water}})
    // }]
    // Commented out due to static data being used (data.json)
    axios.get(process.env.VUE_APP_ROOT_API)
      .then(res => {
        const saunaData = res.data.map(s => {return {'x': s.timestamp, 'y': s.sauna}});
        const airData = res.data.map(s => {return {'x': s.timestamp, 'y': s.air}});
        const waterData = res.data.map(s => {return {'x': s.timestamp, 'y': s.water}});
        //const humidityData = res.data.map(s => {return {'x': s.timestamp, 'y': s.humidity}});
        //const uvData = res.data.map(s => {return {'x': s.timestamp, 'y': s.uv}});
        //const airPressureData = res.data.map(s => {return {'x': s.timestamp, 'y': s.airPressure}});
        //console.log(saunaData);
        //console.log(airData);
        //console.log(waterData);
        //console.log(humidityData);
        //console.log(uvData);
        //console.log(airPressureData);
        this.series = [{
          data: saunaData,
          latest : saunaData.slice(-1)[0].y
        },{
          data: airData,
          latest : airData.slice(-1)[0].y
        },{
          data: waterData,
          latest : waterData.slice(-1)[0].y
        }]
      })
      .catch(err => console.log(err));
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}
</style>
