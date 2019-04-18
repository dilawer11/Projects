import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    products: [1,2,3],
  },
  getters:{

  },
  mutations: {
    ADD_PRODUCTS(state,passedProducts){
      state.products=passedProducts
    }
  },
  actions: {

  }
})




