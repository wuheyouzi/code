<template>
  <view>
    <h3 class="flex justify-center items-center" style="padding: 30px 0;">请在下方输入框中写html</h3>
    <uni-easyinput type="textarea" maxlength="-1" autoHeight v-model="star"></uni-easyinput>
    <h2 class="flex justify-center items-center" style="margin: 60rpx 0;">效果展示</h2>
    <view v-html="star" style="min-height: 600rpx"></view>
    <view class="flex items-center justify-center" style="position: absolute; bottom: 20px; width: 100%">
      <button class="flex" type="primary" @click="star = null" size="mini">清空</button>
      <button class="flex" type="primary" @click="publish()" size="mini">提交</button>
    </view>
  </view>
</template>

<script>
  export default {
    data() {
      return {
        star: null
      }
    },
    methods: {
      publish() {
        if (articleHtml.length < 20) {
          uni.showToast({
            title: "请继续补充呀",
            icon: 'error'
          })
          return;
        }
        uniCloud.callFunction({
          name: "fun",
          data: {
            api: "addStar",
            args: {
              content: this.star
            }
          }
        }).then(res => {
            
        })
      }
    }
  }
</script>

<style>

</style>
