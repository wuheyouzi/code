<template>
  <view>
    <view v-html="star"></view>
  </view>
</template>

<script>
  export default {
    data() {
      return {
        star: null
      }
    },
    onLoad: function(option) {
      uni.setNavigationBarTitle({
        title: option.title
      })

      this.getArticle(option.aid);
    },
    methods: {
      getArticle(aid) {
        uniCloud.callFunction({
          name: "fun",
          data: {
            api: "getStar",
            args: {
              aid
            }
          }
        }).then(res => {
          if (res.result.success === false) {
            uni.showToast({
              title: res.result.errorMessage,
              icon: 'error'
            })
            return;
          }
          this.star = res.result.data.content;
        })
      }
    }
  }
</script>

<style>

</style>
