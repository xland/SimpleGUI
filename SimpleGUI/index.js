"use strip";

import * as os from "os";
(function(g){
    os.remove("c:\\1.txt");
    console.log(123);
})(globalThis);