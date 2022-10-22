"use strict";
let a;
a = 10;
a = 33;
let b;
b = "hello ts";
let c = true;
function sum(a, b) {
    return a + b;
}
let t;
t = "male";
t = "female";
let x;
let y;
y = 1;
y = "10";
y = 't';
y = true;
let z;
z = 1;
z = "10";
z = 't';
z = true;
let e;
e = "hello";
let s;
s = e;
function fn() {
}
function fn2() {
    throw new Error("error");
}
let o;
let p;
p = { name: "star", age: 10 };
p = { name: "star" };
let q;
q = { name: "star", a: 1, b: 2 };
let d;
d = function (n1, n2) {
    return 10;
};
let arr;
let f;
let g;
let h;
h = ["hello", "star"];
var Gender;
(function (Gender) {
    Gender[Gender["unknown"] = 0] = "unknown";
    Gender[Gender["Male"] = 1] = "Male";
    Gender[Gender["Gender"] = 2] = "Gender";
})(Gender || (Gender = {}));
let i;
i = {
    name: "star",
    gender: Gender.Male
};
console.log(i.gender === Gender.Male);
let j;
j = {
    name: "1",
    age: 10
};
let k;
let l;
