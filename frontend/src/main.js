import Vue from 'vue'
import App from './App.vue'
import VueCodemirror from 'vue-codemirror';
// Service
import * as rest from "./services";
 
// require styles
import 'codemirror/lib/codemirror.css'
import 'codemirror/mode/clike/clike'

Vue.config.productionTip = false
Vue.prototype.$rest = rest
Vue.use(VueCodemirror,)

new Vue({
  render: h => h(App),
}).$mount('#app')
