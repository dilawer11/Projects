<template>
<div id="index">
         <div class="preloader"><div class="loader startLoad"></div></div>
        <div class="page-loader startLoad animi-loader" style="animation-name: none;">
          <div class="loader startLoad"></div>
        </div>
        <div class="main_img new_top img-shadow">
            <div>
                <img src="assets/images/me-2.jpeg" alt="">
            </div>
        </div>
     


       
        <div class="top">
            <a href="#home" class="smooth_scroll"><i class="fa fa-angle-up fa-2x"></i></a>
        </div>
        <!--Start Home Section-->
                <section class="home " id="home">
                    <div class="full_height bg_image" style="background-image: url('assets/images/bg.jpg');" data-stellar-background-ratio="0.7">
                        <div id="particles-js"></div>
                        
                        <!-- nav -->
                       
                        <div class="overlay">
                            <div class="wrapper">
                                <div class="content opacity-zero">
                                    <h1>Surgical Fibre</h1>
                                    <span>manufacturer of surgical dressings</span>
                                </div>
                            </div>
                        </div>
                    </div><!--.full_height-->
                </section>
                <!--End Home Section-->


                <!--Start About Section-->
                <section class="about padding-top-90 padding-bottom-90" id="about">
                    <div class="container">
                        <div class="row">
                            <div class="col-md-6 item1">
                                <h3>about us</h3>
                                <p>We are one of the best surgical dressings manufacturer of pakistan with the aim to sell top quality products nationwide and abroad.</p>
                                <div class="more-about-me">
                                    <div class="follow">
                                        <span>Follow Us</span>
                                        <a href="https://www.facebook.com/surgicalfibre/">Facebook</a>
                                        
                                    </div>
                                 
                                </div>
                            </div>
                        </div><!--.row-->
                    </div><!--.container-->
                </section>
                <!--End About Section-->


                <!--Start Portfolio Section-->
                <section  class="portfolio padding-top-90 padding-bottom-60 primary_bg" id="portfolio">
                    <div class="container">
                        <div class="sec_title">
                            <p>portfolio</p>
                            <h2>Products</h2>
                        </div>

                        <div class="row grid" id="products-showroom">
                            <div v-for="(item,index) in products" :key="index">
                               <div class="col-xs-12 col-sm-6 col-md-4 grid-item grid-sizer design">
                                <div class="box">
                                    <div class="my__img">
                                        <img src="assets/images/portfolio/work-1.jpg" alt=''>
                                    </div>
                                    <div class="boxContent project_popup">
                                        <a class="popup-with-zoom-anim" href="#slider_popup">
                                            <div class="display-table">
                                                <div class="display-table-cell">
                                                    <span class="post">{{item.category}}</span>
                                                    <h3 class="title">{{item.name}}</h3>
                                                </div>
                                            </div>
                                        </a>
                                    </div>
                                </div>
                            </div>
                            <!--Project 1 Details-->
                            <div id="slider_popup" class="zoom-anim-dialog mfp-hide">
                            <div class="display-table">
                                <div class="display-table-cell">
                                    <div class="row">
                                        <div class="col-sm-6">
                                            <img src="assets/images/portfolio/work-4.jpg" alt="">
                                        </div>
                                        <div class="col-sm-6">
                                            <h3>{{item.name}}</h3>
                                            <ul class="list-unstyled project_info">
                                                <li><span>Category :</span>{{item.category}}</li>
                                            </ul>
                                            <p>
                                                <ul>
                                                    <li v-for="(size,i) in item.sizes" :key="i">{{size.size}} </li>
                                                </ul>
                                                {{item.description}}
                                            </p>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                        </div>            
                        </div><!--.row-->
                       
                    </div><!--.container-->
                </section>
                <!--End Portfolio Section-->

                <!--Start Testimonials Section-->
                <section class="testimonials padding-top-90 padding-bottom-90" id="testimonials">
                    <div class="container">
                        <img src="assets/images/quotes-white.png" alt="" class="quotes">
                        <div class="owl-carousel" id="testimonial-carousel">
                            
                            <!--testimonial 1-->
                            <div class="testimonial">
                                <div class="content">
                                    <p>
                                        Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus molestie, justo nec convallis sollicitudin, sapien lorem dictum lacus, non consequat odio ipsum nec est. Sed mattis egestas elementum. Nulla facilisi. Quisque placerat risus ac nunc ornare tincidunt.
                                    </p>
                                    <h6 class="name-job">
                                        <span class="name">Arshad Kamal</span>
                                        <span class="job">CEO</span>
                                    </h6>
                                </div>
                            </div>
                            <!--testimonial 2-->
                            <div class="testimonial">
                                <div class="content">
                                    <p>
                                        Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus molestie, justo nec convallis sollicitudin, sapien lorem dictum lacus, non consequat odio ipsum nec est. Sed mattis egestas elementum. Nulla facilisi. Quisque placerat risus ac nunc ornare tincidunt.
                                    </p>
                                    <h6 class="name-job">
                                        <span class="name">Rutab Ahmed</span>
                                        <span class="job">Director</span>
                                    </h6>
                                </div>
                            </div>
                        </div><!--.owl-carousel-->
                    </div><!--.container-->
                </section>
                <!--End Testimonials Section-->
                </div>
</template>

<script>
import db from '@/firebase/init'
export default {
    name: 'Index',
    data(){
        return{
            products: null,
        }
    },
    async created(){
        const snapshot = await db.collection('products').get()
        snapshot.forEach(document => {
            let product = document.data()
            this.products.push(product)
        })
    },
  
    
}
</script>

<style>

</style>
