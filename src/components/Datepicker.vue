
<template>
<v-card class="mx-1 my-1" justify="center" height="100%">
  <v-date-picker v-model="picker"></v-date-picker>
</v-card>
</template>

<script>
export default {
  data () {
    return {
      picker: new Date().toISOString().substr(0, 10),
    }
  },
}
</script>

<style scoped>

</style>
