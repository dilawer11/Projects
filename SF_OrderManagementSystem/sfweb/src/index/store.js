import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    products: [1,2,3],
    currency : 'Rs.'
  },
  getters:{

  },
  mutations: {
    UPDATE_PRODUCTS(state,passedProducts){
      state.products=passedProducts
    },
    SET_CURRENCY(state,rate){
      state.currency='$'
      state.products.forEach(product=>{
        product.sizes.forEach(size=>{
          size.price=size.price*rate
        })
      })
    }
  },
  actions: {

  }
})




