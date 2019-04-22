import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    statusOptions:null
  },
  mutations: {
    UPDATE_STATUS_OPTIONS(state,passedOptions){
      state.statusOptions=passedOptions
    }
  },
  actions: {

  }
})
