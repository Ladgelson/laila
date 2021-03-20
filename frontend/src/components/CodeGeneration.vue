<template>
    <div class="container-fluid">
        <codemirror 
            v-model="code"
            :options="cmOptions"
            @input="onCmCodeChange"
            @beforeChange="onCmBlockLastLines"
            style="CodeMirror"
            />
    </div>
</template>

<script>
import 'codemirror/mode/clike/clike'
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
        onCmBlockLastLines(cm, change){
            if(this.codeType == 'flex' || this.codeType == 'bison'){
                if(cm.lineCount()-11 <= change.from.line){
                    change.cancel();
                }
            }
        },
        selectInitialCode(codeType){
            if(codeType == 'flex') {
                if(this.type == 'lexical') {
                    return `
/*

    Here you can put your FLEX code.

*/

/*

    The function main is required and cannot be changed

*/
int main(){
	yyin = fopen("code","r");
	yylex();
	fclose(yyin);
return 0;
}`;
                } else {
                    return `
/*

    Here you can put your FLEX code.

*/

/*

    The function main is required and cannot be changed

*/



int yywrap() {
   return 1;
}`;
                }
            } 
            if(codeType == 'bison') return `
/*

    Here you can put your Bison code.

*/

// The function main is required and cannot be changed

#include "lex.yy.c"

int main(){
	yyin=fopen("entrada.lad","r");
	yyparse();
	yylex();
	fclose(yyin);
return 0;
}`;
            return '';
        }
    },
    data(){ 
        return {
            code: this.selectInitialCode(this.codeType),
            cmOptions: {
                // codemirror options
                tabSize: 4,
                mode: 'text/x-csrc',
                highlightDifferences: true,
                theme: 'dracula',
                lineNumbers: true,
                line: true,
                autoRefresh:true,
            }   
        }
    },
    watch: {
        code(val) {
            this.$emit('changeCode', {
                code: val,
                type: this.codeType
            });
        }, 
    }
}

</script>
<style>
.CodeMirror { 
    text-align: left!important;
    height: 500px
}
</style>