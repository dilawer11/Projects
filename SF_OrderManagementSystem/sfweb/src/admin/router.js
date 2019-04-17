import Vue from 'vue'
import Router from 'vue-router'
import ProductsIndex from '@/components/ProductsManagement/ProductsIndex'
import AddProduct from '@/components/ProductsManagement/AddProduct'
import EditProduct from '@/components/ProductsManagement/EditProduct'
import Dashboard from '@/components/Dashboard'
import Login from '@/components/Login'
import NotFound from '@/components/NotFound'
import ArchivedOrders from '@/components/OrderManagement/ArchivedOrders'
import OrdersIndex from '@/components/OrderManagement/OrdersIndex'
import ViewOrder from '@/components/OrderManagement/ViewOrder'
import EditOrder from '@/components/OrderManagement/EditOrder'

import firebase from 'firebase/app'

Vue.use(Router)

const router = new Router({
  mode: 'history',
  base: process.env.BASE_URL,
  routes: [
 
    {
      path: '/admin/',
      name: 'Dashboard',
      component: Dashboard,
      meta:{
        requiresAuth:true
      }
    },
    {
      path: '/admin/login',
      name: 'Login',
      component: Login,
      meta:{
        logoutOnly:true
      }
    },
    {
      path: '/admin/products',
      name: 'ProductsIndex',
      component: ProductsIndex,
      meta:{
        requiresAuth: true
      }
    },
    {
      path: '/admin/products/add-product',
      name: 'AddProduct',
      component: AddProduct,
      meta:{
        requiresAuth: true
      }
    },
    {
      path: '/admin/products/edit-product/:product_slug',
      name: 'EditProduct',
      component: EditProduct,
      meta:{
        requiresAuth: true
      }
    },
    {
      path: '/admin/orders',
      name: 'OrdersIndex',
      component : OrdersIndex,
      meta:{
        requiresAuth: true
      }
    },
    {
      path: '/admin/orders/archived',
      name: 'ArchivedOrders',
      component : ArchivedOrders,
      meta:{
        requiresAuth: true
      }
    },
    {
      path: '/admin/orders/view-order/:order_no',
      name: 'ViewOrder',
      component : ViewOrder,
      meta:{
        requiresAuth: true
      }
    },
    {
      path: '/admin/orders/edit-order/:order_no',
      name: 'EditOrder',
      component : EditOrder,
      meta:{
        requiresAuth: true
      }
    },
    {
      path: '/admin/*',
      name: 'NotFound',
      component: NotFound
    }
  ]
})
router.beforeEach((to,from,next)=>{
  if(to.matched.some(rec => rec.meta.requiresAuth)){
    var user = firebase.auth().currentUser
    if(user){
      next()
    }else{
      next({name:'Login'})
    }
  } else{
    next()
  }
})


export default router
