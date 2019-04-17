<template>
  <div id="client">
    <Navbar /> 
    <router-view/>
    <Footer/>
  </div>
</template>

<script>
import Navbar from '@/components/Client/Navbar'
import Footer from '@/components/Client/Footer'
import db from '@/firebase/init'

export default {
  name: 'App',
  components:{
    Navbar,
    Footer
  },
  data(){
    return {
    }
  },
 
}
</script>

<style>

</style>