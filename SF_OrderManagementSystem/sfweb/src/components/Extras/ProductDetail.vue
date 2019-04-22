<template>
  <div id="product-detail" class="row grid">
      <section class="testimonials padding-top-90 padding-bottom-90" id="testimonials">
      <div class="container">
        <h1>Product Detail</h1>
      </div>
    </section>
    <div class="container">

        <div class="row">
          <div class="col-sm-6">
            <img src="assets/images/portfolio/work-4.jpg">
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
                  <tr v-for="(sizeObj,index) in product.sizes" :key="index">
                    <td>{{sizeObj.size}}</td>
                    <td>{{currencySign}}{{(sizeObj.price*currencyRate).toFixed(2)}}</td>
                  </tr>
                </tbody>
              </table>
            </div>
            <a href="/#home">Back</a>
          </div>
        </div>
      </div>

  </div>
</template>

<script>
import { mapState } from 'vuex'
export default {
  name: "ProductDetail",
  data() {
    return {

    }
  },
  computed:{
    ...mapState(['products','currencySign','currencyRate']),
    product: function(){
        return this.products[this.$route.params.product_index]
    }
  },


};
</script>

<style>
</style>
