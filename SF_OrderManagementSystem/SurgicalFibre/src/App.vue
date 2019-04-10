<template>
  <div id="app">
    <Navbar /> 
    <router-view/>
  </div>
</template>

<script>
import Navbar from '@/components/ProductsManagement/Navbar'
import firebase from 'firebase'
export default {
  name: 'App',
  components:{
    Navbar
  },
}
</script>

<style>

</style>
