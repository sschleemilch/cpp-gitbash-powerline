# cpp-gitbash-powerline

A gitbash-powerline implemented in C++ using libgit2.
Provides several information regarding the git repository currently navigated into such as:
- current branch + commitID or showing that you are on a detached HEAD
- how many commits the current branch is ahead/behind of its origin reference
- modified, staged, untracked files if not switched off with '--no-status'
- warning if on detached HEAD and modified files are present

## Using

### Install and configure a Powerline Font
For being able to use the binary as it is you do need to setup a font that supports the unicode characters
being used. You can find the font I am using in `setup`.

In case of Windows, to activate the font, you will need to modify your `~/.minttyrc`. Here an example content with a color schema:

```
BoldAsFont=no
Font=DejaVu Sans Mono for Powerline
BoldAsColour=yes
FontHeight=13
ForegroundColour=248,248,242
BackgroundColour=40,42,54
Black=0,0,0
BoldBlack=40,42,53
Red=255,85,85
BoldRed=255,110,103
Green=80,250,123
BoldGreen=90,247,142
Yellow=241,250,140
BoldYellow=244,249,157
Blue=202,169,250
BoldBlue=202,169,250
Magenta=255,121,198
BoldMagenta=255,146,208
Cyan=139,233,253
BoldCyan=154,237,254
White=191,191,191
BoldWhite=230,230,230
Term=xterm-256color
Transparency=off
OpaqueWhenFocused=no
```

In case of Unix, you will have the best experience if you change your terminal color-shema to the same colors defined
as the given colors in `.minttyrc`. I recommend playing around with the colors that in the end it just looks good (e.g. use gpick to find the right colors
so that the prompt symbol has transparent background).


### .bashrc adaptions to call the executable

We need to manuplate the `PS1` variable of our bash to call our executable and saving the result in a variable.
Since printing Unicode can be messy on Windows, I decided to leave it to the bash itself to interprete the 
unicode sequences. Therefore, I am calling `echo -e <binary-result>`.
For large repositories, the repository status information can be switched off and on, since a `git status` can
take several seconds (even though the implementation with libgit2 is faster then a normal `git status` on the 
command line!). For that purpose, the following `.bashrc` example also defines a small function to be able to
switch the status of files in the index and in the working tree dynamically and defining a short alias for it.

```bash
GITBASH_POWERLINE_STATUS=
function _update_ps1() {
   PS1_CONTENT="$(<path-to-gitbash-binary> $? $GITBASH_POWERLINE_STATUS 2> /dev/null)"
   PS1="$(echo -e $PS1_CONTENT) "
}


PROMPT_COMMAND="_update_ps1; $PROMPT_COMMAND"


function gitbash_powerline_switch_status() {
    if [ "$GITBASH_POWERLINE_STATUS" = --no-status ] ; then
        GITBASH_POWERLINE_STATUS=
    else
        GITBASH_POWERLINE_STATUS=--no-status
    fi
}

alias switch_status=gitbash_powerline_switch_status
```

## Compiling

### Linux (Ubuntu as example)

- install openssl: `sudo apt install libssl-dev`
- install build-essentials: `sudo apt install build-essentials`
- install cmake: `sudo apt install cmake`

`mkdir build && cd build`
`cmake ..`
`cmake --build .`

### Windows

- I did compile with msvc 16 which is shipped with Visual Studio 2019 Community Edition

`mkdir build && cd build`
`cmake ..`
`cmake --build .`
