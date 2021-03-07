<template>
    <div class="main ">
        <Nav/>
        <div class="row mainInfo align-items-center">
            <div class="col ">
                <div class="row justify-content-end align-items-center" >
                    <img src="https://previews.123rf.com/images/yuzach/yuzach1607/yuzach160700007/60379520-cute-black-cat-in-flat-style-with-funny-cartoon-square-head.jpg" />
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
    background-color: #8605B8;
    border-color: #8605B8;
}

.button-group button:hover{
    background-color: #8c21b5;
    border-color: #8c21b5;
}

</style>