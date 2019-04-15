#include <iostream>
#include "bash_color.hpp"

BashColor::BashColor() {}

BashColor::~BashColor() {}

std::string BashColor::getEscapeSequenceForFGColor(COLOR c) {
    std::string fgStart = "\\[\\033[38;5;";
    std::string fgEnd = "m\\]";

    switch (c) {
    case COLOR::GREEN:
        return fgStart + "2" + fgEnd;
    case COLOR::RED:
        return fgStart + "9" + fgEnd;
    case COLOR::BLACK:
        return fgStart + "0" + fgEnd;
    case COLOR::WHITE:
        return fgStart + "231" + fgEnd;
    case COLOR::ORANGE:
        return fgStart + "202" + fgEnd;
    case COLOR::BLUE:
        return fgStart + "39" + fgEnd;
    case COLOR::GREY:
        return fgStart + "245" + fgEnd;
    case COLOR::GREY_DARK:
        return fgStart + "239" + fgEnd;
    case COLOR::GREY_LIGHT:
        return fgStart + "251" + fgEnd;
    case COLOR::YELLOW:
        return fgStart + "190" + fgEnd;
    case COLOR::TRANSPARENT:
        return fgStart + "8" + fgEnd;
    case COLOR::PINK:
        return fgStart + "213" + fgEnd;
    }
    return std::string();
}

std::string BashColor::getEscapeSequenceForBGColor(COLOR c){
    std::string bgStart = "\\[\\033[48;5;";
    std::string bgEnd = "m\\]";

    switch (c){
        case COLOR::GREEN:
            return bgStart + "2" + bgEnd;
        case COLOR::RED:
            return bgStart + "1" + bgEnd;
        case COLOR::BLACK:
            return bgStart + "0" + bgEnd;
        case COLOR::WHITE:
            return bgStart + "231" + bgEnd;
        case COLOR::ORANGE:
            return bgStart + "208" + bgEnd;
        case COLOR::BLUE:
            return bgStart + "39" + bgEnd;
        case COLOR::GREY:
            return bgStart + "245" + bgEnd;
        case COLOR::GREY_DARK:
            return bgStart + "239" + bgEnd;
        case COLOR::GREY_LIGHT:
            return bgStart + "251" + bgEnd;
        case COLOR::YELLOW:
            return bgStart + "3" + bgEnd;
        case COLOR::TRANSPARENT:
            return bgStart + "8" + bgEnd;
        case COLOR::PINK:
            return bgStart + "213" + bgEnd;
    }
    return std::string();
}

std::string BashColor::getResetSequence() {
    return "\\[\\033[0m\\]";
}

std::string BashColor::getBoldSequence() {
    return "\\[\\033[1m\\]";
}

void BashColor::print(std::string s, COLOR fgC, COLOR bgC, bool bold = false) {
    std::string colorString = getEscapeSequenceForFGColor(fgC) + getEscapeSequenceForBGColor(bgC);
    if (bold) {
        colorString += getBoldSequence();
    }
    colorString += s + getResetSequence();
    std::cout << colorString;
}
