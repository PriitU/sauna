<template>
  <v-app>
    <v-app-bar app color="primary" dark>
      <div class="d-flex align-center">
        <v-img
          alt="Vuetify Logo"
          class="shrink mr-2"
          contain
          src="https://cdn.vuetifyjs.com/images/logos/vuetify-logo-dark.png"
          transition="scale-transition"
          width="40"
        />
      </div>

      <v-spacer></v-spacer>

      <v-btn
        href="https://github.com/priitu"
        target="_blank"
        text
      >
        <span class="mr-2">Github</span>
        <v-icon>mdi-open-in-new</v-icon>
      </v-btn>
    </v-app-bar>
    <v-content>
    <v-container>
      <v-layout row justify-center>
        <!--<v-flex xs6 md4>
          <Datepicker  v-bind:series="series"/>
        </v-flex>-->
        <v-flex xs7 md4>
          <Stats  v-bind:series="series"/>
        </v-flex>
        <v-flex xs11 md8>
          <Graph :options="options" :series="series" />
        </v-flex>
      </v-layout>
    </v-container>
  </v-content>
    <v-footer app>
      <span>&copy; 2020</span>
    </v-footer>
  </v-app>
</template>

<script>
import axios from 'axios';
import Graph from './components/Graph';
import Stats from './components/Stats';
// import Datepicker from './components/Datepicker';
// import json from '../data.json';
export default {
  name: 'App',
  components: {
    // Datepicker,
    Stats,
    Graph
  },
  data() {
    return {
      options: {
        chart: {
          id: 'sauna',
          background: '#fff',
          zoom: {
            autoScaleYaxis: true
          },
          parentHeightOffset: 0
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
    //   data: json.map(s => {return {'x': s.timestamp, 'y': s.sauna}}),
    //   latest : json[json.length-1].sauna,
    //   latestUpdateTime : new Date(json[json.length-1].timestamp).toLocaleString('en-GB', { timeZone: 'UTC' })
    // },{
    //   name: 'Air',
    //   data: json.map(s => {return {'x': s.timestamp, 'y': s.air}}),
    //   latest : json[json.length-1].air
    // },{
    //   name: 'Water',
    //   data: json.map(s => {return {'x': s.timestamp, 'y': s.water}}),
    //   latest : json[json.length-1].water
    // }]
    // Commented out due to static data being used (data.json)
    axios.get(process.env.VUE_APP_ROOT_API)
      .then(res => {
        const saunaData = res.data.map(s => {return {'x': s.timestamp, 'y': s.sauna}});
        const airData = res.data.map(s => {return {'x': s.timestamp, 'y': s.air}});
        const waterData = res.data.map(s => {return {'x': s.timestamp, 'y': s.water}});
        const lastUpdate = new Date(saunaData.slice(-1)[0].x)//.toLocaleString('en-GB', { timeZone: 'UTC' })
        const currentTime = new Date()//.toLocaleString('en-GB', { timeZone: 'UTC' })
        const timeFromUpdate = Math.round((currentTime.getTime()-lastUpdate.getTime())/1000/60)
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
          latest : saunaData.slice(-1)[0].y,
          latestUpdateTime : lastUpdate,
          timeFromUpdate : timeFromUpdate
        },{
          data: airData,
          latest : airData.slice(-1)[0].y,
        },{
          data: waterData,
          latest : waterData.slice(-1)[0].y,
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
