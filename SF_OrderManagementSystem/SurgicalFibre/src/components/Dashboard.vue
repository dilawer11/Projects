<template>
    <div class="dashboard">
        <h2 class="center-align">Dashboard</h2>
        <router-link class="center-align" :to="{name: 'ProductsIndex'}">Products</router-link>
    </div>
</template>

<script>
export default {
    name: 'Dashboard',
    data(){
        return{

        }
    }
}
</script>

<style>

</style>
