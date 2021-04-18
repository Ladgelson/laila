<template>
    <div class="main ">
        <Nav/>
        <div class="row mainInfo align-items-center">
            <div class="col logoImg">
                <div class="row justify-content-end align-items-center" >
                    <img src="./../assets/cat-svgrepo-com.svg" />
                </div>
            </div>
            <div class="col ">
                <div class="row align-items-center">
                    <div class="title" >LAILA</div>
                </div>
                <div class="row align-items-center">
                    <div class="standFor">Lexical And Syntatic Analyser - online</div>
                </div>
                <div class="description-group">
                    <div class="row align-items-center">
                        <div class="description">Create your own programming language.</div>
                    </div>
                    <div class="row align-items-center">
                        <div class="description">Use the traditional Flex and Bison</div>
                    </div>
                    <div class="row align-items-center">
                        <div class="description">Online. Simple. Clean. Fast.</div>
                    </div>
                </div>
                <div class="row align-items-center button-group">
                    <router-link to="/painel/lexical">
                        <button class="btn btn-primary" type="submit">Lexical Analyser</button>
                    </router-link>
                    <router-link to="/painel/sintatical">
                        <button class="btn btn-primary" type="submit">Lexical and Syntatic Analyser</button>
                    </router-link>
                </div>
            </div>
        </div>
        <div class="myInfo row justify-content-end align-items-end container-fluid">
            <div>
                <div class="col  infoProfile">
                    <div class="nameProfile">
                        Micaías Ladgelson
                    </div>
                    <div>
                        Student at Instituto Federal do Ceará
                    </div>
                    <div>
                        E-mail: micaiasladgelsondasilva@gmail.com
                    </div>
                    <strong>
                        <a href="https://docs.google.com/forms/d/e/1FAIpQLSdvpi2grfXYEViPZ19iECi2-fh4AD5VDIzCR0NoPgeeMQYqGg/viewform?usp=sf_link">
                            Link to form
                        </a>
                    </strong>
                    <ul class="social-icons">
                        <li>
                            <a href="https://github.com/Ladgelson">
                                <i class="fab fa-github"></i>
                            </a>
                        </li>
                        <li>
                            <a href="https://www.linkedin.com/in/micaiasladgelson/">
                                <i class="fa fa-linkedin"></i>
                            </a>
                        </li>
                    </ul>
                </div>
            </div>
        </div>
    </div>
</template>
<script>
import Nav from './Nav.vue'
export default {
    components: {
        Nav,
    },
}
</script>
<style>

#app {
    min-height: 100vh;
}

.main {
    min-height: 100vh;
    margin: 0;
}

.mainInfo {
    height: 60vh;
    margin: 0;
}

img {
    height: 300px;
    width: 300px;
    border-radius: 50px;
}

.title {
    height: 45px;
    font-size: 40px;
    font-weight: bold;
    margin-left: 20px;
    padding: 0;
}

.standFor {
    font-size: 15px;
    font-weight: bold;
    margin-left: 20px;
}

.description {
    font-size: 17px;
    margin-left: 20px;
}

.description-group {
    padding-top: 10px;
}

.button-group {
    padding-top: 20px;
}

.button-group button{
    margin-left: 20px;
    background-color: #323031;
    border-color: #323031;
}

.button-group button:hover{
    background-color: #9DE7F9;
    border-color: #323031;
    color: black;
    font-weight: bold;  
}

.imgProfile {
    height: 120px;
    width: 120px;
    border-radius: 10px;
    margin-right: 20px;
}

.infoProfile {
    padding: 10px 10px 10px 0;
}

.nameProfile {
    font-size: 20px;
    font-weight: bold;
}

.myInfo {
    height: 28vh;
}

.iconLink {
    height: 40px;
    width: 40px;
    border-radius: 10px;
}

.imgGroup {
    margin-top: 10px;
}

.github {
    margin-left: 10px;
}

@media (max-width: 600px) {
    .logoImg {display: none}
    .imgProfile {display: none}
}

.social-icons {
  padding: 0;
  list-style: none;
  margin: 0;
}
.social-icons li {
  display: inline-block;
  margin: 0.15em;
  position: relative;
  font-size: 1em;
}
.social-icons i {
  color: black;
  position: absolute;
  top: 0.95em;
  left: 0.96em;
  transition: all 265ms ease-out;
}
.social-icons a {
  display: inline-block;
}
.social-icons a:before {
  transform: scale(1);
  -ms-transform: scale(1);
  -webkit-transform: scale(1);
  content: " ";
  width: 45px;
  height: 45px;
  border-radius: 100%;
  display: block;
  background: linear-gradient(45deg, #9DE7F9, #9DE7F9);
  transition: all 265ms ease-out;
}
.social-icons a:hover:before {
  transform: scale(0);
  transition: all 265ms ease-in;
}
.social-icons a:hover i {
  transform: scale(2.2);
  -ms-transform: scale(2.2);
  -webkit-transform: scale(2.2);
  color: #9DE7F9;
  background: -webkit-linear-gradient(45deg, #9DE7F9, black);
  -webkit-background-clip: text;
  -webkit-text-fill-color: transparent;
  transition: all 265ms ease-in;
}

</style>