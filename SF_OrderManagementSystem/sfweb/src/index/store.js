import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    products: [1,2,3],
    currencySign : 'Rs.',
    currencyRate : 1,
  },
  getters:{

  },
  mutations: {
    UPDATE_PRODUCTS(state,passedProducts){
      state.products=passedProducts
    },
    SET_CURRENCY(state,rate){
      state.currencySign='$'
      state.currencyRate=rate
    }
  },
  actions: {

  }
})




