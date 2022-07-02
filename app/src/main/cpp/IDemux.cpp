//
// Created by pwjworks on 2022/6/28.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main() {
    while (!isExit) {
        XData d = Read();
        if (d.size > 0) {
            Notify(d);
        }
    }
}
