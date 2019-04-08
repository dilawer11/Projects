import Vue from 'vue'
import Router from 'vue-router'
import Index from '@/components/Index'
import AddProduct from '@/components/AddProduct'
import EditProduct from '@/components/EditProduct'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'Index',
      component: Index
    },
    {
      path: '/add-product',
      name: 'AddProduct',
      component: AddProduct
    },
    {
      path: '/edit-product/:product_slug',
      name: 'EditProduct',
      component: EditProduct
    }
  ]
})
