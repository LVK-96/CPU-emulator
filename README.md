# CPU emulator
Little project I did to teach myself computer architecture. WIP.

Based on Ben Eater's excellent [video series](https://www.youtube.com/playlist?list=PLowKtXNTBypGqImE405J2565dvjafglHU).

## Dev environment setup
Requires [cmake](https://cmake.org/).

> create a build dir and generate makefile
```bash
mkdir build && cd build
cmake ../src # generate makefile
```

> Build the program and run
```bash
make
./CpuEmulator
```
> The emulator runs the program in `test/test.asm`


## TODO
* Proper testing :D
* Add documentation for instuction formats
* GUI

