"use strict";var t=require("../../../common/vendor.js");const e={data:()=>({star:null}),onLoad:function(e){t.index.setNavigationBarTitle({title:e.title}),this.getArticle(e.aid)},methods:{getArticle(e){t.pn.callFunction({name:"fun",data:{api:"getStar",args:{aid:e}}}).then((e=>{!1!==e.result.success?this.star=e.result.data.content:t.index.showToast({title:e.result.errorMessage,icon:"error"})}))}}};var r=t._export_sfc(e,[["render",function(t,e,r,a,n,s){return{a:n.star}}]]);wx.createPage(r);
