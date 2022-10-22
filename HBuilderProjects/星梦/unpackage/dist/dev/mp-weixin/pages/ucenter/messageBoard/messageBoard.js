"use strict";
var common_vendor = require("../../../common/vendor.js");
const _sfc_main = {
  data() {
    return {
      content: "",
      list: this.getList(),
      status: "\u6B63\u5728\u52A0\u8F7D\u7559\u8A00",
      timer: null,
      onLogin: false
    };
  },
  onLoad() {
    this.timer = setInterval(() => this.getList(), 2500);
  },
  onUnload() {
    clearInterval(this.timer);
  },
  onShow() {
    if (!this.onLogin) {
      this.onLogin = true;
      if (this.content && common_vendor.index.getStorageSync("token")) {
        this.publish();
      }
    }
  },
  methods: {
    checkToken() {
      let token = common_vendor.index.getStorageSync("token");
      if (!token) {
        common_vendor.index.showToast({
          title: "\u8BF7\u5148\u767B\u5F55",
          icon: "error"
        });
        common_vendor.index.navigateTo({
          url: "/pages/ucenter/login/login"
        });
        this.onLogin = true;
        return;
      }
    },
    getList(api) {
      common_vendor.pn.callFunction({
        name: "fun",
        data: {
          api: api || "getMessages"
        }
      }).then((res) => {
        this.list = res.result.data;
        this.status = this.list == false ? "\u7559\u8A00\u677F\u662F\u7A7A\u7684" : "\u6240\u6709\u7559\u8A00\u5185\u5BB9";
      });
    },
    publish() {
      if (this.onLogin === false)
        return;
      if (!this.content.trim()) {
        common_vendor.index.showToast({
          title: "\u7559\u8A00\u65E0\u6548",
          icon: "error"
        });
        this.status = "\u7559\u8A00\u65E0\u6548";
        return;
      }
      common_vendor.pn.callFunction({
        name: "fun",
        data: {
          api: "addMessage",
          args: {
            content: this.content
          },
          token: common_vendor.index.getStorageSync("token")
        }
      }).then((res) => {
        console.log(res.result);
        if (res.result.success === false) {
          throw Error();
        }
        this.status = "\u7559\u8A00\u6210\u529F";
        common_vendor.index.showToast({
          title: "\u7559\u8A00\u6210\u529F",
          icon: "success"
        });
        this.content = "";
      }).catch((e) => {
        console.log(e);
        common_vendor.index.showToast({
          title: "\u7559\u8A00\u5931\u8D25",
          icon: "error"
        });
      });
    }
  }
};
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return {
    a: $data.content,
    b: common_vendor.o(($event) => $data.content = $event.detail.value),
    c: common_vendor.o(($event) => ($options.checkToken(), $options.publish())),
    d: common_vendor.t($data.status),
    e: common_vendor.f($data.list, (item, k0, i0) => {
      return {
        a: common_vendor.t(item.content),
        b: common_vendor.t(item.time),
        c: item.backgroundColor,
        d: item._id
      };
    })
  };
}
var MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__file", "D:/HBuilderProjects/\u661F\u68A6/pages/ucenter/messageBoard/messageBoard.vue"]]);
wx.createPage(MiniProgramPage);
