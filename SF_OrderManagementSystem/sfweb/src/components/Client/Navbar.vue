<template>
    <div id="navbar">
     

        <nav class="navbar navbar-default navbar-fixed-top">
            <div class="container">
                <div class="navbar-header">
                

                    <!-- LOGO -->
                    <a class="navbar-brand" href="#"><span>Surgical Fibre</span></a>

                </div>
                
                    <ul class="nav navbar-nav navbar-right">
                        <li>
                            <a href="/#home">Home</a>
                        </li>
                        <!-- <li>
                            <router-link to="/#about" class="smooth_scroll">About</router-link>
                        
                        </li>
                        
                 
                        <li>
                            <a href="/#portfolio" class="smooth_scroll">Products</a>
                        </li> -->
                        <li>
                           <router-link class="smooth_scrool" :to="{name:'Order'}">Order</router-link>
                        </li>
                        
                        <li>
                            <router-link class="smooth_scrool" :to="{name:'Query'}">Contact</router-link>
                        </li>
                    </ul>
                
            </div><!--.container-->
        </nav>
        <!--End Scroll Top-->
    </div>
        
</template>

<script>
export default {
    name:'Navbar',
    data(){
        return{

        }
    }
}
</script>

<style>

</style>
