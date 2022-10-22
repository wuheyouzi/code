"use strict";
var common_vendor = require("../../../common/vendor.js");
const _sfc_main = {
  data() {
    return {
      article: ""
    };
  },
  onLoad: function(option2) {
    common_vendor.index.setNavigationBarTitle({
      title: option2.title
    });
    this.getArticle();
  },
  methods: {
    getArticle() {
      common_vendor.pn.callFunction({
        name: "fun",
        data: {
          api: "getArticle",
          args: {
            aid: option.aid
          }
        }
      }).then((res) => {
        this.article = res.result.data[0].content;
      });
    }
  }
};
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return {
    a: $data.article
  };
}
var MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__file", "D:/HBuilderProjects/\u661F\u68A6/pages/stars/article/article.vue"]]);
wx.createPage(MiniProgramPage);
