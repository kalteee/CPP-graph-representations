# C++ Graph Algorithms and Representations

A robust, object-oriented C++ project demonstrating standard graph representations (Adjacency List and Matrix) and various graph algorithms. The project uses a virtual interface (`IGraph`) to allow algorithms to run seamlessly regardless of the underlying graph representation.

The project started out as an assignment, and in my free time I developed it further. Nonetheless, some variable names in the source code are hungarian, sorry for the incostency for anyone reading it. 

## Features
- **Representations:** `GraphList` (Adjacency List), `GraphMatrix` (Adjacency Matrix).
- **Traversals:** BFS (Breadth-First Search), DFS (Depth-First Search).
- **Algorithms:**
  - Diameter computation.
  - Kosaraju's Algorithm for Strongly Connected Components (Source finding).
  - Cycle detection and Directed Acyclic Graph (DAG) construction.

## How to Build and Run Locally

This project uses **CMake**. To run this on your local machine, ensure you have a C++ compiler (supporting C++17) and CMake installed.

### Windows

You need Visual Studio 2022 with **Desktop Developement with C++** and **CMake**

Clone the repository: 
```powershell
git clone https://github.com/kalteee/CPP-graph-representations.git
cd CPP-graph-representations
```
Create a `build` directory and configure the project: 

```powershell
mkdir build
cd build
cmake ..
```

Build the project: 

```powershell 
cd --build .
```
Run the program from the project root: 

```powershell
cd ..
.\build\Debug\graph_app.exe
```
### Linux

On Ubuntu/Debian install the required tools: 

```bash
sudo apt update
sudo apt install build-essential cmake
```
Clone the repository:

```bash
git clone https://github.com/kalteee/CPP-graph-representations.git
cd CPP-graph-representations
```

Create a build directory and configure the project:

```bash
mkdir build
cd build
cmake ..
```

Build the project:

```bash
cmake --build .
```

Run the program from the project root:

```bash
cd ..
./build/graph_app
```

### Selecting the graph and creating custom tests

When the program starts it automatically detects all `.txt` files in the examples directory and displays them in a numbered order. Choose the number of the file which you want to test. 

The program enables the user to add his/her own graph to the test cases. 

Create a new `.txt` file in the `examples/` directory. 

Make sure to use the required file format.

The first line contains the number of vertices

Each of the following lines contain a directed edge in the form of 

```text
u v
```
which represents a directed edge from vertex `u` to vertex `v`

Vertices are numbered from `0` to `n-1`. 

Save your `.txt` file in the `.examples/` directory.

If you have added or modified a `.txt` file in the directory, you do not need to rebuild the project, simply run the executable. The new or modified file will be displayed as a test option on the interface. 
