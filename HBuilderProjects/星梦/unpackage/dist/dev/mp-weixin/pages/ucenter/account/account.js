"use strict";
var common_vendor = require("../../../common/vendor.js");
const _sfc_main = {
  data() {
    return {
      id: null,
      userName: null,
      item: null
    };
  },
  onLoad() {
    let token = common_vendor.index.getStorageSync("token");
    if (!token) {
      let pages = getCurrentPages();
      if (pages.length < 2) {
        common_vendor.index.navigateTo({
          url: "/pages/ucenter/ucenter"
        });
        return;
      }
      common_vendor.index.navigateBack();
    }
    this.getUserInfo();
  },
  methods: {
    getUserInfo() {
      let token = common_vendor.index.getStorageSync("token");
      common_vendor.pn.callFunction({
        name: "fun",
        data: {
          api: "getUserInfo",
          token
        }
      }).then((res) => {
        if (!res.result.success) {
          throw Error(res.errorMessage);
        }
        this.id = res.result.data.id;
        this.userName = res.result.data.userName;
      }).catch((e) => {
        console.log(e);
        common_vendor.index.showToast({
          icon: "none",
          title: "\u83B7\u53D6\u5931\u8D25"
        });
      });
    },
    inputDialogToggle() {
      this.$refs.inputDialog.open();
    },
    dialogInputConfirm(val) {
      if (!this.item) {
        common_vendor.index.showToast({
          icon: "error",
          title: "\u5BF9\u8C61\u9519\u8BEF, \u8BF7\u91CD\u8BD5"
        });
        this.item = null;
        return;
      }
      if (!val.trim()) {
        common_vendor.index.showToast({
          icon: "error",
          title: "\u8BF7\u8F93\u5165\u6709\u6548\u503C"
        });
        this.item = null;
        return;
      }
      let token = common_vendor.index.getStorageSync("token");
      common_vendor.pn.callFunction({
        name: "fun",
        data: {
          api: "updateUserInfo",
          args: {
            item: this.item,
            val
          },
          token
        }
      }).then((res) => {
        if (!res.result.success) {
          throw Error(res.result.errorMessage);
        }
        common_vendor.index.showToast({
          icon: "success",
          title: "\u4FEE\u6539\u6210\u529F"
        });
        this.getUserInfo();
      }).catch((e) => {
        console.log(e);
        common_vendor.index.showToast({
          icon: "error",
          title: "\u4FEE\u6539\u5931\u8D25"
        });
      });
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
};
if (!Array) {
  const _easycom_uni_list_item2 = common_vendor.resolveComponent("uni-list-item");
  const _easycom_uni_list2 = common_vendor.resolveComponent("uni-list");
  const _easycom_uni_popup_dialog2 = common_vendor.resolveComponent("uni-popup-dialog");
  const _easycom_uni_popup2 = common_vendor.resolveComponent("uni-popup");
  (_easycom_uni_list_item2 + _easycom_uni_list2 + _easycom_uni_popup_dialog2 + _easycom_uni_popup2)();
}
const _easycom_uni_list_item = () => "../../../uni_modules/uni-list/components/uni-list-item/uni-list-item.js";
const _easycom_uni_list = () => "../../../uni_modules/uni-list/components/uni-list/uni-list.js";
const _easycom_uni_popup_dialog = () => "../../../uni_modules/uni-popup/components/uni-popup-dialog/uni-popup-dialog.js";
const _easycom_uni_popup = () => "../../../uni_modules/uni-popup/components/uni-popup/uni-popup.js";
if (!Math) {
  (_easycom_uni_list_item + _easycom_uni_list + _easycom_uni_popup_dialog + _easycom_uni_popup)();
}
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return {
    a: common_vendor.o(($event) => $options.changeUserName()),
    b: common_vendor.p({
      title: "\u7528\u6237\u540D",
      rightText: $data.userName,
      clickable: true
    }),
    c: common_vendor.o(($event) => $options.changePassword()),
    d: common_vendor.p({
      title: "\u5BC6\u7801",
      rightText: "\u70B9\u6B64\u4FEE\u6539",
      clickable: true
    }),
    e: common_vendor.p({
      title: "id",
      rightText: $data.id
    }),
    f: common_vendor.sr("inputClose", "5b0ee4ec-5,5b0ee4ec-4"),
    g: common_vendor.o($options.dialogInputConfirm),
    h: common_vendor.p({
      mode: "input",
      title: "\u4FEE\u6539\u5185\u5BB9",
      placeholder: "\u8BF7\u8F93\u5165\u4FEE\u6539\u540E\u60F3\u8981\u7684\u5185\u5BB9"
    }),
    i: common_vendor.sr("inputDialog", "5b0ee4ec-4"),
    j: common_vendor.p({
      type: "dialog"
    })
  };
}
var MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__file", "D:/HBuilderProjects/\u661F\u68A6/pages/ucenter/account/account.vue"]]);
wx.createPage(MiniProgramPage);
