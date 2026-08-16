#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "../include/graph/IGraph.h"
#include "../include/graph/GraphList.h"
#include "../include/graph/GraphMatrix.h"
#include "../include/algorithms/Diameter.h"
#include "../include/algorithms/Source.h"
#include "../include/algorithms/Acyclic.h"

using namespace std;

// Segédfüggvény a gráf beolvasására fájlból
// A fájl formátuma: első sorban a csúcsok száma (n), utána soronként egy él (u v)
unique_ptr<IGraph> load_graph(const string& filename, bool use_matrix) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error with opening the file: " << filename << endl;
        return nullptr;
    }

    int n;
    if (!(file >> n)) return nullptr;

    unique_ptr<IGraph> graph;
    if (use_matrix) {
        graph = make_unique<GraphMatrix>(n);
    } else {
        graph = make_unique<GraphList>(n);
    }

    int u, v;
    while (file >> u >> v) {
        graph->add_edge(u, v);
    }

    return graph;
}

// Univerzális tesztelő függvény (nem tudja, hogy lista vagy mátrix van alatta!)
void run_tests(const IGraph& graph, const string& name) {
    cout << "=== Running tests: " << name << " ===" << endl;
    cout << "Number of vertices: " << graph.size() << endl;

    // 1. Átmérő (Diameter)
    int diam = Diameter::compute(graph);
    cout << "Diameter: " << (diam == -1 ? "Not connected" : to_string(diam)) << endl;

    // 2. Forrás (Source / Kosaraju)
    int source = Source::findsource(graph);
    cout << "Global Source Node: " << (source == -1 ? "There is no unique Source" : to_string(source)) << endl;

    // 3. Kör-élek keresése (Acyclic DFS method)
    auto back_edges = MakeAcyclic::dfsmethod(graph);
    cout << "Number of Edges closing Cycles " << back_edges.size() << endl;
    if (!back_edges.empty()) {
        cout << "  Examples: ";
        for (size_t i = 0; i < min(back_edges.size(), (size_t)3); ++i) {
            cout << "(" << back_edges[i].first << "->" << back_edges[i].second << ") ";
        }
        cout << endl;
    } else {
        cout << " the Graph is Acyclic" << endl;
    }

    cout << "-----------------------------------" << endl;
}

int main() {
    string test_file = "examples/graph1.txt";

    // 1. Tesztelés Szomszédsági Listával
    cout << "Reading the Graph as Adjacency List..." << endl;
    auto list_graph = load_graph(test_file, false);
    if (list_graph) {
        run_tests(*list_graph, "Adjacency List");
    }

    // 2. Tesztelés Szomszédsági Mátrixszal
    cout << "\nReading the Graph as Adjacency Matrix..." << endl;
    auto matrix_graph = load_graph(test_file, true);
    if (matrix_graph) {
        run_tests(*matrix_graph, "Adjacency Matrix");
    }

    return 0;
}
