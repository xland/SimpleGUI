"use strip";

import * as sg from "sg";
import * as std from "std";
import * as os from "os";
(function (g) {
    let a = new sg.Window({x:1800,frame:true,shadow:false,title:"我的窗口"});
    //a.close();
    a.addEventListener("resize", (e) => {
        console.log(e);
    })
    console.log(a.close());
})(globalThis);