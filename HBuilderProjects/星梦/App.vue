<script>
  export default {
    onLaunch: function() {
      console.log('星空下，是无尽星海，欢迎来到星梦')
      console.log('App Launch')
    },
    onLoad: function() {
      console.log('App Load')
    },
    onShow: function() {
      console.log('App Show')
    },
    onHide: function() {
      console.log('App Hide')
    }
  }
</script>

<style>
  .flex {
    /* flex布局 */
    display: flex;
  }

  .flex-row {
    /* flex布局 横排列 */
    flex-direction: row;
  }

  .flex-col {
    /* flex布局 竖排列 */
    flex-direction: column;
  }

  .flex-col-reverse {
    /* flex布局 竖翻转 */
    flex-direction: column-reverse;
  }

  .items-center {
    /* flex布局 x轴居中 */
    align-items: center;
  }

  .justify-center {
    /* flex y轴居中 */
    justify-content: center;
  }

  .scroll-smooth {
    /* 滑动效果 */
    scroll-behavior: smooth;
  }
</style>
