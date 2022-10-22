module.exports = function formatTime() {
  let time = getDate();
  let year = time.getFullYear();
  let month = time.getMonth() + 1;
  let dates = time.getDate();
  let hour = time.getHours();
  hour = hour < 10 ? '0' + hour : hour;
  let minute = time.getMinutes();
  minute = minute < 10 ? '0' + minute : minute;
  let second = time.getSeconds();
  second = second < 10 ? '0' + second : second;
  return year + '/' + month + '/' + dates + ' ' + hour + ':' + minute + ':' + second;
}

function getDate() {
  let localDate = new Date();
  let timezone = 8; //目标时区时间，东八区   东时区正数 西市区负数
  let offset_GMT = localDate.getTimezoneOffset(); // 本地时间和格林威治的时间差，单位为分钟
  let nowTime = localDate.getTime(); // 本地时间距 1970 年 1 月 1 日午夜（GMT 时间）之间的毫秒数
  let targetDate = new Date(nowTime + offset_GMT * 60 * 1000 + timezone * 60 * 60 * 1000);
  return targetDate;
}
