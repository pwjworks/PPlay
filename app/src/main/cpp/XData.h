//
// Created by pwjworks on 2022/6/28.
//

#pragma once

struct XData {
    unsigned char *data = 0;
    unsigned char *datas[8] = {0};
    bool isAudio = false;
    int width = 0;
    int height = 0;
    int size = 0;

    void Drop();
};