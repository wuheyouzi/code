module.exports = async (args, db, openId, ctx) => {
  let res = await db.collection("starList").get();
  return res.data;
}
