#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <filesystem>

#include "../include/graph/IGraph.h"
#include "../include/graph/GraphList.h"
#include "../include/graph/GraphMatrix.h"
#include "../include/algorithms/Diameter.h"
#include "../include/algorithms/Source.h"
#include "../include/algorithms/Acyclic.h"

using namespace std;


// File format: first line - number of vertices (n) then for n lines (u,v) the edges
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
vector<string> get_test_files() {
    vector<string> files;
    if (!filesystem::exists("examples")) {
    cerr << "Error: examples directory not found." << endl;
    return 1;
}
    for (const auto& entry : filesystem::directory_iterator("examples")) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            files.push_back(entry.path().string());
        }
    }

    sort(files.begin(), files.end());

    return files;
}
// Universal test function
void run_tests(const IGraph& graph, const string& name) {
    cout << "=== Running tests: " << name << " ===" << endl;
    cout << "Number of vertices: " << graph.size() << endl;

    // 1. Diameter
    int diam = Diameter::compute(graph);
    cout << "Diameter: " << (diam == -1 ? "Not strongly connected" : to_string(diam)) << endl;

    // 2. Source 
    int source = Source::findsource(graph);
    cout << "Global Source Node: " << (source == -1 ? "There is no unique Source" : to_string(source)) << endl;

    // 3. Edges closing cycles
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
    vector<string> test_files = get_test_files();
    if (test_files.empty()) {
        cerr << "No graph files found in examples/." << endl;
        return 1;
    }
    cout << "Available graphs:" << endl;
    for (size_t i = 0; i < test_files.size(); ++i) {
        cout << i + 1 << ". " << test_files[i] << endl;
    }

    cout << "\nChoose a graph (1-" << test_files.size() << "): ";
    int choice;
    cin >> choice;

    if (choice < 1 || choice > static_cast<int>(test_files.size())) {
        cerr << "Invalid choice." << endl;
        return 1;
    }
    string test_file = test_files[choice - 1];

    cout << "\nSelected graph: " << test_file << endl;
    cout << "===================================" << endl;
    // Adjacency List
    cout << "\nReading the Graph as Adjacency List..." << endl;

    auto list_graph = load_graph(test_file, false);

    if (list_graph) {
        run_tests(*list_graph, "Adjacency List");
    }
    // Adjacency Matrix
    cout << "\nReading the Graph as Adjacency Matrix..." << endl;

    auto matrix_graph = load_graph(test_file, true);
    if (matrix_graph) {
        run_tests(*matrix_graph, "Adjacency Matrix");
    }

    return 0;
}
