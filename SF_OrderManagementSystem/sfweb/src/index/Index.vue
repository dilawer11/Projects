<template>
  <div class="row grid" id="client">
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
  </div>
</template>

<script>

import firebase from 'firebase/app'

export default {
  name: 'Client',
  components:{

  },
  data(){
    return {
      products: [0,1,2],
    }
  }
}
</script>

<style>

</style>