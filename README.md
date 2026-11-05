# Dzia

[![C/C++ CI](https://github.com/MarharytaKh/Dzia-Game/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/MarharytaKh/Dzia-Game/actions/workflows/c-cpp.yml)
[![Latest release](https://img.shields.io/github/v/release/MarharytaKh/Dzia-Game)](https://github.com/MarharytaKh/Dzia-Game/releases/latest)

Dzia is a small pixel-style game written entirely in C++ using the SFML library. I did not use any game engines, frameworks or shortcuts.
The project focuses on learning and demonstrating the fundamentals of game development:
manual rendering and animation using SFML, game loop, collision detection, and player movement, custom logic and mechanics implemented from scratch.
This project was created to explore how classic 2D games can be built from the ground up, relying only on C++ and SFML for graphics, input, and audio and was made for my University project.

## Download

Ready-to-run zip archives for Windows and Linux are attached to every [release](https://github.com/MarharytaKh/Dzia-Game/releases).

## Build

Requirements: CMake 3.28+, a C++17 compiler (MSVC 2022, GCC or Clang), Python 3 and Git.
SFML 2.6.2 is downloaded and built automatically with CMake `FetchContent`, so nothing has to be installed by hand and no DLLs are stored in the repository.

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure
```

The game is placed in `build/bin` together with its images and fonts.
On Windows the folder can also be opened directly in Visual Studio with **File → Open → Folder**.

On Linux SFML needs these system packages:

```
sudo apt install -y build-essential cmake git python3 libxrandr-dev libxcursor-dev libudev-dev libfreetype-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libx11-dev
```

### Release package

`scripts/release.py` configures, builds, runs the tests and packs the game into `dist/DziaGame-<version>-<os>-<arch>.zip`.
The version is taken from the latest `v*` git tag.

```
python scripts/release.py
```

### Building in WSL

The Linux build can be done on Windows inside WSL2. Use Ubuntu 24.04: it ships CMake 3.28, while Ubuntu 22.04 has only 3.22.

```
wsl --install -d Ubuntu-24.04
```

Then inside Ubuntu install the Linux packages listed above and run:

```
git clone https://github.com/MarharytaKh/Dzia-Game.git
cd Dzia-Game
python3 scripts/release.py
./build/bin/DziaGame
```

On Windows 11 the game window opens through WSLg.

## CI

GitHub Actions builds and tests the game on `windows-latest` and `ubuntu-latest` on every push and pull request, and uploads the zip archives as artifacts.
Pushing a `v*` tag also publishes the archives as a GitHub Release:

```
git tag v1.0.0
git push origin v1.0.0
```

## 🖼️ Image Credits

Part of the images used in the game were created by me, and part were obtained from freely available online resources.
I do not claim ownership or authorship of these images — all rights remain with their respective creators.
