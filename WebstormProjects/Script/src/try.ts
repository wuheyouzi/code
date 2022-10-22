//import {} from ""

let a: number;

a = 10;
a = 33;

let b: string;
b = "hello ts";

let c = true;

function sum(a: number, b: number): number {
    return a + b;
}

let t: "male" | "female";
t = "male";
t = "female";

let x: boolean | string;

let y: any; // 关闭TS类型检测
y = 1;
y = "10";
y = 't';
y = true;

let z;
z = 1;
z = "10";
z = 't';
z = true;

let e: unknown;
e = "hello";

let s: string;

// if (typeof e == "string") {
//     s = e;
// }
//s = e as string;
s = <string> e;

function fn(): void {
    //return;
}

function fn2(): never { // 无返回，报错用
    throw new Error("error");
}

let o: object; // 在js/ts中，万物皆对象

let p: {name: string, age?: number}; // ? 表示属性可选
p = {name: "star", age: 10};
p = {name: "star"};

let q: {name: string, [property: string]: any};
q = {name: "star", a: 1, b: 2};

let d: (a: number, b: number) => number;
d = function (n1, n2) {
    return 10;
}

let arr: string[];

let f: number[];

let g: Array <number>;

let h: [string, string];
h = ["hello", "star"];

enum Gender{
    unknown,
    Male,
    Gender
}

let i: {name: string, gender: Gender}
i = {
    name: "star",
    gender: Gender.Male
}

console.log(i.gender === Gender.Male);

let j: {name: string} & {age: number};
j = {
    name: "1",
    age: 10
}

type mytype = 1 | 2 | 3 | 4 | 5;
let k: mytype;
let l: mytype;

