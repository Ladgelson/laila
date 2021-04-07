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
                    <div class="standFor">Lexical And sIntaticaL Analyser - online</div>
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
                        <button class="btn btn-primary" type="submit">Lexical and Sintatical Analyser</button>
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
                        Estudante no Instituto Federal do Ceará - Campus Aracati
                    </div>
                    <div>
                        Contato: micaiasladgelsondasilva@gmail.com
                    </div>
                    <strong>
                        <a href="https://docs.google.com/forms/d/e/1FAIpQLSdvpi2grfXYEViPZ19iECi2-fh4AD5VDIzCR0NoPgeeMQYqGg/viewform?usp=sf_link">
                            Link para formulário
                        </a>
                    </strong>
                    <div class="imgGroup">
                        <a href="https://www.linkedin.com/in/micaiasladgelson/">
                            <img class="iconLink" src="./../assets/linkedin.svg"/>
                        </a>
                        <a class="github" href="https://github.com/Ladgelson">
                            <img class="iconLink" src="./../assets/logotipo-do-github.svg"/>
                        </a>
                    </div>
                </div>
            </div>
            <div>
                <img class="imgProfile" alt="img" src="./../assets/ladgelson.jpg" />
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
    border-color: #9DE7F9;
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

</style>