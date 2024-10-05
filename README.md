# 6502 Emulator

A C++ 6502 emulator With interactive GUI to visualise the internals both step by step, and as a program freely runs.
Developed as part of an NES emulator project [https://github.com/MCFoord/nes_emulator] with the intention of learning GUI development on a smaller project before using that knowledge on the bigger project.

Built on linux, however also runs on windows. 

![](https://github.com/MCFoord/6502_Emulator/raw/master/programscreenshot.png)

## Build Instructions
1. recursive clone the repo
2. entry point CMake file is in the main project directory
3. run the 6502Emulator executable


## Program Use
- add desired program to programs directory
- select program from dropdown
- open one or more memory hex view windows
- run program or execute single intrcutions


## To do
- [ ] refactor control panel to cpu interface to avoid deep nesting of reference passing
- [ ] breakpoint to halt porgram execution
- [ ] file dialog for program selection
- [ ] add executed intruction debug lists
- [ ] add ability to jump forward and backwards in instruction list with changes refelcted in memory and registers  
