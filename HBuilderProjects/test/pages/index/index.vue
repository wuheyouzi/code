<template>

</template>

<script>
  export default {
    data() {
      return {}
    },
    onLoad() {
      uniCloud.callFunction({
        name: "fun"
      }).then(res => {
        console.log(res)
      })
    },
    methods: {

    }
  }
</script>

<style>
</style>
