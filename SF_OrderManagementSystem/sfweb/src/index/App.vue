<template>
  <div id="client">
    <Navbar/>
    <router-view/>
    <Footer/>
  </div>
</template>

<script>
import Navbar from "@/components/Client/Navbar";
import Footer from "@/components/Client/Footer";
import { mapMutations } from 'vuex'
import db from "@/firebase/init";
import currencyConverter from "@/firebase/currencyConverter";
const axios = require("axios");

export default {
  name: "App",
  components: {
    Navbar,
    Footer
  },
  data() {
    return {};
  },
  methods: {
    ...mapMutations([
      'UPDATE_PRODUCTS',
      'SET_CURRENCY'
    ]),

  },
  created() {
    db.collection("products")
      .get()
      .then(snapshot => {
        let localProducts = [];
        snapshot.forEach(doc => {
          localProducts.push(doc.data());
        });
        this.UPDATE_PRODUCTS(localProducts);
        let request =
          "https://free.currconv.com/api/v7/convert?q=PKR_USD&compact=ultra&apiKey=" +
          currencyConverter.apiKey;
        axios
          .get(request)
          .then(response => {
            this.SET_CURRENCY(response.data.PKR_USD);
          })
          .catch(err => {
            console.log(err);
          });
      });
  }
};
</script>

<style>
</style>