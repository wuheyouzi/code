<template>
  <view>
    <view class="flex" style="margin: 60rpx 30rpx;" @click="loginInfo()">
      <image src="../../static/bg.jpg" style="border-radius: 50%; width: 90px; height: 90px;"></image>
      <view class="flex-col" style="margin-left: 28rpx; margin-top:45rpx;">
        <view v-if="onLogin === null">正在获取登录信息</view>
        <view v-else-if="onLogin === true">
          <view style="margin-bottom: 12rpx;">{{userName}}</view>
          <view v-if="id"> id: {{id}}</view>
        </view>
        <view v-else>
          <p style="margin-bottom: 15rpx;">未登录</p>
          <p style="font-size: small; color: darkcyan;">赶紧登录吧!</p>
        </view>
      </view>
    </view>
    <uni-list>
      <uni-list-item title="铸星" link to="/pages/ucenter/creation/creation"></uni-list-item>
      <uni-list-item title="留言板" link to="/pages/ucenter/messageBoard/messageBoard"></uni-list-item>
      <uni-list-item title="关于星梦" link to="/pages/ucenter/about/about"></uni-list-item>
    </uni-list>
  </view>
</template>

<script>
  export default {
    data() {
      return {
        id: null,
        userName: "",
        onLogin: null
      }
    },
    onLoad() {
      this.getUserInfo();
    },
    onShow() {
      this.getUserInfo();
    },
    methods: {
      loginInfo() {
        if (this.onLogin !== true) {
          uni.navigateTo({
            url: "/pages/ucenter/login/login"
          });
          return;
        }
        uni.navigateTo({
          url: "/pages/ucenter/account/account"
        })
      },
      getUserInfo() {
        let token = uni.getStorageSync("token");
        if (!token) {
          this.onLogin = false;
          return;
        }
        uniCloud.callFunction({
          name: "fun",
          data: {
            api: "getUserInfo",
            token
          }
        }).then(res => {
          if (!res.result.success) {
            throw Error(res.result.errorMessage);
          }
          this.onLogin = true;
          let userInfo = res.result.data;
          this.id = userInfo.id;
          this.userName = userInfo.userName;
        }).catch(e => {
          console.log(e);
          this.onLogin = false;
        })
      }
    }
  }
</script>

<style>
</style>
