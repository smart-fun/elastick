#pragma once

class BaseMenu {
public:
    virtual void init() {};
    virtual void deinit() {};
    virtual void show() = 0;
    virtual void update() = 0;
    virtual void onPrevious() = 0;
    virtual void onNext() = 0;
    virtual void onValidate() = 0;
};
