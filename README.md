# JSON Library

An Implementation for [RFC 7159](https://tools.ietf.org/html/rfc7159) for parsing and generating JSON (JavaScript Object
Notation) data.

## Getting Started

This library parses and generates JSON data, facilitating data interchange between systems. Ideal for integrating with
applications that require structured data communication.

## Supported Platforms

- **Windows**: Visual Studio (MSVC)
- **Linux**: GCC or Clang
- **MacOS**: Xcode (Clang)

## Prerequisites

- [CMake](https://cmake.org/) 3.8 or later
- A C++ compiler compatible with CMake (e.g., MSVC, GCC, or Clang)

## Building the Library

To compile the library, use the following steps:

```sh
mkdir build && cd build
cmake ..
make
```

On Windows, use:

```sh
mkdir build && cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

## Usage

```cpp
#include "value.h"
#include <iostream>

int main() {
    // JSON input string
    std::string jsonString = R"({"temperature": 23.5, "unit": "Celsius", "valid": true})";

    // Parse the JSON string
    Json::Value json = Json::Value::FromEncoding(jsonString);

    // Validate parsing
    if (json.GetType() == Json::Value::Type::Invalid) {
        std::cerr << "Failed to parse JSON." << std::endl;
        return 1;
    }

    // Extract values
    double temperature = (double)json["temperature"];
    std::string unit = (std::string)json["unit"];
    bool isValid = (bool)json["valid"];

    // Print extracted values
    std::cout << "Temperature: " << temperature << " " << unit << std::endl;
    std::cout << "Valid: " << (isValid ? "Yes" : "No") << std::endl;

    return 0;
}
```

## License

Licensed under the [MIT license](LICENSE.md).
