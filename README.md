An application for MSP430 that blinks an LED.

Use this as a template for building applications using
the following toolchains: GCC, Clang, Mementos, and DINO.

All dependencies (toolchains, except GCC and Clang, and libraries) and the
application are built using [Maker](https://github.com/CMUAbstract/Maker) build
system. Maker relies on submodules to reference dependencies from within the
top-level application repo. This allos strict association between versions of
toolchains and libraries to each application, which helps keep things
deterministic as libraries and toolchains undergo changes.

The following external toolchains need to be installed on the system:

* [TI GCC toolchain](http://www.ti.com/tool/msp430-gcc-opensource): only
  versions up to v3.05 work, due to some incompatibility not yet fixed. Package
  for Arch Linux is available in AUR: [mspgcc-ti](https://aur.archlinux.org/packages/mspgcc-ti).
* [LLVM/Clang](http://llvm.org/) (Mementos and DINO have been updated to build
  against v3.8 only). To get the older version, may have to build from source.
* Cmake is necessary to build LLVM passes in DINO and Mementos

To setup paths to the external toolchains, see variable names in
`ext/maker/Makefile.env` and set them in `Makefile` in top-level directory of
this app: `TI_TOOLCHAIN`, `LLVM_ROOT`. (Note: environment configuration
is not yet cleanly organized in Maker).


To build the tools:

    make ext/<tool>/all

In this case, to build the LLVM passes of Mementos and DINO:

    make ext/mementos/all
    make ext/dino/all

To build the application and its dependencies:

    make bld/<toolchain>/all

where `<toolchain>` is one of: `gcc`, `clang`, `mementos`, `dino`.

Note that the runtime libraries that are part of Mementos and DINO
are libraries, and are built as part of this latter command, just
like any other library, e.g. `libmsp`.

To clean only the app build:

    make bld/<toolchain>/clean

To clean the app and the libraries:

    make bld/<toolchain>/depclean

To build dependencies, without the app:

    make bld/<toolchain>/dep
