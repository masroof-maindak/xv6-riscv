# xv6

xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern RISC-V multiprocessor using ANSI C.

## Dependencies

#### Arch

```bash
sudo pacman -S riscv64-linux-gnu-binutils riscv64-linux-gnu-gcc riscv64-linux-gnu-gdb qemu-emulators-full
```

## Debugging

- Run `riscv64-linux-gnu-gdb` inside the **xv6** directory (whilst the xv6 VM is operational in another terminal obviously), and then to debug a file you've coded, `file user/_<name>`, `b main`, and `continue` (can't `run` because it has to start the kernel too)
- [Source](https://pdos.csail.mit.edu/6.1810/2024/labs/guidance.html)

## BUILDING AND RUNNING XV6

You will need a RISC-V "newlib" tool chain from
https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for
riscv64-softmmu.  Once they are installed, and in your shell
search path, you can run "make qemu".

NOTE: Trivially installing the dependencies listed above should suffice.
