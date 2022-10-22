<template>
  <view>
    <h3 class="flex items-center justify-center" style="padding: 40rpx;">开发路上，星芒照耀</h3>
    <uni-card padding="50rpx" class="flex flex-row">
      <view v-for="person in list">
        <view class="flex flex-row" style="padding-bottom: 20px;">
          <image class="flex" :src="person.picPath"></image>
          <view class="flex flex-col justify-center" style="padding-left: 8rpx;">
            <view class="flex" style="padding-left: 20rpx; font-size: 35rpx; padding-bottom: 3px;">{{person.name}}
            </view>
            <text class="flex" style="padding-left: 20rpx;">--{{person.describe}}</text>
          </view>
        </view>
      </view>
    </uni-card>
  </view>
</template>

<script>
  export default {
    data() {
      return {
        list: [{
          "name": "Victor",
          "describe": "方向指导，问题解答",
          "picPath": "../../../static/康文昌.jpg"
        }, {
          "name": "小河酱",
          "describe": "ui设计指导",
          "picPath": "../../../static/小河酱.jpg"
        }, {
          "name": "无聊的霜霜",
          "describe": "问题讨论",
          "picPath": "../../../static/无聊的霜霜.jpg"
        }]
      }
    },
    methods: {

    }
  }
</script>

<style>
  image {
    width: 170rpx;
    height: 170rpx;
    border-radius: 50%;
  }
</style>
