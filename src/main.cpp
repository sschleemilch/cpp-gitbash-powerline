#include <iostream>
extern "C" {    
    #include "git2.h"
}
#include "bash_color.hpp"
#include "help_functions.hpp"


int main() {
    std::string cwd = std::getenv("PWD");
    std::string home = std::getenv("HOME");

    //git_repository *repo = NULL;
    //int error = git_repository_open(&repo, "/tmp/…");
    BashColor::print(getCWDString(cwd, home),
        BashColor::COLOR::GREEN,
        BashColor::COLOR::BLACK,
        false);
}
