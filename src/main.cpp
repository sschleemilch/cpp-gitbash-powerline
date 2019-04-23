#include <iostream>
#include <algorithm>
#include "bash_color.hpp"
#include "unicode_symbols.hpp"
#include "help_functions.hpp"
#include "git_repo.hpp"

#include "git2.h"

void print_prompt_symbol(int last_command_return_code) {
    std::cout << " ";
    if (last_command_return_code == 0) {
        BashColor::print(UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::TRIANGLE_RIGHT),
            BashColor::COLOR::PINK,
            BashColor::COLOR::TRANSPARENT,
            false);
    } else {
        std::string to_print = "(" + std::to_string(last_command_return_code) + ")";
        to_print += UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::TRIANGLE_RIGHT);
        BashColor::print(to_print,
            BashColor::COLOR::RED,
            BashColor::COLOR::TRANSPARENT,
            false);
    }
}

void print_head_infos(GitRepo& repo, bool show_status) {
    std::string to_print;
    if (repo.head_detached) {
        to_print = " " + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::ANCHOR);
        to_print += repo.commit_id + " ";
        BashColor::print(to_print,
            BashColor::COLOR::BLACK,
            BashColor::COLOR::ORANGE,
            false);
        if (repo.index_changes > 0 || repo.wt_changes > 0 || repo.wt_added > 0) {
            to_print = " " + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::LIGHTNING);
            to_print += " DANGER ";
            to_print += UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::LIGHTNING) + " ";
            BashColor::print(to_print,
                BashColor::COLOR::BLACK,
                BashColor::COLOR::RED,
                true);
        }
    } else {
        BashColor::COLOR bg_color = BashColor::COLOR::GREEN;
        to_print = " ";
        if (!show_status) {
            bg_color = BashColor::COLOR::YELLOW;
            to_print += UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::DELTA) + "?" + " ";
        }
        if (repo.index_changes > 0 || repo.wt_changes > 0 || repo.wt_added > 0) {
            bg_color = BashColor::COLOR::YELLOW;
            to_print += UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::DELTA) + " ";
        }
        to_print += repo.branch + " ";
        to_print += "(" + repo.commit_id + ") ";
        BashColor::print(to_print,
            BashColor::COLOR::BLACK,
            bg_color,
            false);
    }
}

void print_remote_infos(GitRepo& repo) {
    std::string to_print;
    std::string arrows = UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::ARROW_UP_DOWN);
    if (repo.ahead == -1 && repo.behind == -1) {
        to_print = " " + arrows + "? ";
        BashColor::print(to_print,
            BashColor::COLOR::RED,
            BashColor::COLOR::GREY_DARK,
            false);
    } else if (repo.ahead > 0 && repo.behind == 0){
        to_print = " " + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::ARROW_UP) + std::to_string(repo.ahead) + " ";
        BashColor::print(to_print,
            BashColor::COLOR::GREEN,
            BashColor::COLOR::GREY_DARK,
            false);
    } else if (repo.behind > 0 && repo.ahead == 0) {
        to_print = " " + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::ARROW_DOWN) + std::to_string(repo.behind) + " ";
        BashColor::print(to_print,
            BashColor::COLOR::RED,
            BashColor::COLOR::GREY_DARK,
            false);
    } else if (repo.ahead == 0 && repo.behind == 0) {
        BashColor::print(" " + arrows + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::CHECK) + " ",
            BashColor::COLOR::GREEN,
            BashColor::COLOR::GREY_DARK,
            false);
    } else {
        to_print = " " + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::ARROW_UP) + std::to_string(repo.ahead);
        BashColor::print(to_print,
            BashColor::COLOR::GREEN,
            BashColor::COLOR::GREY_DARK,
            false);
        BashColor::print(UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::LIGHTNING),
            BashColor::COLOR::YELLOW,
            BashColor::COLOR::GREY_DARK,
            false);
        to_print = std::to_string(repo.behind) + UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::ARROW_DOWN) + " ";
        BashColor::print(to_print,
            BashColor::COLOR::RED,
            BashColor::COLOR::GREY_DARK,
            false);
    }
}

void print_status_infos(GitRepo& repo){
    std::string to_print;

    if (repo.index_changes > 0) {
        to_print = " " + std::to_string(repo.index_changes);
        to_print += UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::FLAG) + " ";
        BashColor::print(to_print,
            BashColor::COLOR::BLACK,
            BashColor::COLOR::GREEN,
            false);
    }
    if (repo.wt_changes > 0) {
        to_print = " " + std::to_string(repo.wt_changes);
        to_print += UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::PENCIL) + " ";
        BashColor::print(to_print,
            BashColor::COLOR::BLACK,
            BashColor::COLOR::ORANGE,
            false);
    }
    if (repo.wt_added > 0) {
        to_print = " " + std::to_string(repo.wt_added);
        to_print += UnicodeSymbols::getString(UnicodeSymbols::SYMBOL::PLUS) + " ";
        BashColor::print(to_print,
            BashColor::COLOR::BLACK,
            BashColor::COLOR::RED,
            false);
    }
}

int main(int argc, char** argv) {
    bool show_status = true;
    std::string no_status_flag = "--no-status";
    if (argc > 2 && !no_status_flag.compare(argv[2])) {
        show_status = false;
    }
    std::string cwd = std::getenv("PWD");
    std::string home = std::getenv("HOME");
    std::replace(home.begin(), home.end(), '\\', '/');

    GitRepo repo;
    repo.init(cwd);

    BashColor::print(get_cwd_string(cwd, home),
        BashColor::COLOR::BLACK,
        BashColor::COLOR::BLUE,
        false);

    if (repo.is_repo) {
        repo.set_head_infos();
        repo.set_remote_infos();
        if (show_status) {
            repo.set_status_infos();
        }
        print_head_infos(repo, show_status);
        if (show_status) {
            print_status_infos(repo);
        }
        print_remote_infos(repo);
    }
    int lastCommandState = 0;
    try {
        lastCommandState = atoi(argv[1]);
    } catch (std::exception const & e) {
        // ignore
    }
    print_prompt_symbol(lastCommandState);
}
