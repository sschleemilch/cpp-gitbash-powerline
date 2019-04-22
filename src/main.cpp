#include <iostream>
#include <algorithm>

#include "bash_color.hpp"
#include "unicode_symbols.hpp"
#include "help_functions.hpp"
#include "git_repo.hpp"

#include "git2.h"

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

void printHEADInfos(GitRepo& repo) {
    if (repo.headDetached) {
        std::string toPrint;
        toPrint = " " + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::ANCHOR);
        toPrint += repo.commit_id + " ";
        BashColor::print(toPrint,
            BashColor::COLOR::BLACK,
            BashColor::COLOR::ORANGE,
            false);
    } else {
        BashColor::print(" " + repo.branch + " ",
            BashColor::COLOR::BLACK,
            BashColor::COLOR::GREEN,
            false);
    }
}

int main(int argc, char** argv) {
    std::string cwd = std::getenv("PWD");
    std::string home = std::getenv("HOME");
    std::replace(home.begin(), home.end(), '\\', '/');

    GitRepo repo;
    repo.init(cwd);

    BashColor::print(getCWDString(cwd, home),
        BashColor::COLOR::BLACK,
        BashColor::COLOR::BLUE,
        false);

    if (repo.isRepo) {
        repo.setHEADInfos();
        printHEADInfos(repo);
    }
    int lastCommandState = 0;
    try {
        lastCommandState = atoi(argv[1]);
    } catch (std::exception const & e) {
        // ignore
    }
    printPromptSymbol(lastCommandState);
}
