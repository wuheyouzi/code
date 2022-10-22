<template>
  <view>
    <unicloud-db where="state == true || user_id._id == $cloudEnv_uid" v-slot:default="{data, loading, error, options}"
      collection="guestbook, uni-id-users" field="_id, text, state, user_id.nickname, user_id.avatar_file, user_id._id">
      <view v-if="error">{{error.message}}</view>
      <view v-else>
        <view v-for="(item, index) in data" :key="index" class="item">
          <view class="main">
            <!-- <cloud-image :src="item.user_id[0].avatar_file.url"></cloud-image> -->
            <view>
              <text class="nickname">{{item.user_id[0].nickname}}</text>
              <text>{{item.text}}</text>
            </view>
            <text>{{item.state ? "审核通过" : "审核中"}}</text>
          </view>
        </view>
      </view>
    </unicloud-db>
    <button type="default" @click="add">添加</button>
  </view>
</template>

<script>
  export default {
    data() {
      return {

      }
    },
    methods: {
      add() {
        const db = uniCloud.database();
        const guestbookTable = db.collection('guestbook')
        guestbookTable.add({
          "text": "这是第一条数据",
          // "state": false,
          // "user_id": "123456"
        })
      }
    }
  }
</script>

<style>

</style>
