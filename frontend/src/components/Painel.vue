<template>
    <div class="container-fluid">
        <Nav/>
        <div class="buttons row">
            <ButtonGroup class="col-11" :type="id" v-on:changeIde="changeIde"/>
            <button v-on:click="sendCode" type="submit" class="buttonSend col-1 btn btn-primary">Enviar</button>
        </div>
        <div class="row">
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[0]" class="col code" codeType="flex"/>
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[1]" class="col code" codeType="bison"/>
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[2]" class="col code" codeType="test"/> 
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[3]" class="col code" codeType="entrada"/> 
        </div>
        <span>Terminal</span>
        <div class="row">
            <codemirror 
                class="terminal col"
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
                readOnly: true
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
                let objToSend = {
                    'lexicalAnalyser': this.flexCode,
                    'sintaticalAnalyser': this.bisonCode,
                    'code': this.testCode,
                    'hash': "1"
                }
                console.log(objToSend)
                if(this.id == 'lexical'){
                    ret = await this.$rest.lexical.create(objToSend);
                    if(this.id == 'lexical'){
                        this.result = ret.cOut;
                        this.result += ret.errorC;
                        if(ret["status"]){
                            this.result += ret.return;
                        } else {
                            this.result += ret.message;
                        }
                    }
                }
                if(this.id == 'sintatical'){
                    ret = await this.$rest.sintatical.create(objToSend)
                    if(ret["status"]){
                        this.result = ret.warning + '\n';
                        this.result += ret.return;
                    } else {
                        this.result = ret.message;
                        this.result += ret.warning;
                    }
                }
                // if(ret["status"]){
                //     this.result = ret.warning + '\n';
                //     this.result += ret.return;
                // } else {
                //     this.result = ret.message;
                //     this.result += ret.warning;
                // }
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
    height: 300px;
}

.terminal .CodeMirror{
    height: 200px;
    width: 100%;    
}

div.vue-codemirror.terminal.col {
    padding: 0px 15px 0px 0px;
    margin: 0px;
}

.container-fluid {
    padding: 0px;
}

.buttonSend {
    background-color: #323031;
    border-color: #323031;
    color: white;
}

.buttonSend:hover {
    border-color: #323031;
    background-color: #0FBBE6;
    color: black;
    font-weight: bold;
}

.buttons {
    margin-top: 10px;
}

.row {
    margin: 0px;
}
</style>