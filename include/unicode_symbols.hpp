#pragma once
#include <string>

class UnicodeSymbols {
public:
    UnicodeSymbols();
    ~UnicodeSymbols();
    enum SYMBOL {
        CROSS,
        ANCHOR,
        LIGHTNING,
        FLAG,
        PENCIL,
        PLUS,
        DELTA,
        ARROW_UP_DOWN,
        CHECK,
        SUN,
        HEART,
        DANGER,
        ARROW_RIGHT,
        ARROW_UP,
        ARROW_DOWN,
        MERGE,
        ARROW_RIGHT_2,
        TRIANGLE_RIGHT
    };
    static std::string getString(SYMBOL);
};
