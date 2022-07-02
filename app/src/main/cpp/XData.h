//
// Created by pwjworks on 2022/6/28.
//

#pragma once

struct XData {
    unsigned char *data = 0;
    bool isAudio = false;
    int size = 0;

    void Drop();
};