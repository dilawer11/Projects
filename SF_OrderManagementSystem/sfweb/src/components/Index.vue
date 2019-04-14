<template>
    <div id="index">
      <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Poppins:300,400,500,600,700,800%7CMontserrat:300,400,500,600,700,800,900">

        <!-- Bootstrap css -->
        <link rel="stylesheet" href="@/assets/css/bootstrap.css">

        <!-- magnific-popup.css -->
        <link rel="stylesheet" href="@/assets/css/magnific-popup.css">

        <!-- owl carousel css -->
        <link rel="stylesheet" href="@/assets/css/owl.carousel.min.css">
        <link rel="stylesheet" href="@/assets/css/owl.theme.min.css">

        <!-- font-awesome.min.css -->
        <link rel="stylesheet" href="@/assets/css/font-awesome.min.css">
        
        <!-- pe-icon-7-stroke.min.css -->
        <link rel="stylesheet" href="@/assets/css/pe-icon-7-stroke.min.css">
        
        <!-- Main style css -->
        <link rel="stylesheet" href="@/assets/css/style.css">
        
        <!-- Responsive css -->
        <link rel="stylesheet" href="@/assets/css/responsive.css">


        
        <!--Start Preloader-->
        <div class="preloader"><div class="loader startLoad"></div></div>
        <div class="page-loader startLoad animi-loader" style="animation-name: none;">
          <div class="loader startLoad"></div>
        </div>
        <!--End Preloader-->


        <!--Start Intro Image-->
        <div class="main_img new_top img-shadow">
            <div>
                <img src="@/assets/images/me-2.jpeg" alt="">
            </div>
        </div>
        <!--End Intro Image-->


        <!--Start Scroll Top-->
        <div class="top">
            <a href="#home" class="smooth_scroll"><i class="fa fa-angle-up fa-2x"></i></a>
        </div>
        <!--End Scroll Top-->


        <main class="load-main">
            <div class="main-content">


                <!--Start Home Section-->
                <section class="home " id="home">
                    <div class="full_height bg_image" style="background-image: url('@/assets/images/bg.jpg');" data-stellar-background-ratio="0.7">
                        <div id="particles-js"></div>
                        
                        <!-- nav -->
                        <nav class="navbar navbar-default navbar-fixed-top">
                            <div class="container">
                                <div class="navbar-header">
                                    <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1" aria-expanded="false">
                                        <span class="sr-only">Toggle navigation</span>
                                        <span class="icon-bar"></span>
                                        <span class="icon-bar"></span>
                                        <span class="icon-bar"></span>
                                    </button>

                                    <!-- LOGO -->
                                    <a class="navbar-brand" href="#"><span>Surgical Fibre</span></a>

                                </div>
                                <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
                                    <ul class="nav navbar-nav navbar-right">
                                        <li class="active">
                                            <a href="#home" class="smooth_scroll">Home</a>
                                        </li>
                                        <li>
                                            <a href="#about" class="smooth_scroll">About</a>
                                        </li>
                                        <!--
                                        <li>
                                            <a href="#services" class="smooth_scroll">Services</a>
                                        </li>
                                    -->
                                        <li>
                                            <a href="#portfolio" class="smooth_scroll">Products</a>
                                        </li>
                                        <li>
                                            <a href="#testimonials" class="smooth_scroll">Team</a>
                                        </li>
                                        
                                        <li>
                                            <a href="#contact" class="smooth_scroll">Contact</a>
                                        </li>
                                    </ul>
                                </div><!-- /.navbar-collapse -->
                            </div><!--.container-->
                       </nav>
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
                            <!--
                            <div class="col-md-6 item2">
                                <h3>Top Selling</h3>
                             
                                <div class="skills">

                                    
                                    <div class="skill">
                                        <span>Guaze</span>
                                        <span>40%</span>
                                        <div class="progress_bg">
                                            <div class="progress_bar"></div>
                                        </div>
                                    </div>

                                    
                                    <div class="skill">
                                        <span>Cotton</span>
                                        <span>25%</span>
                                        <div class="progress_bg">
                                            <div class="progress_bar"></div>
                                        </div>
                                    </div>

                                    
                                    <div class="skill">
                                        <span>Belladona</span>
                                        <span>25%</span>
                                        <div class="progress_bg">
                                            <div class="progress_bar"></div>
                                        </div>
                                    </div>

                                   
                                    <div class="skill">
                                        <span>Bandaged</span>
                                        <span>10%</span>
                                        <div class="progress_bg">
                                            <div class="progress_bar"></div>
                                        </div>
                                    </div>

                                </div>
                            </div>-->
                        </div><!--.row-->
                    </div><!--.container-->
                </section>
                <!--End About Section-->


                <!--Start Fun Facts-->
             
                <!--End Fun Facts-->


                <!--Start Services Section-->
           
                <!--End Services Section-->


                <!--Start Portfolio Section-->
                <section class="portfolio padding-top-90 padding-bottom-60 primary_bg" id="portfolio">
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
                                                    <span class="post">Design</span>
                                                    <h3 class="title">modal one</h3>
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
                                            <div id="MySlider2" class="carousel slide margin-bottom-30" data-ride="carousel">
                                               
                                                <ol class="carousel-indicators">
                                                    <li data-target="#MySlider2" data-slide-to="0" class="active"></li>
                                                    <li data-target="#MySlider2" data-slide-to="1"></li>
                                                    <li data-target="#MySlider2" data-slide-to="2"></li>
                                                </ol>

                                               
                                                <div class="carousel-inner" role="listbox">

                                                    <div class="item active">
                                                        <img src="assets/images/portfolio/work-2.jpg" alt="">
                                                    </div>

                                                    <div class="item">
                                                        <img src="assets/images/portfolio/work-3.jpg" alt="">
                                                    </div>

                                                    <div class="item">
                                                        <img src="assets/images/portfolio/work-4.jpg" alt="">
                                                    </div>

                                                </div>

                                                
                                                <a class="left carousel-control" href="#MySlider2" role="button" data-slide="prev">
                                                    <span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>
                                                    <span class="sr-only">Previous</span>
                                                </a>
                                                <a class="right carousel-control" href="#MySlider2" role="button" data-slide="next">
                                                    <span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>
                                                    <span class="sr-only">Next</span>
                                                </a>
                                            </div>
                                            
                                            
                                        </div>
                                        <div class="col-sm-6">
                                            <h3>Creative Design</h3>
                                            <ul class="list-unstyled project_info">
                                                <li><span>Client :</span>Envato</li>
                                                <li><span>Date :</span>March 19, 2017</li>
                                                <li><span>Skills :</span>HTML5, JS, CSS3</li>
                                            </ul>
                                            <p>
                                                Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
                                            </p>
                                            <a href="#" class="demo">Visit website</a>
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


                <!--Start Blog Section-->
            
                <!--End Blog Section-->


                <!--Start Contact Section-->
         
                <!--End Contact Section-->


                <!--Start Footer-->
                <footer>
                    <div class="footer-info">
                        <div class="container text-center">
                            <div class="row text-center info">

                                <div class="col-sm-4 item">
                                    <div class="content">
                                        <span class="pe-7s-call pe-3x pe-va icon"></span>
                                        <div>
                                            <p>+92 321 4444826</p>
                                        </div>
                                    </div>
                                </div>

                                <div class="col-sm-4 item">
                                    <div class="content">
                                        <span class="pe-7s-mail pe-3x pe-va icon"></span>
                                        <div>
                                            <p><a href="mailto:surgicalfibre@gmail.com">surgicalfibre@gmail.com</a></p>
                                        </div>
                                    </div>
                                </div>

                                <div class="col-sm-4 item">
                                    <div class="content">
                                        <span class="pe-7s-map-marker pe-3x pe-va icon"></span>
                                        <div>
                                            <p>Lahore, Punjab</p>
                                        </div>
                                    </div>
                                </div>

                            </div><!--.row-->
                        </div><!--.container-->  
                    </div>
                    <div class="footer-bottom">
                        <div class="container text-center">
                            <p>&copy; 2018 Surgical Fibre | Designed by Dilawer Ahmed</p>
                        </div><!--.container-->  
                    </div>
                </footer>
                <!--End Footer-->


            </div><!--.main-content-->
        </main>

    

        <!--jquery.min.js-->
        <script src="@/assets/js/jquery.min.js"></script>

        <!--animate-skills.js-->
        <script src="@/assets/js/animate-skills.js"></script>

        <!--waypoints.min.js-->
        <script src="@/assets/js/waypoints.min.js"></script>

        <!--jquery.counterup.min.js-->
        <script src="@/assets/js/jquery.counterup.min.js"></script>

        <!--particles.min-->
        <script src="@/assets/js/particles.min.js"></script>

        <!--app.js-->
        <script src="@/assets/js/app-polygon.js"></script>

        <!--jquery.fittext.js-->
        <script src="@/assets/js/jquery.fittext.js"></script>

        <!--bootstrap.min.js-->
        <script src="@/assets/js/bootstrap.min.js"></script>

        <!--jquery.magnific-popup.min.js-->
        <script src="@/assets/js/jquery.magnific-popup.min.js"></script>

        <!--isotope.pkgd.min.js-->
        <script src="@/assets/js/isotope.pkgd.min.js"></script>

        <!--owl.carousel.min.js-->
        <script src="@/assets/js/owl.carousel.min.js"></script>

        <!-- Main script js -->
        <script src="@/assets/js/custom.js"></script>

       </div>  
     
        
</template>

<script>
export default {
    name: 'Index',
    data(){
        return{
            products: [0,1,2]
        }
    }
}
</script>

<style>

</style>
