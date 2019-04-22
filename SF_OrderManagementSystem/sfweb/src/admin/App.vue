<template>
  <div id="app">
    <Navbar /> 
    <router-view/>
  </div>
</template>

<script>
import Navbar from '@/components/Navbar'
import firebase from 'firebase/app'
import db from '@/firebase/init'
import { mapMutations } from 'vuex'

export default {
  name: 'App',
  components:{
    Navbar
  },
  methods:{
    ...mapMutations(['UPDATE_STATUS_OPTIONS'])
  },
  created(){
    db.collection('statusOptions').get().then((snap)=>{
      let statusOptions = []
      snap.forEach(doc=>{
        statusOptions.push(doc.data().name)
      })
      this.UPDATE_STATUS_OPTIONS(statusOptions)
    }).catch(err=>{
      console.log(err)
    })
  }
}
</script>

<style>

</style>