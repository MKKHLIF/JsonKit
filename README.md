# JSON Library

A compact C library implementing [RFC 7159](https://tools.ietf.org/html/rfc7159) for parsing and generating JSON (JavaScript Object Notation) data.

## Getting Started

This library parses and generates JSON data, facilitating data interchange between systems. Ideal for integrating with applications that require structured data communication.

## Supported Platforms

- **Windows**: Visual Studio (MSVC)
- **Linux**: GCC or Clang
- **MacOS**: Xcode (Clang)

## Prerequisites

- [CMake](https://cmake.org/) 3.8 or later
- A C compiler compatible with CMake

## Building the Library

### Step 1: Generate Build System

Create a build directory and generate the build system using CMake:

```sh
mkdir build
cd build
cmake -G "Unix Makefiles" ..
```

### Step 2: Compile and Link

Navigate to the build directory and compile the project using CMake:

```sh
cd build
cmake --build .
```

## License
Licensed under the [MIT license](LICENSE.md).
