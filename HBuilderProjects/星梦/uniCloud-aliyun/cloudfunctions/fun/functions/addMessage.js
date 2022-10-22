let formatTime = require("time");

module.exports = async (args, db, openId, ctx) => {
  let dateTime = formatTime();

  return await db.collection("messages").add({
    content: args.content,
    time: dateTime,
    backgroundColor: getColor(),
    public: true,
    userId: openId
  })
}
const colorArray = ["#b0d5df", "#f0a1a8", "#f8d86a", "#add5a2", "#58C9B9", "#ffbbd6", "#80deea", "#FFEFBA", "#ecc0cd",
  "#93b5cf"
];
const ColorArrayLen = colorArray.length;

function getColor() {
  let randomNum = Math.random() * (ColorArrayLen - 1);
  let num = Math.round(randomNum);
  return colorArray[num];
}
