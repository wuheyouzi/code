<template>
  <view>
    <view class="flex items-center justify-center" style="padding: 20px 0;">
      <image src="../../../static/logo.png" class="flex" style="width: 130px; height: 130px; border-radius: 50%;">
      </image>
    </view>
    <uni-list style="line-height: 1.5;">
      <uni-list-item title="名字" :rightText="userName" @click="changeUserName()" clickable></uni-list-item>
      <uni-list-item title="秘钥" rightText="点此修改" @click="changePassword()" clickable></uni-list-item>
      <uni-list-item title="id" :rightText="id"></uni-list-item>
    </uni-list>

    <uni-popup ref="inputDialog" type="dialog">
      <uni-popup-dialog ref="inputClose" mode="input" title="修改内容" placeholder="请输入修改后想要的内容"
        @confirm="dialogInputConfirm">
      </uni-popup-dialog>
    </uni-popup>
  </view>
</template>

<script>
  export default {
    data() {
      return {
        id: null,
        userName: null,
        item: null
      }
    },
    onLoad() {
      let token = uni.getStorageSync("token");
      if (!token) {
        let pages = getCurrentPages();
        if (pages.length < 2) {
          uni.navigateTo({
            url: "/pages/ucenter/ucenter"
          })
          return;
        }
        uni.navigateBack();
      }

      this.getUserInfo();
    },
    methods: {
      getUserInfo() {
        let token = uni.getStorageSync("token");

        uniCloud.callFunction({
          name: "fun",
          data: {
            api: "getUserInfo",
            token
          }
        }).then(res => {
          if (!res.result.success) {
            throw Error(res.errorMessage);
          }
          this.id = res.result.data.id;
          this.userName = res.result.data.userName;
        }).catch(e => {
          console.log(e);
          uni.showToast({
            icon: 'none',
            title: "获取失败"
          })
        })
      },
      inputDialogToggle() {
        this.$refs.inputDialog.open();
      },
      dialogInputConfirm(val) {
        if (!this.item) {
          uni.showToast({
            icon: 'error',
            title: "对象错误, 请重试"
          })
          this.item = null;
          return;
        }

        if (!val.trim()) {
          uni.showToast({
            icon: "error",
            title: "请输入有效值"
          })
          this.item = null;
          return;
        }

        let token = uni.getStorageSync("token");
        uniCloud.callFunction({
          name: "fun",
          data: {
            api: "updateUserInfo",
            args: {
              item: this.item,
              val
            },
            token
          }
        }).then(res => {
          if (!res.result.success) {
            throw Error(res.result.errorMessage);
          }

          uni.showToast({
            icon: "success",
            title: "修改成功"
          })

          this.getUserInfo();
        }).catch(e => {
          console.log(e);
          uni.showToast({
            icon: "error",
            title: "修改失败"
          })
        })
        this.item = "";
      },
      changeUserName() {
        this.item = "userName";
        this.inputDialogToggle();
      },
      changePassword() {
        this.item = "password";
        this.inputDialogToggle();
      }
    }
  }
</script>

<style>

</style>
