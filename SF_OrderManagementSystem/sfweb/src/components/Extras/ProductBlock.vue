<template>
  <div class="product-blocks">
    <div class="col-xs-12 col-sm-6 col-md-4 grid-item grid-sizer design">
      <div class="box">
        <div class="my__img">
          <img src="assets/images/portfolio/work-1.jpg" alt>
        </div>
        <div class="boxContent project_popup">
          <a class="popup-with-zoom-anim" href="#slider_popup">
            <div class="display-table">
              <div class="display-table-cell">
                <span class="post">{{product.category}}</span>
                <h3 class="title">{{product.name}}</h3>
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
              <img src="assets/images/portfolio/work-4.jpg" alt>
            </div>
            <div class="col-sm-6">
              <h3>{{product.name}}</h3>
              <ul class="list-unstyled project_info">
                <li>
                  <span>Category :</span>
                  {{product.category}}
                </li>
                <li>
                  <span>Date :</span>March 19, 2017
                </li>
                <li>
                  <span>Skills :</span>HTML5, JS, CSS3
                </li>
              </ul>
              <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>
              <div class="table-responsive">
                <table class="table">
                  <thead>
                    <tr>
                      <th>Size</th>
                      <th>Price</th>
                    </tr>
                  </thead>
                  <tbody>
                    <div v-for="(sizeObj,index) in product.sizes" :key="index">
                      <tr>
                        <td>{{sizeObj.size}}</td>
                        <td>{{currency}}{{sizeObj.price}}</td>
                      </tr>
                    </div>
                  </tbody>
                </table>
              </div>
              <a href="#" class="demo">Visit website</a>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>

export default {
  props: ["product", "currency"],
  data() {
    return {};
  },

  methods: {
  }
};
</script>

<style>
</style>
