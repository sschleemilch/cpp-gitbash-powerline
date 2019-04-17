#include <iostream>
extern "C" {    
    #include "git2.h"
}
#include "bash_color.hpp"
#include "unicode_symbols.hpp"
#include "help_functions.hpp"

void printPromptSymbol(int lastCommandReturnCode) {
    if (lastCommandReturnCode == 0) {
        BashColor::print(UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::TRIANGLE_RIGHT),
            BashColor::COLOR::PINK,
            BashColor::COLOR::TRANSPARENT,
            false);
    } else {
        BashColor::print(UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::TRIANGLE_RIGHT),
            BashColor::COLOR::RED,
            BashColor::COLOR::TRANSPARENT,
            false);
    }
}

int main(int argc, char** argv) {
    std::string cwd = std::getenv("PWD");
    std::string home = std::getenv("HOME");

    //git_repository *repo = NULL;
    //int error = git_repository_open(&repo, "/tmp/…");
    BashColor::print(getCWDString(cwd, home),
        BashColor::COLOR::BLACK,
        BashColor::COLOR::BLUE,
        false);
    printPromptSymbol(atoi(argv[1]));
}
