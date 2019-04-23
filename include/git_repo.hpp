#pragma once
#include "git2.h"
#include <string>

class GitRepo {
public:
    GitRepo();
    ~GitRepo();
    bool is_repo;
    bool head_detached;
    std::string branch;
    std::string commit_id;
    void set_head_infos();
    void set_status_infos();
    void set_remote_infos();
    void init(std::string);
    int ahead;
    int behind;

    int index_changes;
    int wt_changes;
    int wt_added;

private:
    static bool init(git_repository*, std::string);
    git_repository* repo;
    std::string repo_path;
};
