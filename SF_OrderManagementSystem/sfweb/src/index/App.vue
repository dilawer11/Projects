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
import currencyConverter from '@/firebase/currencyConverter'
const axios = require('axios')

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
  methods:{
    
  },
  created(){
    let request = 'https://free.currconv.com/api/v7/convert?q=PKR_USD&compact=ultra&apiKey=' + currencyConverter.apiKey
    axios.get(request).then(response=>{
      console.log(response.data.PKR_USD)
    }).catch(err=>{
      console.log(err)
    })
  }
 
}
</script>

<style>

</style>