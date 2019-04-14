<template>
  <div id="app">
    <Navbar /> 
    <router-view/>
  </div>
</template>

<script>
import Navbar from '@/components/Navbar'
import firebase from 'firebase/app'

export default {
  name: 'App',
  components:{
    Navbar
  },
}
</script>

<style>

</style>