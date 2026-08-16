# C++ Graph Algorithms and Representations

A robust, object-oriented C++ project demonstrating standard graph representations (Adjacency List and Matrix) and various graph algorithms. The project uses a virtual interface (`IGraph`) to allow algorithms to run seamlessly regardless of the underlying graph representation.

## Features
- **Representations:** `GraphList` (Adjacency List), `GraphMatrix` (Adjacency Matrix).
- **Traversals:** BFS (Breadth-First Search), DFS (Depth-First Search).
- **Algorithms:**
  - Diameter computation.
  - Kosaraju's Algorithm for Strongly Connected Components (Source finding).
  - Cycle detection and Directed Acyclic Graph (DAG) construction.

## How to Build and Run Locally

This project uses **CMake**. To run this on your local machine, ensure you have a C++ compiler (supporting C++17) and CMake installed.

### 1. Clone the repository
```bash
git clone [https://github.com/YOUR-USERNAME/YOUR-REPO-NAME.git](https://github.com/YOUR-USERNAME/YOUR-REPO-NAME.git)
cd YOUR-REPO-NAME
```
### 2. Build the project
It is recommended to build the project in a separate build directory: 
```bash
mkdir build
cd build
cmake ..
make
```
