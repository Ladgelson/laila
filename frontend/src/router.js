import Vue from 'vue'
import Router from 'vue-router'
// import MainPage from './components/MainPage.vue'
//import Painel from './components/Painel.vue'
Vue.use(Router)

export default new Router({
  linkExactActiveClass: 'active',
  routes: [
    {
      path: '/',
      name: 'mainPage',
      component: () => import('./components/MainPage')
    },
    {
      path: '/painel/:id',
      name: 'painel',
      component: () => import('./components/Painel')
    },
    // {
    //   path: '/',
    //   redirect: 'mainPage',
    //   component: Painel,
    //   children: [
    //     // rotas do projeto
    //     // {
    //     //   path: '/employees/edit/:id',
    //     //   name: 'editar colaborador',
    //     //   component: () => import('./views/Employee/FormEmployee.vue')
    //     // },
    //   ]
    // },
  ]
})