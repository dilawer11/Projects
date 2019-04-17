import Vue from 'vue'
import Router from 'vue-router'
import Index from '@/components/Client/Index'
import Order from '@/components/Client/Order'
import Query from '@/components/Client/Query'


Vue.use(Router)

const router = new Router({
  mode: 'history',
  base: process.env.BASE_URL,
  routes: [
    {
      path: '/',
      name :'Index',
      component: Index
    },
    {
      path: '/query',
      name :'Query',
      component: Query
    },
    {
      path: '/order',
      name :'Order',
      component: Order
    },
  ]
})

export default router
