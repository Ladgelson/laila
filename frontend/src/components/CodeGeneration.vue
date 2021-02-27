<template>
    <div class="container-fluid">
        <h1>{{placeholder}}</h1>
        <codemirror 
            v-model="code"
            :options="cmOptions"
            @input="onCmCodeChange"
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
        codeType: String
    },
    methods: {
        onCmCodeChange(newCode) {
            console.log('this is new code', newCode)
            this.code = newCode
        }
    },
    data(){ 
        return {
            code: 'int a = 10;',
            cmOptions: {
                // codemirror options
                tabSize: 4,
                mode: 'text/x-csrc',
                highlightDifferences: true,
                theme: 'dracula',
                lineNumbers: true,
                line: true,
            }   
        }
    },
    watch: {
        code(val) {
            this.$emit('changeCode', {
                code: val,
                type: this.codeType
            });
        }
    }
}

</script>
<style>
.CodeMirror { 
    text-align: left!important;
    height: 500px
}
</style>