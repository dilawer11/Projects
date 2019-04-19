<template>
  <div id="order">
      <p v-if="feedback">{{feedback}}</p>
    <section class="testimonials padding-top-90 padding-bottom-90" id="testimonials">
      <div class="container">
        <h1>Order</h1>
      </div>
    </section>
    <!--Start Portfolio Section-->
    <section class="portfolio padding-top-90 padding-bottom-60 primary_bg" id="portfolio">
      <div class="container">
        <div class="sec_title">
          <p>Order</p>
          <h2>Form</h2>
        </div>
        <table class="table">
          <thead class="thead-dark">
            <tr>
              <th scope="col">#</th>
              <th scope="col">Product Name</th>
              <th scope="col">Size</th>
              <th scope="col">Quantity</th>
              <th scope="col">Price</th>
              <th scope="col">Total</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="(item,index) in orderItems" :key="index">
              <th scope="row">{{index+1}}</th>
              <td>{{item.name}}</td>
              <td>{{item.size}}</td>
              <td>{{item.qty}}</td>
              <td>{{item.price}}</td>
              <td>{{item.total}}</td>
            </tr>
          </tbody>
        </table>
      </div>

      <!--.container-->
    </section>
    <!--End Portfolio Section-->
  </div>
</template>

<script>
export default {
  name: "Order",
  data() {
    return {
        feedback:null,
      orderItems: [
        {
          name: "Cotton Wool",
          size: "500gm",
          qty: 3,
          price: 50,
          total: 150
        },
        {
          name: "Cotton Bandage",
          size: "3in x 5mtr",
          qty: 4,
          price: 20,
          total: 80
        }
      ],
      another: null,
      orderTotalPrice: 230
    };
  }
};
</script>

<style>
</style>