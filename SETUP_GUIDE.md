# Setup & Execution Guide

This guide provides instructions for setting up the environment, handling large dependencies, and running the Chess project.

## 1. Dependencies

### Stockfish Engine (Manual Download)
The Stockfish executable was removed from the repository due to GitHub's 100MB file size limit. To run the AI features:
1.  Go to the [Stockfish Download Page](https://stockfishchess.org/download/windows/).
2.  Download the **Windows x86-64-avx2** (or the version compatible with your CPU) binary.
3.  Extract the `.exe` file.
4.  Rename it to `stockfish-windows-x86-64-avx2.exe` (or update the path in your code).
5.  Place it inside the `stockfish/` directory.

### Raylib (GUI Library)
The project uses `raylib` for the graphical interface. The library files are already included in the `raylib/` folder. Ensure your compiler is configured to search the following paths:
- **Includes:** `raylib/include`
- **Libraries:** `raylib/lib`
- **DLL:** `raylib/lib/raylib.dll` must be in the same directory as your compiled executable.

## 2. Compilation

### Using the Makefile (Recommended)
If you have `make` and `g++` installed:
```bash
# To compile the main game
g++ main.cpp classes/*.cpp GUI/GUI.cpp -o chess_game.exe -I./raylib/include -I./classes -I./GUI -L./raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
```

### Manual Compilation
If you are using an IDE like VS Code or CLion, ensure your build task includes:
1.  All `.cpp` files in `classes/`.
2.  `GUI/GUI.cpp`.
3.  Linker flags: `-lraylib -lopengl32 -lgdi32 -lwinmm`.

## 3. Running the Project
1.  Ensure `raylib.dll` is in the root directory.
2.  Ensure the `assets/` folder (containing piece images) is present.
3.  Run the executable:
    ```bash
    ./chess_game.exe
    ```

## 4. Troubleshooting
- **Missing Images:** Ensure you run the executable from the project root so the `assets/` path is resolved correctly.
- **Stockfish Error:** If the AI doesn't move, verify that the Stockfish executable path in `AIPlayer.cpp` (or wherever initialized) matches the file you downloaded.
- **DLL Not Found:** Copy `raylib/lib/raylib.dll` to the same folder as your `.exe`.
