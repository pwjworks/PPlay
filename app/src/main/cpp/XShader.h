//
// Created by pwjworks on 2022/7/2.
//

#pragma once

class XShader {
public:
    virtual bool Init();

    // 获取材质并映射到内存
    void GetTexture(unsigned int index, int width, int height, unsigned char *buf);

    virtual void Draw();

protected:
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0};
};