# ChrisOS
## Author: ChrisB
---
### Build Environment
Kubuntu 20.04

---
### Dependencies:
- i686 cross compiler build system (gcc & ld)
  - Follow the instructions [here](https://wiki.osdev.org/GCC_Cross-Compiler)
- qemu
  - Acquire the newest version from following the instructions [here](https://www.qemu.org/download/)
  
---

### Important scripts:
- build.sh
  - Builds all libraries and kernel
- clean.sh
  - Removes all build files
- headers.sh
  - Installs source code headers
- iso.sh
  - Creates the iso file for the OS
- qemu.sh
  - Builds & runs OS using qemu emulator