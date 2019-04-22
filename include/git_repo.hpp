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
    void setStatusInfos();
    void setRemoteInfos();
    void init(std::string);
    int ahead;
    int behind;

    int index_new;
    int index_modified;
    int index_deleted;
    int index_renamed;
    int index_typechanged;

    int wt_new;
    int wt_modified;
    int wt_deleted;
    int wt_renamed;
    int wt_typechanged;
private:
    static bool init(git_repository*, std::string);
    git_repository* repo;
    std::string repo_path;
};
