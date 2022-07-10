//
// Created by pwjworks on 2022/7/2.
//

#pragma once

class XTexture {
public:
    static XTexture *Create();

    virtual bool Init(void *win) = 0;

    virtual void Draw(unsigned char *data[], int width, int height) = 0;
};