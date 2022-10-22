let jwt = require("jsonwebtoken");
let fs = require("fs");
let files = fs.readdirSync(__dirname + "/functions");
let Fun = {};
files.map((filename) => {
  let name = filename.replace(".js", "");
  Object.defineProperty(Fun, name, {
    value: require("./functions/" + filename)
  });
});
let db = uniCloud.database({
  throwOnNotFound: false
});
let env = require("./env.js");

exports.main = async (event, context) => {
  try {
    let {
      api,
      args,
      token
    } = event.body ? JSON.parse(event.body) : event;

    if (typeof Fun[api] !== "function") {
      throw Error("No api");
    }

    let auth = {};
    if (!token && !api.startsWith("login") && !api.startsWith("get")) {
      throw Error('请登录后再操作');
    } else if (token) {
      auth = jwt.verify(token.replace("Bearer ", ""), env.ADMIN_SECRET);
    }

    let data = await Fun[api](args, db, auth.userId, {
      cloud: uniCloud,
      auth,
      env
    });
    return {
      success: true,
      data
    };
  } catch (error) {
    console.log(error);
    return {
      success: false,
      errorMessage: error.message
    }
  }
};
