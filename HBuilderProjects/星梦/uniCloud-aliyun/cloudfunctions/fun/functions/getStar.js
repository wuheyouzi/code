module.exports = async (args, db, openId, ctx) => {
  let res = await db.collection("stars").where({
    _id: args.aid
  }).get();

  if (!res.data.length) throw Error("star不存在");
  return res.data[0];
}
