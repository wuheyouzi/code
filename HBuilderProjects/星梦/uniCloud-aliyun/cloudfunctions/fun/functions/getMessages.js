module.exports = async (args, db, openId, ctx) => {
  let res = await db.collection("messages").where({
    public: true
  }).get();

  return res.data;
}
