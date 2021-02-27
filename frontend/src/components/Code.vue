<template>
    <div class="container-fluid">
        <div class="form-todo form-group">
            <p>
                <textarea 
                    :placeholder="placeholder" 
                    name="message"  
                    class="form-control"
                    style="height: 500px"
                    v-model="code">
                </textarea>
            </p>
        </div>
  </div>
</template>

<script>
export default {
    props: {
        placeholder: String,
        codeType: String
    },
    data() {
        return {
            code: ''
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

</style>