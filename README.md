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

To activate the font, you will need to modify your `~/.minttyrc`. Here an example content with a color schema:

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
   PS1_CONTENT="$(<path-to-gitbash-exe>\\<binary> $? $GITBASH_POWERLINE_STATUS 2> /dev/null)"
   PS1="$(echo -e $PS1_CONTENT) "
}

if [ "$TERM" != "linux" ]; then
   PROMPT_COMMAND="_update_ps1; $PROMPT_COMMAND"
fi

function gitbash_powerline_switch_status() {
    if [ "$GITBASH_POWERLINE_STATUS" = --no-status ] ; then
        GITBASH_POWERLINE_STATUS=
    else
        GITBASH_POWERLINE_STATUS=--no-status
    fi
}

alias switch_status=gitbash_powerline_switch_status
```


## OpenSSL 1.1.1b
https://github.com/openssl/openssl

- Install Perl (either ActiveState or Strawberry)

- Install NASM

- Make sure both Perl and NASM are on your %PATH%

- Fire up a Visual Studio Developer Command Prompt with administrative privileges (make sure you use the 32-bit one if you are building 32-bit OpenSSL, or the 64-bit one if you are building 64-bit OpenSSL)

- From the root of the OpenSSL source directory enter perl Configure VC-WIN32, if you want 32-bit OpenSSL or perl Configure VC-WIN64A if you want 64-bit OpenSSL

- Enter nmake

- Enter nmake test

- Enter nmake install

