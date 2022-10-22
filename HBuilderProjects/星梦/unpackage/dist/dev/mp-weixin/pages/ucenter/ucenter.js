"use strict";
var common_vendor = require("../../common/vendor.js");
const _sfc_main = {
  data() {
    return {
      id: null,
      userName: "",
      onLogin: null
    };
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
        common_vendor.index.navigateTo({
          url: "/pages/ucenter/login/login"
        });
        return;
      }
      common_vendor.index.navigateTo({
        url: "/pages/ucenter/account/account"
      });
    },
    getUserInfo() {
      let token = common_vendor.index.getStorageSync("token");
      if (!token) {
        this.onLogin = false;
        return;
      }
      common_vendor.pn.callFunction({
        name: "fun",
        data: {
          api: "getUserInfo",
          token
        }
      }).then((res) => {
        if (!res.result.success) {
          throw Error(res.result.errorMessage);
        }
        this.onLogin = true;
        let userInfo = res.result.data;
        this.id = userInfo.id;
        this.userName = userInfo.userName;
      }).catch((e) => {
        console.log(e);
        this.onLogin = false;
      });
    }
  }
};
if (!Array) {
  const _easycom_uni_list_item2 = common_vendor.resolveComponent("uni-list-item");
  const _easycom_uni_list2 = common_vendor.resolveComponent("uni-list");
  (_easycom_uni_list_item2 + _easycom_uni_list2)();
}
const _easycom_uni_list_item = () => "../../uni_modules/uni-list/components/uni-list-item/uni-list-item.js";
const _easycom_uni_list = () => "../../uni_modules/uni-list/components/uni-list/uni-list.js";
if (!Math) {
  (_easycom_uni_list_item + _easycom_uni_list)();
}
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return common_vendor.e({
    a: $data.onLogin === null
  }, $data.onLogin === null ? {} : $data.onLogin === true ? common_vendor.e({
    c: common_vendor.t($data.userName),
    d: $data.id
  }, $data.id ? {
    e: common_vendor.t($data.id)
  } : {}) : {}, {
    b: $data.onLogin === true,
    f: common_vendor.o(($event) => $options.loginInfo()),
    g: common_vendor.p({
      title: "\u7559\u8A00\u677F",
      link: true,
      to: "/pages/ucenter/messageBoard/messageBoard"
    }),
    h: common_vendor.p({
      title: "\u5173\u4E8E\u661F\u68A6",
      link: true,
      to: ""
    })
  });
}
var MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__file", "D:/HBuilderProjects/\u661F\u68A6/pages/ucenter/ucenter.vue"]]);
wx.createPage(MiniProgramPage);
