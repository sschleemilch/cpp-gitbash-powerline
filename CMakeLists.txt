cmake_minimum_required(VERSION 3.12.1)
project (gitbash-powerline)

set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories("include")

file(GLOB SOURCES "src/*.cpp")

include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
ExternalProject_Add(libgit2
  GIT_REPOSITORY https://github.com/libgit2/libgit2
  GIT_TAG v0.28.1
  GIT_SHALLOW TRUE
  CMAKE_ARGS -DBUILD_CLAR=OFF -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

link_directories(${CMAKE_BINARY_DIR})

add_executable(gitbash-powerline ${SOURCES})
add_dependencies(gitbash-powerline libgit2)

if(WIN32)
	target_link_libraries(gitbash-powerline git2 winhttp rpcrt4 crypt32)
else()
	target_link_libraries(gitbash-powerline git2 pthread z ssl crypto)
endif()
