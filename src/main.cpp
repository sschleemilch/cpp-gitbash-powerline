#include <iostream>
#include <algorithm>



#include "bash_color.hpp"
#include "unicode_symbols.hpp"
#include "help_functions.hpp"
#include "git_repo.hpp"

void printPromptSymbol(int lastCommandReturnCode) {
    std::cout << " ";
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
    std::replace(home.begin(), home.end(), '\\', '/');

    GitRepo repo(cwd);

    BashColor::print(getCWDString(cwd, home),
        BashColor::COLOR::BLACK,
        BashColor::COLOR::BLUE,
        false);

    if (repo.isRepo) {
        BashColor::print(" git ",
            BashColor::COLOR::BLACK,
            BashColor::COLOR::GREEN,
            false);
    }
    printPromptSymbol(atoi(argv[1]));
}
