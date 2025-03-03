function getCurrentTime() {
    var date = new Date();
    var year = date.getFullYear();
    var month = date.getMonth() + 1; // 月份从0开始，需要加1
    var day = date.getDate();
    var hours = date.getHours();
    var minutes = date.getMinutes();
    var seconds = date.getSeconds();
    var dayOfWeek = date.getDay();

    // 星期数组
    var daysOfWeek = ["星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"];

    // 格式化时间字符串
    return year + "年" + formatTimeComponent(month) + "月" + formatTimeComponent(day) + "日 " +
           formatTimeComponent(hours) + ":" + formatTimeComponent(minutes) + ":" + formatTimeComponent(seconds) + " " +
           daysOfWeek[dayOfWeek];
}

// 格式化时间组件为两位数字
function formatTimeComponent(component) {
    return component < 10 ? "0" + component : component;
}
