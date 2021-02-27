<template>
    <div class="container-fluid">
        <div class="row">
            <CodeGeneration v-on:changeCode="addCode" class="col-sm" placeholder="FLEX Code" codeType="flex"/>
            <CodeGeneration v-on:changeCode="addCode" class="col-sm" placeholder="Bison Code" codeType="bison"/>
            <CodeGeneration v-on:changeCode="addCode" class="col-sm" placeholder="Test Code" codeType="test"/> 
        </div>
    </div>
</template>

<script>
import CodeGeneration from './CodeGeneration.vue'
export default {
    components: {
        CodeGeneration
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
        async sendFlexCode(){
            try {
                this.users = await this.$rest.employees.findAll()
                this.load = false
            } catch(err) {
                console.error(err)
                this.load = false
                this.error = true
            }
        }
    }
}
</script>

<style>

</style>