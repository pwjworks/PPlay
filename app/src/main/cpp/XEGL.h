//
// Created by pwjworks on 2022/7/2.
//

#pragma once

class XEGL {
public:
    virtual bool Init(void *win) = 0;

    static XEGL *Get();

    virtual void Draw() = 0;

protected:
    XEGL() {}
};
