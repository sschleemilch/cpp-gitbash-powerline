#pragma once
#include <string>

class BashColor {
public:
    BashColor();
    ~BashColor();
    enum COLOR {
        GREEN, RED, BLACK, WHITE, ORANGE, BLUE, GREY, GREY_DARK, GREY_LIGHT, YELLOW, TRANSPARENT, PINK
    };
    static void print(std::string, COLOR, COLOR, bool);
private:
    static std::string getEscapeSequenceForFGColor(COLOR);
    static std::string getEscapeSequenceForBGColor(COLOR);
    static std::string getResetSequence();
    static std::string getBoldSequence();
};
