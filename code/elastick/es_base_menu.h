#pragma once

class BaseMenu {
public:
    virtual void show() = 0;
    virtual void onNext() = 0;
    virtual void onValidate() = 0;
};
