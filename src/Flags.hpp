#pragma once

class Flags {

public:
    Flags();

    void SetIndex(int index, bool value);
    bool GetIndex(int index);
    bool HasError();
private:
    unsigned char data;
};
