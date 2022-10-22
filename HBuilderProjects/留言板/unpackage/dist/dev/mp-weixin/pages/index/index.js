"use strict";
var common_vendor = require("../../common/vendor.js");
const _sfc_main = {
  data() {
    return {
      content: "",
      list: this.getList(),
      status: "\u6B63\u5728\u52A0\u8F7D\u7559\u8A00",
      mode: "getMessages",
      timer: null
    };
  },
  onLoad() {
    let token = common_vendor.index.getStorageSync("token");
    if (!token) {
      common_vendor.index.login().then(({
        code
      }) => {
        common_vendor.pn.callFunction({
          name: "fun",
          data: {
            api: "loginWithMp",
            code
          }
        }).then(({
          result
        }) => {
          token = result.token;
          common_vendor.index.setStorageSync("token", token);
          this.getList();
        });
      });
    } else {
      this.getList();
    }
    this.timer = setInterval(() => this.getList(this.mode), 2500);
  },
  onUnload() {
    clearInterval(this.timer);
  },
  methods: {
    getList(api) {
      common_vendor.pn.callFunction({
        name: "fun",
        data: {
          api: api || "getMessages",
          token: common_vendor.index.getStorageSync("token")
        }
      }).then((res) => {
        this.list = res.result.data;
        console.log(this.list);
        this.status = this.list == false ? "\u7559\u8A00\u677F\u662F\u7A7A\u7684" : "\u6240\u6709\u7559\u8A00\u5185\u5BB9";
      });
    },
    publish() {
      this.mode = "getMessages";
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
          api: "publish",
          content: this.content,
          token: common_vendor.index.getStorageSync("token")
        }
      }).then((res) => {
        console.log(res);
        this.status = "\u7559\u8A00\u6210\u529F";
        common_vendor.index.showToast({
          title: "\u7559\u8A00\u6210\u529F",
          icon: "success"
        });
        this.content = "";
      });
    },
    changeMode() {
      if (this.mode === "getMessages") {
        this.mode = "getMyMessages";
        return;
      }
      if (this.mode === "getMyMessages") {
        this.mode = "getMessages";
        return;
      }
    }
  }
};
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return common_vendor.e({
    a: $data.content,
    b: common_vendor.o(($event) => $data.content = $event.detail.value),
    c: common_vendor.o(($event) => $options.publish()),
    d: $data.mode === "getMessages"
  }, $data.mode === "getMessages" ? {} : {}, {
    e: common_vendor.o(($event) => {
      $options.changeMode();
      $options.getList($data.mode);
    }),
    f: common_vendor.t($data.status),
    g: common_vendor.f($data.list, (item, k0, i0) => {
      return common_vendor.e({
        a: common_vendor.t(item.content),
        b: common_vendor.t(item.time),
        c: !item.public
      }, !item.public ? {} : {}, {
        d: item.backgroundColor,
        e: item._id
      });
    })
  });
}
var MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__file", "D:/HBuilderProjects/\u7559\u8A00\u677F/pages/index/index.vue"]]);
wx.createPage(MiniProgramPage);
