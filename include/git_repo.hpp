#pragma once
#include "git2.h"
#include <string>

class GitRepo {
public:
    GitRepo();
    ~GitRepo();
    bool isRepo;
    bool headDetached;
    std::string branch;
    std::string commit_id;
    void setHEADInfos();
    void setRemoteInfos();
    void init(std::string);
    int ahead;
    int behind;
private:
    static bool init(git_repository*, std::string);
    git_repository* repo;
    std::string repo_path;
};
