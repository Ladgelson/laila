<template>
    <div class="container-fluid">
        <ButtonGroup v-on:changeIde="changeIde"/>
        <div class="row">
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[0]" v-bind:class="{'col-8':terminalVisibility}" codeType="flex"/>
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[1]" v-bind:class="{'col-8':terminalVisibility}" codeType="bison"/>
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[2]" v-bind:class="{'col-8':terminalVisibility}" codeType="test"/> 
            <codemirror 
                v-if="terminalVisibility"
                class="col-4"
                v-model="result"
                :options="cmOptions"
                @input="onCmCodeChange"
                style="CodeMirror"
                />
        </div>
        <button v-on:click="sendFlexCode" type="submit" class="btn btn-primary">Enviar</button>
    </div>
</template>

<script>
import 'codemirror/mode/clike/clike'
import 'codemirror/theme/dracula.css'
import CodeGeneration from './CodeGeneration.vue'
import ButtonGroup from './ButtonGroup.vue'
export default {
    components: {
        ButtonGroup,
        CodeGeneration
    },
    data(){
        return {
            flexCode: '',
            bisonCode: '',
            auxCode: '',
            testCode: '',
            result: '',
            terminalVisibility: false,
            cmOptions: {
                tabSize: 4,
                mode: 'text/x-csrc',
                highlightDifferences: true,
                theme: 'dracula',
                lineNumbers: true,
                line: true,
            },
            ides: [
                true,
                false,
                false,
                false,
            ]
        }
    }, 
    methods: {
        onCmCodeChange(newCode) {
            this.result = newCode
        },
        addCode(obj){
            if(obj.type == 'flex')
                this.flexCode = obj.code
            if(obj.type == 'bison')
                this.bisonCode = obj.code
            if(obj.type == 'test')
                this.testCode = obj.code
        },
        changeIde(obj){
            this.ides = obj.ides
        },
        async sendFlexCode(){
            try {
                const ret = await this.$rest.lexical.findAll(
                    {
                        'lexicalAnalyser': this.flexCode,
                        'code': this.testCode,
                        'hash': "1"
                    }
                )
                console.log(ret)
                this.result = ret["return"]
                this.terminalVisibility = true
            } catch(err) {
                console.error(err)
                // this.load = false
                // this.error = true
            }
        }
    }
}
</script>

<style>
</style>