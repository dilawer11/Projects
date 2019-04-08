import Vue from 'vue'
import Router from 'vue-router'
import ProductsIndex from '@/components/ProductsManagement/ProductsIndex'
import AddProduct from '@/components/ProductsManagement/AddProduct'
import EditProduct from '@/components/ProductsManagement/EditProduct'
import Dashboard from '@/components/Dashboard'
import Login from '@/components/Login'
import firebase from 'firebase'

Vue.use(Router)

const router = new Router({
  routes: [
    {
      path: '/products',
      name: 'ProductsIndex',
      component: ProductsIndex,
      meta:{
        requiresAuth:true
      }
    },
    {
      path: '/products/add-product',
      name: 'AddProduct',
      component: AddProduct,
      meta:{
        requiresAuth:true
      }
    },
    {
      path: '/products/edit-product/:product_slug',
      name: 'EditProduct',
      component: EditProduct,
      meta:{
        requiresAuth: true
      }
    },
    {
      path: '/',
      name: 'Dashboard',
      component: Dashboard,
      meta:{
        requiresAuth:true
      }
    },
    {
      path: '/login',
      name: 'Login',
      component: Login,
      meta:{
        logoutOnly:true
      }
    }
  ]
})
router.beforeEach((to,from,next)=>{
  if(to.matched.some(rec => rec.meta.requiresAuth)){
    let user = firebase.auth().currentUser
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