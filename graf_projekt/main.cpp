#include "GraphAsMatrix.h"

int solve(int numOfKeys, int* keyLocations);
void traverseDFSandChangeLabel(Vertex* v, int& value, GraphAsMatrix* graph);

int main() {
    int numOfKeys = 1;
    int* keyLocations;
    int solution;
    while (numOfKeys > 0) {
        std::cout << "------" << std::endl;
        std::cin >> numOfKeys;
        std::cout << "\n";
        keyLocations = new int[numOfKeys];
        for (int i = 0; i < numOfKeys; ++i) std::cin >> keyLocations[i];
        solution = solve(numOfKeys, keyLocations);
        std::cout << "\n" <<  solution << std::endl;
    }
    delete keyLocations;
    return 0;
}

int solve(int numOfKeys, int* keyLocations) {
    auto *graph = new GraphAsMatrix(numOfKeys, false);
    int i, solution;

    for (i = 0; i < numOfKeys; ++i) {
        keyLocations[i] -= 1; // because keys are numbered from 1, not 0, so we need to normalize.
        try {
            graph->AddEdge(i, keyLocations[i]);
        } catch (std::runtime_error& ignored) {}
    }

    solution = 0;
    for (i = 0; i < numOfKeys; ++i) {
        Vertex* v = graph->SelectVertex(i);
        if (v->label.empty()) {
            traverseDFSandChangeLabel(v, solution, graph);
            ++solution;
        }
    }

    delete graph;
    return solution;
}

void traverseDFSandChangeLabel(Vertex* v, int& value, GraphAsMatrix* graph) {
    v->label = std::to_string(value);
    Iterator<Edge>& edgesIter = graph->IncidentEdgesIter(v->Number());
    while (!edgesIter.IsDone()) {
        Edge& edge = *edgesIter;
        if (edgesIter.IsDone()) break;
        Vertex* neighbor = edge.Mate(v);
        if (neighbor->label.empty()) {
            // If the neighbor vertex has not been visited yet, recursively call DFS on it
            traverseDFSandChangeLabel(neighbor, value, graph);
        }
        ++edgesIter;
    }
}