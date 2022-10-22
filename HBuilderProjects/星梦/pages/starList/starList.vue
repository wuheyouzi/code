<template>
  <view>
    <view class="flex my-45 justify-center" @click="statusHandle()">
      <text>{{status}}</text>
    </view>
    <view v-for="star in list" :key="star._id" @click="navigate(star.aid, star.title)">
      <view class="flex items-center stars flex-row scroll-smooth"
        style="border-radius: 10px;margin-bottom: 15px; margin: 13rpx 15rpx">
        <image class="flex" style="width: 100px; height: 100px; border-radius: 15px;" mode="scaleToFill"
          src="https://cdn.jsdelivr.net/gh/BlueSgler/mycdn/img/FD7E555FE7CABE4B2C13EF1F2B2ADD08.jpg">
        </image>
        <view class="flex flex-col" style="margin-left: 20px;">
          <h4>{{star.title}}</h4>
          <text>{{star.describe}}</text>
        </view>
        <text style="padding-left: 20rpx;">{{star.writer}}</text>
      </view>
    </view>
  </view>
</template>

<script>
  export default {
    data() {
      return {
        list: this.getStars(),
        status: "正在铸就星海",
        timer: null
      }
    },
    onLoad() {
      this.timer = setInterval(() => this.getStars(), 60000);
    },
    onUnload() {
      clearInterval(this.timer)
    },
    methods: {
      statusHandle() {
        if (this.list !== "") {
          this.status = "别点我啦";
          return;
        }
        this.status = "loading";
        this.getStars();
      },
      getStars() {
        uniCloud.callFunction({
          name: 'fun',
          data: {
            api: "getStarList"
          }
        }).then(res => {
          this.list = res.result.success === true ? res.result.data : "";
          this.status = this.list === "" ? "ya! 莫得星星" : "沉浸星的光芒";
        })
      },
      navigate(aid, title) {
        uni.navigateTo({
          url: `/pages/starList/star/star?aid=${aid}&title=${title}`
        });
      }
    },
  }
</script>

<style>
  .my-45 {
    /* y轴上下45rpx外边距 */
    margin-top: 45rpx;
    margin-bottom: 45rpx;
  }

  .stars {
    border-bottom: 1px solid #ccc;
    padding: 20rpx;
    border-radius: 20px;
    line-height: 1.5;
    min-height: 150rpx;
  }
</style>
