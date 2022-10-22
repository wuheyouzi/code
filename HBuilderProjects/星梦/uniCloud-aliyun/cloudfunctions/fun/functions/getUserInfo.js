module.exports = async (args, db, openId, ctx) => {
  let res = await db.collection("user").where({
    _id: openId
  }).get();
  let data = {
    id: res.data[0]._id,
    userName: res.data[0].userName
  }
  if (!data.id) {
    throw Error("用户不存在");
  }

  return data;
}
