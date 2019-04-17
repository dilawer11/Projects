<template>
    <div id="query">
        <section class="testimonials padding-top-90 padding-bottom-90" id="testimonials">         
            <div class="container">
                <h1>Contact Us</h1>
            </div>
        </section>
         <!--Start Portfolio Section-->
                <section class="portfolio padding-top-90 padding-bottom-60 primary_bg" id="portfolio">
                     <h2 class="center-align black-text">Query Form</h2>
    
    <div class="container">
    <div class="divider"></div>
    <br><br>
    <br><br>
    <form class="col s12">
        <div class="row">
            <div class="input-field col s12 m6">
                <i class="material-icons prefix">account_circle</i>
                <input v-model="firstname" id="first_name" type="text">
                <label class="active grey-text" for="first_name">First Name</label>
            </div>
            <div class="input-field col s12 m6">
                <i class="material-icons prefix">account_circle</i>
                <input v-model="lastname" id="last_name" type="text" >
                <label class="active grey-text" for="last_name">Last Name</label>
            </div>
        </div>
        <div class="row">
            <div class="input-field col s12 m6">
                <i class="material-icons prefix">email</i>
                <input v-model="email" id="email" type="email">
                <label class="active grey-text" for="email">Email </label>
            </div>
            <div class="input-field col s12 m6">
                <i class="material-icons prefix">phone</i>
                <input v-model="phone" id="phone" type="tel" placeholder="+12-123-1234567">
                <label class="active grey-text" for="phone">Phone</label>
            </div>
        </div>
  
        <div class="row">
            <div class="input-field col s12 m12">
            <i class="material-icons prefix">mode_edit</i>
            <textarea  v-model="message" id="message" class="materialize-textarea grey-text" data-length=250></textarea>
            <label class="active grey-text" for="message">Message</label>
            </div>
        </div>
        <button @click="sendQuery" class="btn waves-effect waves-light grey">
            Send
            <i class="material-icons right">send</i>
        </button> 
    </form>
  </div>
                </section>
                <!--End Portfolio Section-->
    </div>
</template>

<script>

export default {
    name: 'Query',
    data(){
        return{
            firstname: null,
            lastname: null,
            email: null,
            phone: null,
            message: null
        }
    },
    methods:{
        sendQuery(){
            alert('Your Query Has Been Sent')
            this.$router.push({name:'Query'})
            console.log(this.firstname,this.lastname)
            console.log(this.email,this.phone)
            console.log(this.message)
        }
    }
}
</script>

<style>
.query{
    margin-top: 50px;
}
textarea.materialize-textarea{
    height: 10rem;
}
</style>
