"use strict";
var common_vendor = require("../../common/vendor.js");
const _sfc_main = {
  data() {
    return {
      list: this.getStars(),
      status: "\u6B63\u5728\u94F8\u5C31\u661F\u6D77",
      timer: null
    };
  },
  onLoad() {
    this.timer = setInterval(() => this.getStars(), 1e4);
  },
  onUnload() {
    clearInterval(this.timer);
  },
  methods: {
    statusHandle() {
      if (this.list !== "") {
        this.status = "\u522B\u70B9\u6211\u5566";
        return;
      }
      this.status = "loading";
      this.getStars();
    },
    getStars() {
      common_vendor.pn.callFunction({
        name: "fun",
        data: {
          api: "getStars"
        }
      }).then((res) => {
        this.list = res.result.success === true ? res.result.data : "";
        this.status = this.list === "" ? "ya! \u83AB\u5F97\u661F\u661F" : "\u6C89\u6D78\u661F\u7684\u5149\u8292";
      });
    },
    navigate(aid, title) {
      common_vendor.index.navigateTo({
        url: `/pages/stars/article/article?aid=${aid}&title=${title}`
      });
    },
    switchChange(e) {
      common_vendor.index.showToast({
        title: "\u5F53\u524D\u662F\u5426\u9009\u4E2D:" + e.value,
        icon: "none"
      });
    }
  }
};
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return {
    a: common_vendor.t($data.status),
    b: common_vendor.o(($event) => $options.statusHandle()),
    c: common_vendor.f($data.list, (item, k0, i0) => {
      return {
        a: common_vendor.t(item.title),
        b: common_vendor.t(item.content),
        c: common_vendor.t(item.writer),
        d: item._id,
        e: common_vendor.o(($event) => $options.navigate(item.aid, item.title), item._id)
      };
    })
  };
}
var MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__file", "D:/HBuilderProjects/\u661F\u68A6/pages/stars/stars.vue"]]);
wx.createPage(MiniProgramPage);
