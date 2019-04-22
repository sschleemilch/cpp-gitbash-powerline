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
    std::string toPrint;
    if (repo.headDetached) {
        toPrint = " " + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::ANCHOR);
        toPrint += repo.commit_id + " ";
        BashColor::print(toPrint,
            BashColor::COLOR::BLACK,
            BashColor::COLOR::ORANGE,
            false);
    } else {
        toPrint = " " + repo.branch + " ";
        toPrint += "(" + repo.commit_id + ") ";
        BashColor::print(toPrint,
            BashColor::COLOR::BLACK,
            BashColor::COLOR::GREEN,
            false);
    }
}

void printRemoteInfos(GitRepo& repo) {
    std::string toPrint;
    std::string arrows = UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::ARROW_UP_DOWN);
    if (repo.ahead == -1 && repo.behind == -1) {
        toPrint = " " + arrows + "? ";
        BashColor::print(toPrint,
            BashColor::COLOR::RED,
            BashColor::COLOR::GREY_DARK,
            false);
    } else if (repo.ahead > 0 && repo.behind == 0){
        toPrint = " " + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::ARROW_UP) + std::to_string(repo.ahead) + " ";
        BashColor::print(toPrint,
            BashColor::COLOR::GREEN,
            BashColor::COLOR::GREY_DARK,
            false);
    } else if (repo.behind > 0 && repo.ahead == 0) {
        toPrint = " " + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::ARROW_DOWN) + std::to_string(repo.behind) + " ";
        BashColor::print(toPrint,
            BashColor::COLOR::RED,
            BashColor::COLOR::GREY_DARK,
            false);
    } else if (repo.ahead == 0 && repo.behind == 0) {
        BashColor::print(" " + arrows + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::CHECK) + " ",
            BashColor::COLOR::GREEN,
            BashColor::COLOR::GREY_DARK,
            false);
    } else {
        toPrint = " " + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::ARROW_UP) + std::to_string(repo.ahead);
        BashColor::print(toPrint,
            BashColor::COLOR::GREEN,
            BashColor::COLOR::GREY_DARK,
            false);
        BashColor::print(UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::LIGHTNING),
            BashColor::COLOR::YELLOW,
            BashColor::COLOR::GREY_DARK,
            false);
        toPrint = std::to_string(repo.behind) + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::ARROW_DOWN) + " ";
        BashColor::print(toPrint,
            BashColor::COLOR::RED,
            BashColor::COLOR::GREY_DARK,
            false);
    }
}

void printStatusInfos(GitRepo& repo){
    int index_changes = repo.index_new;
    index_changes += repo.index_modified;
    index_changes += repo.index_deleted;
    index_changes += repo.index_renamed;
    index_changes += repo.index_typechanged;

    int wt_changes = repo.wt_new;
    wt_changes += repo.wt_modified;
    wt_changes += repo.wt_deleted;
    wt_changes += repo.wt_renamed;
    wt_changes += repo.wt_typechanged;

    std::string toPrint;

    if (index_changes > 0) {
        toPrint = " " + std::to_string(index_changes);
        toPrint += UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::FLAG) + " ";
        BashColor::print(toPrint,
            BashColor::COLOR::BLACK,
            BashColor::COLOR::YELLOW,
            false);
    }
    if (wt_changes > 0) {
        toPrint = " " + std::to_string(wt_changes);
        toPrint += UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::PENCIL) + " ";
        BashColor::print(toPrint,
            BashColor::COLOR::BLACK,
            BashColor::COLOR::ORANGE,
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
        repo.setRemoteInfos();
        printRemoteInfos(repo);
        repo.setStatusInfos();
        printStatusInfos(repo);
    }
    int lastCommandState = 0;
    try {
        lastCommandState = atoi(argv[1]);
    } catch (std::exception const & e) {
        // ignore
    }
    printPromptSymbol(lastCommandState);
}
