let bcrypt = require("bcryptjs");

module.exports = async (args, db, openId, ctx) => {
  if (args.item === "userName") {
    return await db.collection("user").where({
      _id: openId
    }).update({
      userName: args.val
    });
  }

  if (args.item === "password") {
    let hash = await bcrypt.hash(args.val, 10);
    return await db.collection("user").where({
      _id: openId
    }).update({
      hash
    });
  }

  throw Error("此项不能修改");
}
