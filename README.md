# libQuat #{#mainpage}
<!-- the suffix in the above line is required for doxygen to consider this as the index page of the generated documentation site -->

[![Gitpod Ready-to-Code](https://img.shields.io/badge/Gitpod-Ready--to--Code-blue?logo=gitpod)](https://gitpod.io/#https://github.com/kvedala/libquat)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/kvedala/libquat.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/kvedala/libquat/context:cpp) 
![GitHub repo size](https://img.shields.io/github/repo-size/kvedala/libquat?color=red&style=flat-square)
[![C/C++ CI](https://github.com/kvedala/libquat/workflows/C/C++%20CI/badge.svg)](https://github.com/kvedala/libquat/actions?query=workflow%3A%22C%2FC%2B%2B+CI%22)

## Overview
Simple library for operations on 3D vectors and quaternions.

[Online Documentation](https://kvedala.github.io/libquat)

## Features 
* Simple interface in both C and C++
* Can be expoted to a shared library for use in any other high-level languages, including python. 
* Utilizes pragma checks to utilize hardware floating point units (FPU), when available on ARM Cortex-M microcontrollers.
* Ease access in a variety of forms to individual elements of vectors and quaternions.

## Build
There are no external dependencies for this library other than C++ STL. 
1. Configure step
Issue the following command from the root folder of the repo. This created the `build` directory where the library and programs will get built.
```sh
$ cmake -B build -S.
```
2. Compilation step
Issue the following command from the root folder of the repo. This will compile the static library and will be available as `libquat.lib` or `libquat.a`. The configuration option `RelWithDebInfo` will create a release build with some debug info. For a full release with no debug info, change it to `Release`. The installation folder can also be specified here. 
```sh
$ cmake --build build -t all [--config RelWithDebInfo] [-DCMAKE_INSTALL_PREFIX=/opt/local]
```
3. Install the library
This command will install the static library and the header file `libquat.h` to the system. 
```sh
$ cmake --build build -t install
```
4. Compile custom programs
To incorporate to your programs, all functions and their descriptions are available in `libquat.h` and also at the online link above and link against the compiled library.

## Contribute
We welcome any contributions and suggestions. Feel free to submit a pull-quest with appropriate info. Thank you in advance.
