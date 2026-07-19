# Linity OS

## Supported Architectures

| Architecture | Status | Boot Protocol |
|---|---|---|
| x86_64 | In development | Limine |

## Project Status

The project is under active development. I am currently working on memory management.

## Project Goals

* Support multiple architectures
* Understand how operating systems work
* Provide POSIX support
* Stay true to the UNIX philosophy
* Run DOOM

## Planned Components

* PMM
* VMM
* Scheduler
* Driver Support
* Basic Drivers
* Shell
* POSIX Support

## Getting the Source Code

Clone the project using Git:

```bash
git clone https://github.com/Xolmir/Linity-OS.git
cd Linity-OS
```

## Requirements

The following tools are required to build the project:

* GCC
* GNU ld
* objcopy
* NASM
* QEMU
* xorriso
* tar
* curl
* make

> [!NOTE]
> If your compiler tools cannot generate code for the target architecture, you may need to replace `gcc`, `ld`, and `objcopy` with the appropriate cross-compiler versions.

## Make Targets

| Command | Description |
|---|---|
| `make` | Builds the project |
| `make run` | Runs the operating system in QEMU |
| `make kernel` | Builds only the kernel |
| `make iso` | Creates a bootable ISO image |
| `make doctor` | Checks for missing development tools and dependencies |
| `make clean` | Removes generated build files |

## Project Directories and Files

| Directory or File | Description |
|---|---|
| `arch/` | Contains architecture-specific code |
| `boot/` | Contains architecture-specific files used during boot |
| `include/` | Contains header files for the architectures and the kernel |
| `kernel/` | Contains kernel code that is kept as hardware-independent as possible |
| `toolchain/` | Toolchains required by the project are downloaded into this directory |
| `makefile` | Main build file |

## Usage Warning

> [!WARNING]
> Linity OS is not yet suitable for daily use. Testing it on real hardware is entirely your responsibility.

## License

This project is licensed under the **GNU General Public License v3.0**.

See the [`LICENSE`](LICENSE) file for more information.