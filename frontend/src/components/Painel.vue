<template>
    <div class="container-fluid">
        <div class="row">
            <Code v-on:changeCode="addCode" class="col-sm" placeholder="FLEX Code" codeType="flex"/>
            <Code v-on:changeCode="addCode" class="col-sm" placeholder="Bison Code" codeType="bison"/>
            <Code v-on:changeCode="addCode" class="col-sm" placeholder="Test Code" codeType="test"/> 
        </div>
    </div>
</template>

<script>
import Code from './Code.vue'
export default {
    components: {
        Code
    },
    data(){
        return {
            flexCode: '',
            bisonCode: '',
            auxCode: '',
            testCode: ''
        }
    }, 
    methods: {
        addCode(obj){
            if(obj.type == 'flex')
                this.flexCode = obj.code
            if(obj.type == 'bison')
                this.bisonCode = obj.code
            if(obj.type == 'test')
                this.testCode = obj.code
        },
    }
}
</script>

<style>

</style>