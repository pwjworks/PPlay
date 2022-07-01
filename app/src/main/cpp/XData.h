//
// Created by pwjworks on 2022/6/28.
//

#pragma once

struct XData {
    unsigned char *data = 0;
    int size = 0;

    void Drop();
};