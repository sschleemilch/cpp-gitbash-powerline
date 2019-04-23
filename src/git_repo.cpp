#include "git_repo.hpp"
#include <iostream>

GitRepo::GitRepo() {
    git_libgit2_init();
    ahead = -1;
    behind = -1;
    index_changes = 0;
    wt_changes = 0;
    wt_added = 0;
    repo_root = "";
}
GitRepo::~GitRepo() {}

void GitRepo::set_head_infos() {
    
    int detached = git_repository_head_detached(repo);
    if (detached == 1) {
        head_detached = true;
    } else {
        head_detached = false;
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

void GitRepo::set_remote_infos() {
    if (head_detached) {
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

void GitRepo::set_status_infos() {
    git_status_list *status;
    git_status_options statusopt;
    git_status_init_options(&statusopt, GIT_STATUS_OPTIONS_VERSION);
    statusopt.flags = GIT_STATUS_OPT_EXCLUDE_SUBMODULES;
    statusopt.flags |= GIT_STATUS_OPT_INCLUDE_UNTRACKED;
    statusopt.flags |= GIT_STATUS_OPT_NO_REFRESH;

    //GIT_STATUS_SHOW_INDEX_ONLY
    //GIT_STATUS_SHOW_WORKDIR_ONLY
    statusopt.show  = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;

    git_status_list_new(&status, repo, &statusopt);

    size_t i, maxi = git_status_list_entrycount(status);
    const git_status_entry *s;

    for (i = 0; i < maxi; i++) {
        s = git_status_byindex(status, i);
        
        if (s->status == GIT_STATUS_CURRENT)
            continue;

        // index status
        if (s->status & GIT_STATUS_INDEX_NEW)
            index_changes++;
        if (s->status & GIT_STATUS_INDEX_MODIFIED)
            index_changes++;
        if (s->status & GIT_STATUS_INDEX_DELETED)
            index_changes++;
        if (s->status & GIT_STATUS_INDEX_RENAMED)
            index_changes++;
        if (s->status & GIT_STATUS_INDEX_TYPECHANGE)
            index_changes++;

        // working tree status
        if (s->status & GIT_STATUS_WT_MODIFIED)
            wt_changes++;
        if (s->status & GIT_STATUS_WT_DELETED)
            wt_changes++;
        if (s->status & GIT_STATUS_WT_RENAMED)
            wt_changes++;
        if (s->status & GIT_STATUS_WT_TYPECHANGE)
            wt_changes++;
        if (s->status == GIT_STATUS_WT_NEW)
            wt_added++;
    }
    git_status_list_free(status);
}

void GitRepo::init(std::string cwd) {
    int error;
    git_buf root = {0};
    error = git_repository_discover(&root, cwd.c_str(), 0, NULL);
    if (error < 0) {
        is_repo = false;
        return;
    }
    repo_root = root.ptr;
    error = git_repository_open_ext(&repo, root.ptr, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);
    git_buf_free(&root);
    if (error == 0) {
        is_repo = true;
        return;
    }
    is_repo = false;
}
