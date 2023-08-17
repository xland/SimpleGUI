"use strip";

import * as sg from "sg";
import * as std from "std";
import * as os from "os";
(function (g) {
    let a = new sg.Window({ x: 1800, frame: false, shadow: true, title: "我的窗口", captionArea: [{ x0: 0, y0: 0, x1: 100, y1: 100 },{ x0: 200, y0: 200, x1: 100, y1: 100 }] });
    //a.close();
    a.addEventListener("resize", (e) => {
        console.log(e);
    })
    console.log(a.close());
})(globalThis);