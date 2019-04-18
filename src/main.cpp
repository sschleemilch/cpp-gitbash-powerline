#include <iostream>
#include <algorithm>

#include "git2.h"

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
    std::replace(home.begin(), home.end(), '\\', '/');
    
    git_libgit2_init();
    int error;
    bool isRepo = false;
    git_buf root = {0};
    error = git_repository_discover(&root, cwd.c_str(), 0, NULL);

    git_repository *repo = NULL;
    error = git_repository_open_ext(&repo, root.ptr, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);
    git_buf_free(&root);
    if (error == 0) {
        isRepo = true;
    }

    BashColor::print(getCWDString(cwd, home),
        BashColor::COLOR::BLACK,
        BashColor::COLOR::BLUE,
        false);
    BashColor::print(UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::QUADRANT_UPPER_LEFT),
        BashColor::COLOR::BLUE,
        BashColor::COLOR::GREEN,
        false);
    BashColor::print(" BRANCH ",
        BashColor::COLOR::BLACK,
        BashColor::COLOR::GREEN,
        false);
    std::cout << " ";
    printPromptSymbol(atoi(argv[1]));
}
