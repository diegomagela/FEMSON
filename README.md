# FEMSON

## Build and Compile Instructions

To build and compile the project, navigate to the [cpp](cpp/) folder and run the following commands in the terminal:

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
```

This process has been tested with `cmake 3.25.1` and `g++ 12.2.0`. For Debian-based users, you can install `cmake` and `g++` by running the following command in the terminal:

```sh
$ sudo apt install cmake g++-12
```

## Example of Usage

```cpp
#include "input.h"

int main() {
    input femson("filename.femson");

    // Model nodes
    auto const nodes = femson.get_nodes();
    auto const n_nodes = nodes.size();

    for (auto const &node : nodes) {
        auto const id = node.id;
        auto const x_coord = node.x;
        auto const y_coord = node.y;
        auto const z_coord = node.z;

        // Fill model node container
    }

    return 0;
}
```