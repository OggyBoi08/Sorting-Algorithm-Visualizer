# Sorting Visualizer

A C++ sorting algorithm visualizer built with [SDL3](https://github.com/libsdl-org/SDL) and [SDL3_image](https://github.com/libsdl-org/SDL_image).

The program visualizes sorting algorithms by updating the array one step at a time, allowing the sorting process to be seen rather than simply showing the final result.

## Demo

The visualizer opens an `800 x 600` resizable window and displays an array as vertical bars.

- **Red** — unsorted elements
- **Green** — sorted elements
- **Blue** — the element currently being processed

At the moment, `main.cpp` is configured to run **Shell Sort**.

## Algorithms

The project currently contains step-by-step implementations for:

- Insertion Sort
- Bubble Sort
- Heap Sort
- Shell Sort

The sorting logic is separated from the rendering code, making it possible to add or experiment with other algorithms.

## Requirements

### Operating system

The included executable and DLLs are built for:

- **Windows 10/11**
- **64-bit (x86-64)**

### Compiler

The project was developed using:

- **GCC / MinGW-w64**
- **Code::Blocks**
- MSYS2 MinGW-w64 toolchain

The included Code::Blocks project file is:

```text
Sorting_Visualizer.cbp
```

## SDL Versions

This project was built and tested with the following versions:

| Dependency | Version | Architecture |
|---|---:|---|
| SDL3 | **3.4.14** | Windows x64 |
| SDL3_image | **3.4.4** | Windows x64 |

These versions are recommended if you want to reproduce the development environment as closely as possible.

SDL3 was released as version 3.4.14 in August 2026, while SDL3_image 3.4.4 was released in May 2026.

### Important

If you are only interested in **running the included executable**, you do **not** need to install SDL separately. The required runtime DLLs are already included in the project:

```text
SDL3.dll
SDL3_image.dll
```

Both DLLs must remain in the same directory as the executable.

## Running the Program

### Option 1 — Run the included executable

The compiled executable is located at:

```text
bin/Debug/Sorting_Visualizer.exe
```

Make sure these files are together:

```text
bin/
└── Debug/
    ├── Sorting_Visualizer.exe
    ├── SDL3.dll
    ├── SDL3_image.dll
    └── bar-chart.png
```

> **Note:** In the current repository layout, the DLLs and `bar-chart.png` are located in the project root while the executable is inside `bin/Debug/`. For the executable to run correctly from `bin/Debug/`, copy `SDL3.dll`, `SDL3_image.dll`, and `bar-chart.png` into that directory, or run the executable from a working directory where those files are accessible.

## Building from Source

### 1. Install SDL3

Download the **SDL3 3.4.14 development package for MinGW**.

You need the development package rather than only the runtime DLL.

The project expects SDL3 headers and libraries to be available to MinGW.

The relevant structure should look approximately like:

```text
mingw64/
├── include/
│   └── SDL3/
├── lib/
│   ├── libSDL3.dll.a
│   └── ...
└── bin/
    └── SDL3.dll
```

### 2. Install SDL3_image

Download the **SDL3_image 3.4.4 development package for MinGW**.

Its headers should provide:

```text
include/
└── SDL3_image/
    └── SDL_image.h
```

and its library should be available to the linker.

### 3. Configure the compiler

The Code::Blocks project was configured for the MSYS2 MinGW-w64 GCC compiler.

The project links against:

```text
SDL3
SDL3_image
```

### 4. Build

Open:

```text
Sorting_Visualizer.cbp
```

in Code::Blocks and build the project.

Alternatively, the source files can be compiled manually using a MinGW-w64 GCC toolchain with the appropriate SDL3 include and library paths.

## Project Structure

```text
Sorting_Visualizer/
│
├── main.cpp                  # Program entry point and main loop
├── render.cpp                # SDL rendering implementation
├── render.h                  # Renderer interface
├── update.cpp                # Sorting algorithm implementations
├── update.h                  # Sorting state and algorithm declarations
├── utility.cpp               # Utility functions
├── utility.h                 # Utility declarations
│
├── bar-chart.png             # Application icon
│
├── SDL3.dll                 # SDL3 runtime library
├── SDL3_image.dll            # SDL3_image runtime library
│
├── Sorting_Visualizer.cbp    # Code::Blocks project
│
└── bin/
    └── Debug/
        └── Sorting_Visualizer.exe
```

## How It Works

Instead of sorting the entire array in a single function call, the algorithms are implemented as **incremental state machines**.

For example, each frame performs one small portion of the sorting operation:

```cpp
shell_sort_step(state);
```

The renderer then draws the current state of the array.

This approach makes it possible to visualize what the algorithm is doing internally.

The general flow is:

```text
Initialize array
      ↓
Create sorting state
      ↓
Main loop
      ↓
Perform one sorting step
      ↓
Render current array
      ↓
Repeat until sorted
```

## Changing the Algorithm

The currently selected algorithm is controlled in `main.cpp`.

For example, the current program uses:

```cpp
SortState state = CreateShellSortState(arr);
```

To experiment with another implemented algorithm, replace it with the corresponding state constructor:

```cpp
SortState state = CreateInsertionSortState(arr);
```

or:

```cpp
SortState state = CreateBubbleSortState(arr);
```

or:

```cpp
SortState state = CreateHeapSortState(arr);
```

The corresponding step function must also be called in the main loop.

## Controls

There are currently no keyboard controls.

- Close the window to exit the program.
- The window is resizable.

## Technical Details

- Language: **C++**
- Graphics: **SDL3**
- Image loading: **SDL3_image**
- Compiler: **GCC / MinGW-w64**
- IDE: **Code::Blocks**
- Target: **Windows x64**
- Window size: **800 × 600**
- Rendering: SDL3 2D renderer
- Frame delay: approximately **16 ms (~60 FPS)**

## Why I Built This

This project was built to explore sorting algorithms beyond their theoretical implementations by visualizing their individual operations in real time.

It also provided practical experience with:

- C++ programming
- Object-oriented design
- SDL3
- Real-time rendering
- Animation/game loops
- Algorithm implementation
- State-based algorithm visualization
- Separating application logic from rendering logic

## License

This project is available under the license specified in this repository.

If no license file is present, please contact the repository owner before redistributing or modifying the project for other purposes.
