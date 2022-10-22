<template>
  <view class="flex items-center justify-center flex-col">
    <h3 style="margin: 70rpx 0;">沉入星境</h3>
    <view class="flex-col inputArea">
      <uni-easyinput type="text" placeholderStyle="font-size: 15px;" v-model="userName" placeholder="名字">
      </uni-easyinput>
      <uni-easyinput style="margin: 30rpx 0;" type="password" placeholderStyle="font-size: 15px;" v-model="password"
        placeholder="秘钥">
      </uni-easyinput>
    </view>
    <view style="margin-top: 60rpx;">
      <button type="primary" size="default" @click="userLogin()" class="w-40 rounded">进入星境</button>
    </view>
  </view>
</template>

<script>
  export default {
    data() {
      return {
        userName: "",
        password: ""
      }
    },
    onLoad() {},
    methods: {
      userLogin() {
        if (!this.userName || !this.password) {
          uni.showToast({
            title: "啊，空的?",
            icon: "error"
          })
          return;
        }
        this.login('loginWithUser', {
          userName: this.userName,
          password: this.password
        })
      },
      login(api, data) {
        uniCloud.callFunction({
          name: "fun",
          data: {
            api,
            args: data
          }
        }).then(({
          result
        }) => {
          if (result.data.token) {
            uni.setStorageSync("token", result.data.token);
            uni.showToast({
              title: "进入成功"
            })
            uni.navigateBack();
          }
        }).catch(e => {
          console.log(e)
          uni.showToast({
            title: "进入失败",
            icon: "error"
          })
        })
      }
    }
  }
</script>

<style>
  .inputArea {
    margin: 0 30rpx;
  }

  .input {
    border-bottom: 1px solid #ccc;
    padding-bottom: 10rpx;
    margin: 39rpx;
  }

  .rounded {
    border-radius: 10px;
  }

  .w-40 {
    width: 10rem
  }
</style>
