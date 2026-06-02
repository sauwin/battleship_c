# Battleship — C-Based Console Tactical Game

A structured, console-based implementation of the classic Battleship strategic board game written in pure C. The game features an interactive Command Line Interface (CLI), a modular grid management system, automated AI opponents with variable strategies, and persistent state management for game saving/loading.

---

## About

This project is a strict, low-level implementation of the Battleship board game designed to meet rigorous standards of memory efficiency, procedural architecture, and modular code separation. It handles two-dimensional game matrices, state transition logic, coordinate validation, and pseudo-random decision matrices for the Artificial Intelligence engine without high-level framework abstraction.

---

## Features

- **Robust Game Loop:** Turn-based gameplay execution managing tracking grids (shots fired) and placement grids (own ships).
- **Advanced AI Opponent:** Automated tactical engine utilizing targeted search matrices upon a successful strike and random-dispersal scanning.
- **Dynamic Grid & Placement Subsystem:** Dynamic placement validation checking boundaries, orientation (horizontal/vertical), and multi-tile overlap rules.
- **State Persistence:** Custom structural serialization framework supporting game saving and continuous sessions loading via explicit binary/text formats.
- **Strict Architecture:** Clear compilation segregation via headers (`.h`) and implementations (`.c`) ensuring compile-time safety and optimal linker scoping.

---

## Tech Stack

| Layer | Component | Specification |
|---|---|---|
| Core Language | ISO/IEC 9899:1999 | C99 Standard Compliance |
| Build System | CMake | Version 3.10+ Multi-platform Meta-build |
| Compiler Toolchain | GCC / Clang | Strict warnings enabled (`-Wall -Wextra -Werror`) |
| Paradigm | Procedural | Modular Functional Decomposition |
| I/O Structure | Standard I/O (`stdio.h`) | Stream-based Console Rendering & Serialization |

---

## Project Structure

```
battleship_c-main/
├── .gitattributes          # Git repository attribute tracking configuration
├── .gitignore              # Dependency and binary build artifact exclusions
├── CMakeLists.txt          # Primary cross-platform build definitions configuration
├── CMakeLists.txt.user     # User-specific local IDE workspace and build states
├── LICENSE                 # Project open-source operational licensing permissions
├── README.md               # Complete architectural documentation and usage instructions
├── ai.c                    # Artificial Intelligence decision-making and hunting matrix algorithms
├── ai.h                    # Interface declarations for the automated AI behaviors
├── board.c                 # Grid layout, cell statuses, printing configurations, and tracking logic
├── board.h                 # Structures (`Board`, `Cell`) and programmatic grid manipulation definitions
├── main.c                  # Application entry point, core initialization, and global state engine loop
├── save.c                  # Binary/Text serialization framework for session backup and extraction
├── save.h                  # Persistent I/O interface declarations and state headers
├── ships.c                 # Fleet array tracking, vessel orientation, hit points, and damage handling
├── ships.h                 # Structural abstractions for distinct naval vessels and fleets
└── type.h                  # Centralized global enumerations, primitives, constants, and macro definitions
```

---

## Getting Started

### Prerequisites

- **CMake** v3.10 or higher
- **C Compiler:** Native system toolchain (`gcc`, `clang`, or `MSVC`)
- **Make/Ninja:** Native underlying build automation tool

### Compilation and Build Instructions

Execute a standard out-of-source compilation sequence:

```bash
# Clone the repository (or navigate to the unzipped root directory)
cd battleship_c-main

# Generate build configuration binaries via CMake
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build the executable payload
cmake --build build
```

The resulting executable binary will be generated within the `./build/` directory.

### Running the Application

Execute the compiled application binary straight from the shell console:

```bash
# On Linux/macOS
./build/battleship

# On Windows
.\build\Release\battleship.exe
```

---

## Component Specifications

### 1. Game State and Domain Primitives (`type.h`)
Encapsulates global explicit data declarations, cell state representations (e.g., `CELL_EMPTY`, `CELL_SHIP`, `CELL_HIT`, `CELL_MISS`), and coordinate mappings.

### 2. Grid Management Infrastructure (`board.c` / `board.h`)
Handles the allocation, rendering, and lifecycle of the primary two-dimensional spatial arrays. Provides coordinates manipulation wrappers validating matrix indices before structural manipulation.

### 3. Tactical Automata Engine (`ai.c` / `ai.h`)
Features targeted algorithmic tracking routines. Once a hit occurs on a vessel segment, the engine switches from a sparse scanning sequence to adjacent perimeter sweeping to accelerate vessel sinking.

### 4. Serialization Architecture (`save.c` / `save.h`)
Writes the exact raw binary memory state arrays or formatted text indices directly to files. Validates checksum markers during read operations to prevent game state corruption during runtime loading.

---

## Configuration & Standards Compliance

The source architecture strictly emphasizes:
- Zero dynamic allocation overhead inside the critical game path (utilizing deterministic stack/static bounds).
- Comprehensive guard clauses at the beginning of all modular functions to prevent out-of-bounds index exceptions.
- Explicit definition mapping using enumerations rather than raw magical integers to preserve strict type definitions.

---

## License

This project is distributed under the terms specified in the standard open-source license. Refer to the bundled `LICENSE` file within the repository root for structural permissions, warranties, and explicit liability guidelines.
