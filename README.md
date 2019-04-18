# cpp-gitbash-powerline

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


