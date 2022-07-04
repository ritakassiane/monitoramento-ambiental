import Vue from 'vue'
import VueRouter from 'vue-router'
import Main from '../components/Main.vue'
import History from '../views/History.vue'

Vue.use(VueRouter)

const routes = [
    {
        path: '/',
        name: 'Main',
        component: Main
      },
      {
        path: '/history',
        name: 'History',
        component: History
      }
]

const router = new VueRouter({
    mode: 'history',
    base: process.env.BASE_URL,
    routes
  })
  
  export default router
  