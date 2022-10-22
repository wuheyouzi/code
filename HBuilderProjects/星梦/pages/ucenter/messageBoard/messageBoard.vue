<template>
  <view>
    <view class="flex justify-center items-center inputArea">
      <view class="flex flex-row">
        <input type="text" class="flex input" style="width: 480rpx" v-model="content" placeholder="在这里写上你的留言" />
        <button type="primary" class="flex" @click="checkToken(), publish()" size="mini"
          style="margin-left: 10px;">发布</button>
      </view>
    </view>
    <view class="flex justify-center items-center status">
      <text>{{status}}</text>
    </view>
    <view class="flex justify-center items-center flex-col-reverse scroll-smooth">
      <view v-for="item in list" :key="item._id">
        <view class="flex flex-row box" :style="{background: item.backgroundColor}">
          <view>
            <view style="font-size: 1.3rem; word-break: break-all;">{{item.content}}</view>
            <view style="font-size: 1rem;">{{item.time}}</view>
          </view>
        </view>
      </view>
    </view>
  </view>
</template>

<script>
  export default {
    data() {
      return {
        content: '',
        list: this.getList(),
        status: "正在加载留言",
        timer: null,
        onLogin: false
      }
    },
    onLoad() {
      this.timer = setInterval(() => this.getList(), 2500);
    },
    onUnload() {
      clearInterval(this.timer)
    },
    onShow() {
      if (!this.onLogin) {
        this.onLogin = true;
        if (this.content && uni.getStorageSync("token")) {
          this.publish();
        }
      }
    },
    methods: {
      checkToken() {
        let token = uni.getStorageSync('token');
        if (!token) {
          uni.showToast({
            title: "请先登录",
            icon: "error"
          })
          uni.navigateTo({
            url: "/pages/ucenter/login/login"
          })
          this.onLogin = true;
          return;
        }
      },
      getList(api) {
        uniCloud.callFunction({
          name: 'fun',
          data: {
            api: api || "getMessages"
          }
        }).then(res => {
          this.list = res.result.data;
          this.status = this.list == false ? "留言板是空的" : "所有留言内容";
        })
      },
      publish() {
        if (this.onLogin === false) return;
        if (!this.content.trim()) {
          uni.showToast({
            title: "留言无效",
            icon: "error"
          })
          this.status = "留言无效";
          return;
        }
        uniCloud.callFunction({
          name: 'fun',
          data: {
            api: 'addMessage',
            args: {
              content: this.content
            },
            token: uni.getStorageSync("token")
          }
        }).then(res => {
          if (res.result.success === false) {
            throw Error(res.result.errorMessage);
          }
          this.status = "留言成功";
          uni.showToast({
            title: "留言成功",
            icon: "success"
          })
          this.content = "";
        }).catch(e => {
          console.log(e);
          uni.showToast({
            title: "留言失败",
            icon: "error"
          })
        })
      }
    }
  }
</script>

<style>
  .inputArea {
    padding-top: 30rpx;
  }

  .input {
    border-bottom: 1px solid #ccc;
    padding: 3rpx;
    flex: 1;
  }

  .status {
    padding: 26rpx;
  }

  .title {
    font-size: 36rpx;
    color: #8f8f94;
  }

  .box {
    margin: 23rpx 48rpx;
    border-bottom: 1px solid #ccc;
    padding: 38rpx;
    border-radius: 60rpx;
    line-height: 2.85;
    min-height: 7rem;
    width: 560rpx;
  }
</style>
