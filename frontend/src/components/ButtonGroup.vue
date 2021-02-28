<template>
    <ul class="nav nav-tabs">
        <li class="nav-item">
            <a v-on:click="selectIde(0)" class="nav-link" v-bind:class="{active: ides[0]}" href="#">FLEX Code</a>
        </li>
        <li class="nav-item">
            <a v-on:click="selectIde(1)" class="nav-link" v-bind:class="{active: ides[1]}" href="#">Bison Code</a>
        </li>
        <li class="nav-item">
            <a v-on:click="selectIde(2)" class="nav-link" v-bind:class="{active: ides[2]}" href="#">Test Code</a>
        </li>
        <li class="nav-item">
            <a v-on:click="selectIde(3)" class="nav-link" v-bind:class="{active: ides[3]}" href="#">Entrada</a>
        </li>
    </ul>
</template>

<script>
export default {
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
            console.log(index)
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