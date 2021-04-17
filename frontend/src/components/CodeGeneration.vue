<template>
    <div class="container-fluid">
        <codemirror 
            v-model="code"
            :options="cmOptions"
            @input="onCmCodeChange"
            style="CodeMirror"
            />
    </div>
</template>

<script>
            // @beforeChange="onCmBlockLastLines"
import 'codemirror/mode/clike/clike'
import axios from 'axios'
// theme css
import 'codemirror/theme/dracula.css'
export default {
    props: {
        placeholder: String,
        codeType: String,
        type: String
    },
    methods: {
        onCmCodeChange(newCode) {
            this.code = newCode;
        },
        // onCmBlockLastLines(cm, change){
        //     if(this.codeType == 'flex' || this.codeType == 'bison'){
        //         if(cm.lineCount()-11 <= change.from.line){
        //             change.cancel();
        //         }
        //     }
        // },
        selectInitialCode(codeType, data){
            // console.log(codeType,data);
            // this.code = 'ai dento viado';

            if(this.type == 'lexical'){
                if(codeType == 'flex'){
                    this.code = data["lexicalAnalyser"];
                } else if(codeType == 'test'){
                    this.code = data['code'];
                }
            } else if(this.type == 'sintatical'){
                if(codeType == 'flex'){
                    this.code = data['lexicalAnalyser'];
                } else if(codeType == 'bison'){
                    this.code = data['sintaticalAnalyser'];
                } else if(codeType == 'test'){
                    this.code = data['code'];
                }
            }
        },

        async getCodes(){
            const URL_BASE = "http://200.129.3.5:8081/";
            await axios({
                method: 'get',
                url: this.type == 'lexical' ? URL_BASE+"lexicalCode" : URL_BASE+"sintaticalCode", 
            })
            .then(({data})=> {
                console.log(data);
                this.selectInitialCode(this.codeType, data);
            });
        }
    },
    data(){ 
        return {
            code: '',
            cmOptions: {
                // codemirror options
                tabSize: 4,
                mode: 'text/x-csrc',
                highlightDifferences: true,
                theme: 'dracula',
                lineNumbers: true,
                line: true,
                autoRefresh:true,
            },
            codeData: {}
        }
    },
    watch: {
        code(val) {
            this.$emit('changeCode', {
                code: val,
                type: this.codeType
            });
        }, 
    },
    mounted() {
        this.getCodes();
    },
    computed: {
        // lex: async function(){
            
        // },
        // sin: function(){
        //     axios({
        //         method: 'get',
        //         url: "http://0.0.0.0:5001/sintaticalCode"
        //     })
        //     .then((data)=> {console.log(data); return data;})
        //     return ""
        // }
    }
}

</script>
<style>
.CodeMirror { 
    text-align: left!important;
    height: 500px
}
</style>