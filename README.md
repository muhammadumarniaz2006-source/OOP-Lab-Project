# OOP-Lab-Project
Project Disscussion

# Rules to write code:
1. Use proper comments to explain ---> what is doing why.
2. Do only your assigned/discussed task.
3. every functionality will be core folder.
4. and every classes will be in lib folder.
5. main function will be in main.cpp.
6. use proper git commits while commiting your code.
7. Always commit after one function change with clear message.

### Most Important
Report your daily work with day number in your own .md file.

# Git command to continue to code with changes:
1. git pull

# Git commands to push:
1. git add .                                // git commit -am "ABC"
2. git commit -m "Your changes"
3. git checkout -b your name
4. git push -u origin your name

# How to Run the Project

## 1. Console Version (Standard)
If you haven't set up the GUI library yet, you can run the text-based version:
1. Open your terminal in the project folder.
2. Compile: `g++ main.cpp classes/*.cpp -o main.exe`
3. Run: `./main.exe`

---

# Detailed Raylib Setup Guide (GUI Version)

This guide helps you set up **Raylib** to enable graphics for the Chess game. Follow these steps exactly.

### Step 1: Prerequisites
Ensure you have a C++ compiler installed (MinGW-w64 is recommended for Windows).
*   Open your terminal and type: `g++ --version`
*   If you see a version number, you are ready to go.

### Step 2: Download the Library
1.  Go to the [Raylib GitHub Releases](https://github.com/raysan5/raylib/releases) page.
2.  Scroll down to the **Assets** section of the latest release (e.g., version 5.0).
3.  **Crucial:** Download the version that matches your compiler. 
    *   For 64-bit Windows with MinGW, download: `raylib-5.0_win64_mingw-w64.zip`
    *   *Do not download the "source code" or the "MSVC" version unless you are using Visual Studio.*

### Step 3: Install Files into the Project
1.  Extract the downloaded `.zip` file.
2.  In your project folder (`OOP-Lab-Project`), create a new folder named `raylib`.
3.  From the extracted folder, copy the `include` and `lib` folders and paste them inside your new `raylib` folder.
4.  **Verification:** Your project structure must look like this:
    ```text
    OOP-Lab-Project/
    ├── classes/      (Your .cpp and .hpp files)
    ├── raylib/
    │   ├── include/  (Should contain raylib.h)
    │   └── lib/      (Should contain libraylib.a)
    ├── main.cpp
    └── README.md
    ```

### Step 4: Compiling with Raylib
Because Raylib is an external library, we have to tell `g++` exactly where the files are and which Windows systems to use for graphics. 

**Note on Headers:** You do NOT include `.hpp` files in this command. They are automatically pulled in by the `.cpp` files via `#include`.

**The Command:**
```bash
g++ -I. main.cpp classes/*.cpp -o main.exe -I./raylib/include -L./raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
```

**What do these flags mean?**
*   `-I.`: Tells the compiler to look for your project's header files (like `classes/Board.hpp`) starting from the current folder.
*   `-I./raylib/include`: Tells the compiler to look for Raylib's header files.
*   `-L./raylib/lib`: Tells the compiler where the library code (`libraylib.a`) is.
*   `-lraylib -lopengl32 -lgdi32 -lwinmm`: Links Raylib and the necessary Windows graphics drivers.

### Step 5: Running the Game
After the command finishes without errors, a `main.exe` file will be created. Run it by typing:
```bash
./main.exe
```

### Troubleshooting
*   **"raylib.h: No such file or directory"**: This means your folder structure is wrong or the `-I` path in the command doesn't match where your `include` folder is.
*   **"cannot find -lraylib"**: This means the `-L` path is incorrect or you didn't copy the `libraylib.a` file into `raylib/lib`.

---

# C++ Fundamentals Reference
* Headers (`.hpp`): These are like "contracts" or "blueprints." They tell the compiler what a class looks like (its name, variables, and function names) without
    necessarily saying how those functions work.
* Source (`.cpp`): These contain the "implementation" (the actual code inside the functions).
* Why split them? If you put all your code in headers, every time you include that header in a new file, the compiler has to re-compile all that code. Splitting them
    makes compilation much faster and prevents "multiple definition" errors.


2. Include Guards
Every header file should start and end with an include guard:
1 #ifndef PIECE_HPP
2 #define PIECE_HPP
3 // code here
4 #endif
This prevents the same file from being included twice in the same compilation unit, which would cause an error.


3. How #include and Paths Work
* `#include <vector>` (Angle Brackets): Tells the compiler to look in the System Folders (where standard libraries like STL are kept).
* `#include "Piece.hpp"` (Quotes): Tells the compiler to look in the Current Directory first.
* The `-I` Flag: When you run g++ -I., you are telling the compiler: "Also look for headers in the current directory (.)." This is why we can write #include
    "classes/Board.hpp" from main.cpp.


4. Circular Dependencies (The Chess Problem)
In your project, a Board has Pieces, and a Piece needs to know about the Board to check if a move is valid. This is a "Circular Dependency."
* The Solution: Forward Declaration.
* In Piece.hpp, we don't #include "Board.hpp". Instead, we just say class Board;. This tells C++ "There is a class named Board, trust me."
* We only #include "Board.hpp" inside Piece.cpp (the implementation file), where the compiler actually needs to see the details of the Board.

5. Recommended Project Structure
A standard professional layout looks like this:


1 ProjectRoot/
2 ├── include/       # All .hpp files
3 ├── src/           # All .cpp files
4 ├── lib/           # Third-party libraries
5 ├── main.cpp       # Entry point
6 └── Makefile       # Automates compilation
In your project, we used classes/ for both, which is also very common for smaller lab projects.


6. How to Run the Project
To run a C++ project, you must:
1. Compile every .cpp file into an "object" file.
2. Link all those object files together into one .exe.

You can do this in one command with g++:


1 g++ -I. main.cpp classes/Game.cpp classes/Board.cpp classes/Bishop.cpp classes/Rook.cpp classes/King.cpp classes/Queen.cpp classes/Knight.cpp classes/Pawn.cpp -o chess.exe

* -I. : Search for headers in the current folder.
* main.cpp classes/*.cpp : Include all source files.
* -o chess.exe : Name the output file.


After running that, you just type ./chess.exe to run it!



# classes:
1. Piece:
    i. public:
        a. Position p;
        b. enum color.
        c. name.
        new_row
        method:

        isvalidmove();
2. pawn,bishop,knight,queen,king,rook.
3. Board:
    public:
    Piece array[8][8];
    move;
    method:
        setmove()
    
4. Game.
    Board b;
    cin
    b.setmovefrom
5. player.
6. history.
7. position.
             Game->Board->





### Coordinates of Chess explained
✦ To help you visualize this, think of the board not as a graph, but as a List of Rows (like a spreadsheet or a notebook).

  1. The Visual Map (The "Spreadsheet" View)
  In your code, x is which Line you are on, and y is which Box in that line you are looking at.

    1        FILES (Columns) -> Mapping to pos.y
    2        a(0)  b(1)  c(2)  d(3)  e(4)  f(5)  g(6)  h(7)
    3       +----+----+----+----+----+----+----+----+
    4 x=0 8 |0,0 |0,1 |0,2 |0,3 |0,4 |0,5 |0,6 |0,7 | 8  <-- BLACK SIDE (Start)
    5       +----+----+----+----+----+----+----+----+
    6 x=1 7 |1,0 |1,1 |1,2 |1,3 |1,4 |1,5 |1,6 |1,7 | 7  (Black Pawns)
    7       +----+----+----+----+----+----+----+----+
    8 x=2 6 |2,0 |2,1 |2,2 |2,3 |2,4 |2,5 |2,6 |2,7 | 6
    9       +----+----+----+----+----+----+----+----+
   10 x=3 5 |3,0 |3,1 |3,2 |3,3 |3,4 |3,5 |3,6 |3,7 | 5
   11       +----+----+----+----+----+----+----+----+
   12 x=4 4 |4,0 |4,1 |4,2 |4,3 |4,4 |4,5 |4,6 |4,7 | 4
   13       +----+----+----+----+----+----+----+----+
   14 x=5 3 |5,0 |5,1 |5,2 |5,3 |5,4 |5,5 |5,6 |5,7 | 3
   15       +----+----+----+----+----+----+----+----+
   16 x=6 2 |6,0 |6,1 |6,2 |6,3 |6,4 |6,5 |6,6 |6,7 | 2  (White Pawns)
   17       +----+----+----+----+----+----+----+----+
   18 x=7 1 |7,0 |7,1 |7,2 |7,3 |7,4 |7,5 |7,6 |7,7 | 1  <-- WHITE SIDE (Start)
   19       +----+----+----+----+----+----+----+----+
   20        a(0)  b(1)  c(2)  d(3)  e(4)  f(5)  g(6)  h(7)

  ---

  2. The Movement Mind Map
  Because x=0 is at the top, the directions feel "upside down" compared to math class:

   * Move DOWN (Towards White): x increases (+1).
   * Move UP (Towards Black): x decreases (-1).
   * Move RIGHT (Towards 'h'): y increases (+1).
   * Move LEFT (Towards 'a'): y decreases (-1).

  Pawn Logic Example:
   * White Pawn: Wants to go "Up" (towards Rank 8). In your code, it moves from x=6 to x=5.
       * Direction: {-1, 0} (Row decreases).
   * Black Pawn: Wants to go "Down" (towards Rank 1). In your code, it moves from x=1 to x=2.
       * Direction: {1, 0} (Row increases).

  ---

  3. Quick Translation Guide
  If you are debugging and see a coordinate, use this table:

  ┌──────────────────────┬─────────────────────────────┬──────────────────────────────┐
  │ If you see Pos(x, y) │ Think in Chess...           │ Example                      │
  ├──────────────────────┼─────────────────────────────┼──────────────────────────────┤
  │ x                    │ Rank (The horizontal lines) │ x=0 is Rank 8; x=7 is Rank 1 │
  │ y                    │ File (The vertical columns) │ y=0 is 'a'; y=7 is 'h'       │
  └──────────────────────┴─────────────────────────────┴──────────────────────────────┘

  The "Magic Formula" used in your Game.cpp:
   * Array Row (x) = 8 - RankNumber (e.g., Rank 4 becomes 8 - 4 = 4)
   * Array Col (y) = Char - 'a' (e.g., 'e' becomes 4)

  Why this is actually good:
  When you write squares[pos.x][pos.y], you are literally saying: "Go to Row X, then find the Y-th piece in that row." This is
  exactly how the computer stores the data, which makes your code faster and less prone to "index out of bounds" errors!