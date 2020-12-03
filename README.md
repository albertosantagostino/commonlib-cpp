# commonlib

A header-only library to collect personal implementations of algorithms, data structures, primitives and multiple useful classes/functions/snippets written in modern C++

## Library

#### Data structures

| File                                                         | Class    | Base/Derived | Description                |
| ------------------------------------------------------------ | -------- | ------------ | -------------------------- |
| [include/data_structures/matrix.h](include/data_structures/matrix.h) | `Matrix` | B            | Generic 2D matrix template |
| [include/data_structures/grid.h](include/data_structures/grid.h) | `Grid`   | D(Matrix)    | Generic 2D characters grid |

#### Primitives

| File                                                     | Class   | Base/Derived | Description                            |
| -------------------------------------------------------- | ------- | ------------ | -------------------------------------- |
| [include/primitives/actor.h](include/primitives/actor.h) | `Actor` | B            | Generic actor to be placed on a `Grid` |
| [include/primitives/position.h](include/primitives/actor.h) | `Position` | B            | Generic 2D position |

### Unit testing and debugging

Tests are written in C++ and are based on the Google Test framework. To build and run them:

```bash
cd build
cmake . && make
./commonlib_tests
```

To interactively debug any (covered) part of the library, just place a breakpoint in Visual Studio Code and press `F5`.
