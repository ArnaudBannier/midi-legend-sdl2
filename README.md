# Midi Legend

[![MIT License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

A small SDL3-based 2D engine and demo application.  
This repository provides a reusable game engine (`engine/`) and a sample application (`application/`) demonstrating UI, sprite sheets, input handling, scenes, and resource management.

## Features

- Minimal 2D engine in C using SDL3, SDL3_image, SDL3_ttf and cJSON.
- UI system with buttons, lists, labels, layouts and anchor-based positioning.
- Sprite sheet support, including 9-slice scaling and pixel-art rendering.
- Demo application showcasing scenes, runtime settings and UI composition.
- Clean project layout suitable as a template for new SDL3 projects.
- Built-in asset obfuscation system:
  * Source assets are placed in `assets_dev/`.
  * The build system can automatically generate obfuscated copies.
  * Obfuscated assets are written to `assets/` and can be loaded normally via the `AssetManager`.

## Recommended Build Setup

The recommended way to build the project is:

- Visual Studio 2026 (or newer)
- CMake version 4.1.2 or higher

### Steps

1. Clone the repository
2. Open the folder in Visual Studio 2026. Visual Studio automatically detects CMake projects.
3. Build and run the project from the IDE.

## Project layout

- `engine/` — static library with engine core: renderer, asset manager, UI components, utilities.
- `application/` — demo application (main, scenes, UI pages, asset registration).
- `third_party/` — optional local copies of SDL2 used by MSVC builds.
- `assets/` — images, sprite sheets and data used by the demo.

## Third-party libraries used

- [SDL2](https://github.com/libsdl-org/SDL)
- [SDL2_image](https://github.com/libsdl-org/SDL_image)
- [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf)
- [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer)

## License

This project is provided under the MIT License. See `LICENSE.md`.
