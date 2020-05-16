<template>
    <header class="header">
        <h1>Saun</h1>
        <Datepicker />
    </header>
</template>

<script>
    import Datepicker from '../Datepicker';
    export default {
        name: "Header",
        components: {
            Datepicker
        }
    }
</script>

<style scoped>
    h1 {
        margin: 5px;
    }

    .header {
        background: #333;
        color: #fff;
        text-align: center;
        padding: 10px;
    }

    .header a {
        color: #fff;
        padding-right: 5px;
    }
</style>