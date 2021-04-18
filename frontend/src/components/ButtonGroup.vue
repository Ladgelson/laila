<template>
    <ul class="nav nav-tabs">
        <li class="nav-item">
            <a v-on:click="selectIde(0)" class="nav-link" v-bind:class="{active: ides[0]}" >FLEX Code</a>
        </li>
        <li v-if="type == 'sintatical'" class="nav-item">
            <a v-on:click="selectIde(1)" class="nav-link" v-bind:class="{active: ides[1]}" >Bison Code</a>
        </li>
        <li class="nav-item">
            <a v-on:click="selectIde(2)" class="nav-link" v-bind:class="{active: ides[2]}" >Test Code</a>
        </li>
        <li class="nav-item">
            <a v-on:click="selectIde(3)" class="nav-link" v-bind:class="{active: ides[3]}" >Input</a>
        </li>
    </ul>
</template>

<script>
export default {
    props: {
        type: String,
    },
    data(){
        return {
            selected: '',
            ides: [
                true,
                false,
                false,
                false,
            ]
        }
    },
    methods: {
        selectIde(index){
            this.deactivateAll()
            this.ides[index] = true
        },
        deactivateAll(){
            let ides = this.ides.map((item) => {
                item = false
                return item
            })
            this.ides = ides
        }
    },
    watch: {
        ides(val) {
            this.$emit('changeIde', {
                ides: val,
            });
        }
    }
}
</script>

<style>

a {
    cursor: pointer;
}

.nav-tabs .nav-link.active {
    background-color: #282A36;
    color: white
}

.nav-tabs .nav-item {
    margin-bottom: -2px;
}


.nav-tabs {
    padding: 0px;
}

a.nav-link.active {
    color: black;
    padding-left: 10px!important;
    padding-right: 10px!important;
}

a.nav-link.active:hover{
    color: white;
    background-color: #45495E;
}

</style>