# Midi Legend

[![MIT License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

This project is a 2D rhythm game inspired by Guitar Hero, developed in C using SDL2.

The code available in this repository corresponds to a project template / basecode provided to students of ESIEA as a final semester project. As such, the game is not feature-complete: it is intended to be extended, improved, and completed by students.

A playable demo showcasing one possible final result is provided as a precompiled binary in the Releases section of this repository.

## Demo

The repository contains basecode only.

A demonstration binary showing a possible finished version of the game is available in the Releases section.
This demo is provided for reference only and may differ from the basecode in this repository.
The demo executable is currently compiled for Windows in 64 bits.

## Recommended Build Setup

The recommended way to build the project is:

- Visual Studio 2026 (or newer)
- CMake version 4.1.2 or higher

### Steps

1. Clone the repository
2. Open the folder in Visual Studio 2026. Visual Studio automatically detects CMake projects.
3. Build and run the project from the IDE.

### Building for linux

Use the following commands to install project dependencies:
```
sudo apt install \
  cmake \
  libsdl2-dev \
  libsdl2-image-dev \
  libsdl2-mixer-dev \
  libsdl2-ttf-dev
```
To create the project with CMake, run the following commands:
```
mkdir _build_linux _build_linux/debug
cd _build_linux/debug
cmake ../.. -DCMAKE_BUILD_TYPE=Debug
```
You can then compile the project from the `_build_linux/debug` folder with either of the following two commands:
```
cmake --build .
cmake --build . --clean-first
```
Again from the `_build_linux/debug` folder, you can run the binary with the following line
```
./application/application
```

## Third-party libraries used

This project relies on the following libraries:
- [SDL2](https://github.com/libsdl-org/SDL)
- [SDL2_image](https://github.com/libsdl-org/SDL_image)
- [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf)
- [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer)

## License

### Code

All source code produced for this project is licensed under the MIT License.
See the `LICENSE.md` file for details.

### Assets

Game assets included in this repository are not covered by the MIT license.
They are provided under various third-party licenses.

Detailed information is available in `assets/LICENSES.md`.

## Educational context

This project is provided as part of the curriculum at __ESIEA__.
It is intended for educational purposes and as a starting point for student projects.
The authors make no claim that the basecode represents a complete or production-ready game.