"use strict";
var common_vendor = require("../../../common/vendor.js");
const _sfc_main = {
  data() {
    return {
      userName: "",
      password: ""
    };
  },
  onLoad() {
  },
  methods: {
    userLogin() {
      if (!this.userName || !this.password) {
        common_vendor.index.showToast({
          title: "\u554A\uFF0C\u7A7A\u7684?",
          icon: "error"
        });
        return;
      }
      this.login("loginWithUser", {
        userName: this.userName,
        password: this.password
      });
    },
    login(api, data) {
      common_vendor.pn.callFunction({
        name: "fun",
        data: {
          api,
          args: data
        }
      }).then(({
        result
      }) => {
        if (result.data.token) {
          common_vendor.index.setStorageSync("token", result.data.token);
          common_vendor.index.showToast({
            title: "\u8FDB\u5165\u6210\u529F"
          });
          common_vendor.index.navigateBack();
        }
      }).catch((e) => {
        console.log(e);
        common_vendor.index.showToast({
          title: "\u8FDB\u5165\u5931\u8D25",
          icon: "error"
        });
      });
    }
  }
};
if (!Array) {
  const _easycom_uni_easyinput2 = common_vendor.resolveComponent("uni-easyinput");
  _easycom_uni_easyinput2();
}
const _easycom_uni_easyinput = () => "../../../uni_modules/uni-easyinput/components/uni-easyinput/uni-easyinput.js";
if (!Math) {
  _easycom_uni_easyinput();
}
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return {
    a: common_vendor.o(($event) => $data.userName = $event),
    b: common_vendor.p({
      type: "text",
      placeholderStyle: "font-size: 15px;",
      placeholder: "\u8D26\u53F7",
      modelValue: $data.userName
    }),
    c: common_vendor.o(($event) => $data.password = $event),
    d: common_vendor.p({
      type: "password",
      placeholderStyle: "font-size: 15px;",
      placeholder: "\u5BC6\u7801",
      modelValue: $data.password
    }),
    e: common_vendor.o(($event) => $options.userLogin())
  };
}
var MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__file", "D:/HBuilderProjects/\u661F\u68A6/pages/ucenter/login/login.vue"]]);
wx.createPage(MiniProgramPage);
