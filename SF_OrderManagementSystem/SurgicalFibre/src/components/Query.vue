<template>
    <div class="query">
    <h2 class="center-align black-text">Query Form</h2>
    
    <div class="container">
    <div class="divider"></div>
    <br><br>
    <br><br>
    <form class="col s12">
        <div class="row">
            <div class="input-field col s12 m6">
                <i class="material-icons prefix">account_circle</i>
                <input id="first_name" type="text">
                <label class="active" for="first_name">First Name</label>
            </div>
            <div class="input-field col s12 m6">
                <i class="material-icons prefix">account_circle</i>
                <input id="last_name" type="text" >
                <label class="active" for="last_name">Last Name</label>
            </div>
        </div>
        <div class="row">
            <div class="input-field col s12 m6">
                <i class="material-icons prefix">email</i>
                <input id="email" type="email">
                <label class="active" for="email">Email </label>
            </div>
            <div class="input-field col s12 m6">
                <i class="material-icons prefix">phone</i>
                <input id="phone" type="tel" >
                <label class="active" for="phone">Phone</label>
            </div>
        </div>
  
        <div class="row">
            <div class="input-field col s12 m12">
            <i class="material-icons prefix">mode_edit</i>
            <textarea id="message" class="materialize-textarea" data-length=250></textarea>
            <label class="active" for="message">Message</label>
            </div>
        </div>
        <button class="btn waves-effect waves-light">
            Send
            <i class="material-icons right">send</i>
        </button> 
    </form>
  </div>
    </div>
</template>

<script>
export default {
    name: 'Query',
    data(){
        return{

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
