#include "git_repo.hpp"

GitRepo::GitRepo(std::string cwd) {
    git_libgit2_init();
    repo = NULL;
    isRepo = init(repo, cwd);
}
GitRepo::~GitRepo() {}

bool GitRepo::init(git_repository *repo, std::string cwd) {
    int error;
    git_buf root = {0};
    error = git_repository_discover(&root, cwd.c_str(), 0, NULL);
    if (error < 0) {
        return false;
    }
    error = git_repository_open_ext(&repo, root.ptr, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);
    git_buf_free(&root);
    if (error == 0) {
        return true;
    }
    return false;
}
