#pragma once
#include "git2.h"
#include <string>

class GitRepo {
public:
    GitRepo(std::string);
    ~GitRepo();
    bool isRepo;
private:
    static bool init(git_repository*, std::string);
    git_repository *repo;
};
