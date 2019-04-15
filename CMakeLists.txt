cmake_minimum_required(VERSION 3.14.2)
project (gitbash-powerline)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(libgit2
  GIT_REPOSITORY https://github.com/libgit2/libgit2
  GIT_TAG v0.28.1
  CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DBUILD_CLAR=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)
include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

add_executable(gitbash-powerline ${SOURCES})
add_dependencies(gitbash-powerline libgit2)

target_link_libraries(gitbash-powerline git2)
