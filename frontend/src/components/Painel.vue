<template>
    <div class="container-fluid">
        <Nav/>
        <div class="buttons row">
            <ButtonGroup class="col-11" :type="id" v-on:changeIde="changeIde"/>
            <button v-on:click="sendCode" type="submit" class="buttonSend col-1 btn btn-primary">Enviar</button>
        </div>
        <div class="row">
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[0]" class="col code" codeType="flex" :type="this.id"/>
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[1]" class="col code" codeType="bison" :type="this.id"/>
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[2]" class="col code" codeType="test"/> 
            <CodeGeneration v-on:changeCode="addCode" v-show="ides[3]" class="col code" codeType="entrada"/> 
        </div>
        <div v-if="load" class="d-flex justify-content-center">
            <div class="spinner-border text-info" role="status">
                <span class="sr-only">Loading...</span>
            </div>
        </div>
        <button type="button" class="terminal btn btn-dark">Terminal</button>
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
            inputCode: '',
            testCode: '',
            result: '',
            terminalVisibility: false,
            load: false,
            main: false,
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
        handleFlexCode(code){
            const index = code.search("int main");
            if(index != -1)
                code = code.substr(0, index);
            code += `
int main(){
	yyin = fopen("code","r");
	yylex();
	fclose(yyin);
    return 0;
}`;
            // console.log(code);
            this.flexCode = code;
        },
        handleBisonCode(code){
            const index = code.search("int main");
            if(index != -1)
                code = code.substr(0, index);
            code += `
int main(){
	yyin=fopen("entrada.lad","r");
	yyparse();
	yylex();
	fclose(yyin);
return 0;
}`;
            // console.log(code);
            this.bisonCode = code;
        },
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
            if(obj.type == 'entrada')
                this.inputCode = obj.code
        },  
        mainValue(obj){
            this.main = obj.main
        },
        changeIde(obj){
            this.ides = obj.ides
        },
        async sendCode(){
            this.load = true;
            this.result = "";
            try {
                let ret;
                if(this.id == 'lexical'){
                    this.handleFlexCode(this.flexCode)
                    let objToSend = {
                        'lexicalAnalyser': this.flexCode,
                        'sintaticalAnalyser': this.bisonCode,
                        'code': this.testCode,
                        'input': this.inputCode
                    }
                    ret = await this.$rest.lexical.create(objToSend);
                    
                    let cOut = ret.cOut == undefined ? '':ret.cOut;
                    let errorC = ret.errorC == undefined ? '':ret.errorC;
                    
                    this.result = cOut;
                    this.result += errorC ;
                    if(ret["status"]){
                        this.result += ret.return;
                    } else {
                        this.result += ret.message;
                    }
                }
                if(this.id == 'sintatical'){
                    this.handleBisonCode(this.bisonCode);
                    let objToSend = {
                        'lexicalAnalyser': this.flexCode,
                        'sintaticalAnalyser': this.bisonCode,
                        'code': this.testCode,
                        'input': this.inputCode
                    }
                    console.log(objToSend);
                    ret = await this.$rest.sintatical.create(objToSend)
                    if(ret["status"]){
                        this.result = ret.warning + '\n';
                        this.result += ret.return;
                    } else {
                        this.result = ret.message;
                        this.result += ret.warning;
                    }
                }
                this.load = false;
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

.terminal {
    border-radius: 0px;
}

.terminal:hover {
    background-color: #343A40;
    border-color: #343A40;
}
</style>