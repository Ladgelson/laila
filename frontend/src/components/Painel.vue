<template>
    <div class="container-fluid">
        <Nav/>
        <div class="buttons row">
            <ButtonGroup class="col-11" :type="id" v-on:changeIde="changeIde"/>
            <button v-on:click="sendCode" type="submit" class="buttonSend col-1 btn btn-primary">Enviar</button>
        </div>
        <div class="row">
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[0]" class="col-8 code" codeType="flex"/>
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[1]" class="col-8 code" codeType="bison"/>
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[2]" class="col-8 code" codeType="test"/> 
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[3]" class="col-8 code" codeType="entrada"/> 
            <codemirror 
                class="col-4"
                v-model="result"
                :options="cmOptions"
                @input="onCmCodeChange"
                />
        </div>
    </div>
</template>

<script>
import 'codemirror/mode/clike/clike'
import 'codemirror/theme/lesser-dark.css'
import CodeGeneration from './CodeGeneration.vue'
import ButtonGroup from './ButtonGroup.vue'
import Nav from './Nav.vue'
export default {
    components: {
        ButtonGroup,
        CodeGeneration,
        Nav
    },
    data(){
        return {
            id: this.$route.params.id,
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
                theme: 'lesser-dark',
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
        async sendCode(){
            try {
                let ret;
                console.log(this.$rest)
                if(this.id == 'lexical'){
                    ret = await this.$rest.lexical.findAll(
                        {
                            'lexicalAnalyser': this.flexCode,
                            'code': this.testCode,
                            'hash': "1"
                        }
                    ) 
                } 
                if(this.id == 'sintatical'){
                    ret = await this.$rest.sintatical.findAll(
                        {
                            'lexicalAnalyser': this.flexCode,
                            'sintaticalAnalyser': this.bisonCode,
                            'code': this.testCode,
                            'hash': "1"
                        }
                    )
                    console.log(ret)
                    if(ret["status"]){
                        this.result = ret.warning + '\n';
                        this.result += ret.return;
                    } else {
                        this.result = ret.message;
                        this.result += ret.warning;
                    }
                }
                console.log(ret)
            } catch(err) {
                console.error(err)
            }
        }
    }
}
</script>

<style>
.code .CodeMirror{
    height: 500px;
}

.container-fluid {
    padding: 0px;
}

.buttonSend {
    background-color: #8605B8;
    border-color: #8605B8;
    color: white;
}

.buttonSend:hover {
    border-color: black;
    background-color: #8605B8;
}

.buttons {
    margin-top: 10px;
}
</style>