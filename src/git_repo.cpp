#include "git_repo.hpp"
#include <iostream>

GitRepo::GitRepo() {
    git_libgit2_init();
    ahead = -1;
    behind = -1;
}
GitRepo::~GitRepo() {}

void GitRepo::setHEADInfos() {
    
    int detached = git_repository_head_detached(repo);
    if (detached == 1) {
        headDetached = true;
    } else {
        headDetached = false;
    }

    git_reference *head = NULL;
    int error = git_repository_head(&head, repo);
    if (error == GIT_EUNBORNBRANCH || error == GIT_ENOTFOUND) {
        branch = "UNKNOWN";
    } else if (!error) {
        branch = git_reference_shorthand(head);
    } else {
        branch = "UNKNOWN";
    }
    git_reference_free(head);
    
    git_oid oid = {0};

    std::string refBranchName = branch;
    if (refBranchName != "HEAD") {
        refBranchName = "refs/heads/" + refBranchName;
    }
    error = git_reference_name_to_id(&oid, repo, refBranchName.c_str());

    if (error == GIT_ENOTFOUND || error == GIT_EINVALIDSPEC) {
        commit_id = "UNKNOWN";
    } else if (!error) {
        char shortsha[10] = {0};
        commit_id = git_oid_tostr(shortsha, 9, &oid);
    } else {
        commit_id = "UNKNOWN";
    }
}

void GitRepo::setRemoteInfos() {
    if (headDetached) {
        return;
    }
    git_oid localOid, originOid;
    std::string localBranch = "refs/heads/" + branch;
    std::string remoteBranch = "refs/remotes/origin/" + branch;
    int error = git_reference_name_to_id(&localOid, repo, localBranch.c_str());
    if (error == GIT_ENOTFOUND || error == GIT_EINVALIDSPEC) {
        return;
    }
    error = git_reference_name_to_id(&originOid, repo, remoteBranch.c_str());
    if (error == GIT_ENOTFOUND || error == GIT_EINVALIDSPEC) {
        return;
    }
    size_t ahead, behind;
    git_graph_ahead_behind(&ahead, &behind, repo, &localOid, &originOid);
    this->ahead = int(ahead);
    this->behind = int(behind);
}

void GitRepo::init(std::string cwd) {
    int error;
    git_buf root = {0};
    error = git_repository_discover(&root, cwd.c_str(), 0, NULL);
    if (error < 0) {
        isRepo = false;
        return;
    }
    error = git_repository_open_ext(&repo, root.ptr, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);
    git_buf_free(&root);
    if (error == 0) {
        isRepo = true;
        return;
    }
    isRepo = false;
}
