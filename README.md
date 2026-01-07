
# 🧩 Rubik’s Cube Solver (CFOP Method) — C++ Implementation

This repository contains a **complete Rubik’s Cube solver written in C++**, based on the widely used **CFOP (Cross, F2L, OLL, PLL)** solving methodology.  
The solver reads a cube state from a file, simulates real cube rotations, and outputs a valid sequence of moves that solves the cube.

This project focuses on **algorithmic correctness, state simulation, and deterministic solving**, rather than brute force or search-based techniques.

---

## 📌 Key Highlights

- Fully implemented **Rubik’s Cube simulation**
- Supports all **basic face rotations** (U, D, L, R, F, B) and their inverses
- Step-by-step solving using **CFOP**
- Reads cube state from a file
- Outputs the exact move sequence used
- Written using **standard C++ (no external libraries)**

---

## 🧠 Solving Strategy Overview (CFOP)

The solver follows the classic **CFOP pipeline**, similar to how speedcubers solve a 3×3 cube.

### 1️⃣ White Cross
- Detects all white edge pieces
- Brings them to the top layer
- Aligns side colors with center pieces
- Inserts them to form a correct white cross

### 2️⃣ White Corners (Completing First Layer)
- Locates white corner pieces
- Moves them to the top layer
- Inserts them using standard right-hand algorithms
- Completes the first layer

### 3️⃣ F2L (First Two Layers)
- Solves middle-layer edges
- Handles both left and right insertion cases
- Removes incorrectly placed edges when necessary
- Completes the first two layers

### 4️⃣ OLL (Orient Last Layer)
- Detects the yellow cross pattern:
  - Dot
  - L-shape
  - Line
  - Cross
- Applies a fixed algorithm to orient all yellow edges

### 5️⃣ PLL (Permute Last Layer)
- Aligns yellow edges with center colors
- Cycles edges until all are correctly placed
- Positions yellow corners
- Orients yellow corners to fully solve the cube

---

## 🗂 Project Structure

. ├── main.cpp           
 # Complete solver implementation 
├── cube_state.txt      
# Input cube configuration 
├── solution.txt        
# Output move sequence 
└── README.md---

## 📥 Input Format (`cube_state.txt`)

- The cube state is represented using **54 characters**
- Faces are stored in the following order:U (Up) D (Down) L (Left) R (Right) F (Front) B (Back)
- Each face contains **9 characters**, listed row-wise
- Total characters: **6 × 9 = 54**

### Example WWWWWWWWWYYYYYYYYYRRRRRRRRROOOOOOOOOGGGGGGGGGBBBBBBBBB
### Color Convention
| Color | Meaning |
|-----|--------|
| W | White |
| Y | Yellow |
| R | Red |
| O | Orange |
| G | Green |
| B | Blue |

> ⚠️ The input must be valid and exactly 54 characters long.

---

## 📤 Output Format (`solution.txt`)

- Contains a **space-separated list of cube moves**
- Represents the exact sequence applied by the solver

### Example Output UC RC UCC FC RCC ...
---

## 🔁 Move Notation

| Notation | Description |
|--------|-------------|
| UC | U face clockwise |
| UCC | U face counter-clockwise |
| DC | D face clockwise |
| DCC | D face counter-clockwise |
| RC | R face clockwise |
| RCC | R face counter-clockwise |
| LC | L face clockwise |
| LCC | L face counter-clockwise |
| FC | F face clockwise |
| FCC | F face counter-clockwise |
| BC | B face clockwise |
| BCC | B face counter-clockwise |

---

## ▶️ Compilation & Execution

### Compile
```bash
g++ -std=gnu++17 main.cpp -o cube_solver
