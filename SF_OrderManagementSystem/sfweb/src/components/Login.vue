<template>
<div>
    <div v-if="loading" class="progress">
        <div class="indeterminate"></div>
    </div>   
    <div class="login">
        <div class="valign-wrapper row login-box">
            <div class="col card hoverable s10 pull-s1 m6 pull-m3 l4 pull-l4">
                <form @submit.prevent="loginUser">
                    <div class="card-content">
                        <span class="card-title">Login to Admin Dashboard</span>
                        <div class="row">
                        <div class="input-field col s12">
                            <label v-if="!email" for="text">User ID</label>
                            <input type="text" name="uid" v-model="email" />
                        </div>
                        <div class="input-field col s12">
                            <label v-if="!password" for="password">Password </label>
                            <input type="password" name="pwd" v-model="password" />
                        </div>
                        <p class="red-text" v-if="feedback">{{feedback}}</p>
                        </div>
                    </div>
                    
                    <div class="card-action right-align">
                        <input type="reset" @click="reset" class="btn-flat grey-text waves-effect">
                        <input type="submit" class="btn teal waves-effect waves-light" value="Login">
                    </div>
                </form>
            </div>
        </div>
    </div>
</div>
</template>

<script>
import firebase from 'firebase'
export default {
    name: 'Login',
    data(){
        return{
            email: "",
            password: "",
            feedback: null,
            loading:false
        }
    },
    methods:{
        loginUser(){
            
            this.feedback=null
            let re = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
            if(re.test(String(this.email).toLowerCase()) && this.password.length>=8 && this.email.length>4){
                this.loading=true
                firebase.auth().signInWithEmailAndPassword(this.email,this.password).then(cred =>{
                    this.loading=false;
                    this.$router.push({name: 'Dashboard'})

                }).catch(err=>{
                    this.feedback=err.message
                    this.loading=false;
                })

            }
            else if(this.password.length<8){
                this.feedback="Password must be 8 characters long"
            }
            else{
                this.feedback="Email Address is not valid"
            }
        },
        reset(){
            this.email= ""
            this.password=""
        }
    },
    created(){
        firebase.auth().onAuthStateChanged(cred=>{
            if(cred){
                this.$router.push({name : 'Dashboard'})
            }
        })
    }
}
</script>

<style>
.login{
    margin-top:100px;
}
.login .label{
    padding:10px;
}
</style>
