# Raycaster
A simple raycaster built with C++23 using [raylib](https://www.raylib.com/). Simulates light rays casting shadows and refracting through circular objects in real time. Games don't use this technique because of performance implications. Ray tracing is a step in this direction but still requires tricks.

The predecessor was written in Java — performance peaked at ~10k rays. We don't have that problem here hehehe.

<img width="1578" height="1226" alt="kép" src="https://github.com/user-attachments/assets/97c7ef89-9bf9-45ab-ab59-a5dad2e0244b" />

## Features
- Up to 100,000 rays rendered in real time
- Refraction mode with adjustable index of refraction
- Draggable light source
- Bouncing occluder circle

## Controls
| Input | Action |
|---|---|
| Left Mouse Button | Move light source |
| Scroll Wheel | Increase / decrease ray count |
| R | Toggle refraction mode |
| Up / Down Arrow | Adjust index of refraction |
| Home | Set ray count to 0 |
| End | Set ray count to maximum |
| F | Toggle borderless fullscreen |

## Building the Project

### Prerequisites
- 64 bit OS
- **Windows:** MSVC (Visual Studio 2022 or 2026)
- **Linux:** C++23 compatible compiler (e.g. GCC 14+)

---

### Windows MSVC
1. Clone the repo
2. Open cmd in the root folder
3. Run `vendor\premake\windows\premake5.exe vs2022` or `vs2026`
4. Open the `.sln` file in Visual Studio
5. Build and run

---

### Linux
1. Clone the repo
2. Open a terminal in the root folder
3. Give the current user executable permission on the premake binary:
```bash
   chmod +x vendor/premake/linux/premake5
```
4. Generate makefiles:
```bash
   vendor/premake/linux/premake5 gmake
```
5. Build *(only specify `CXX` if your default compiler is not C++23 compatible)*:
```bash
   make CXX=g++-14
```
or:
```bash
   make
```
6. Run:
```bash
   bin/Debug-linux-x86_64/Raycaster/Raycaster
```
