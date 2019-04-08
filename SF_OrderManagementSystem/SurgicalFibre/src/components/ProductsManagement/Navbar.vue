<template>
     <div class="navbar">
         <nav class="nav-extended deep-purple darken-1">
             <div class="container">
                <router-link :to="{name:'Index'}">Surgical Fibre Admin Portal</router-link>
                <ul class="right">
                    <li v-if="!user"><router-link :to="{name:'Login'}">Login</router-link></li>
                    <li v-if="user"><router-link :to="{name:'ProductsIndex'}">Products</router-link></li>
                    <li v-if="user"><router-link :to="{name:'Dashboard'}">Dashboard</router-link></li>
                    <!-- <li v-if="user"><router-link :to="{name:'Orders'}">Orders</router-link></li> -->
                    <li v-if="user"><a @click="logout">Logout</a></li>

                </ul>
             </div>
         </nav>
     </div>
     
</template>

<script>
import firebase from 'firebase'
export default {
    name: 'Navbar',
    data(){
        return{
            user: null 
        }
    },
    methods:{
        logout(){
            if(confirm('Are you sure you want to logout?')){
                firebase.auth().signOut().then(()=>{
                    this.$router.push({name:'Login'})
                })
            }
        }
    },
    created(){
        firebase.auth().onAuthStateChanged(cred=>{
            if(cred){
                this.user = cred
            }else{
                this.user = null
            }
            
        })
    }
}
</script>

<style>
.navbar nav{
    padding: 0 20px; 
}
</style>
