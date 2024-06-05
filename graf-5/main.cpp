#include "GraphAsMatrix.h"

#define HALT_ON_MSG false
#define awaitWithMsg(x) std::cout << "\n" << x; if (HALT_ON_MSG) std::cout << " [Enter]..." << std::endl; else std::cout << "\n" << std::endl; if (HALT_ON_MSG) std::cin.ignore()


void test(int startVertex);

int main() {
    test(3);
    test(7);
    return 0;
}

void test(int startVertex) {
    awaitWithMsg("Start: " << startVertex);

    auto* graph = new GraphAsMatrix(10, false);

    graph->AddEdge(0,1);
    graph->AddEdge(1,2);
    graph->AddEdge(2,3);
    graph->AddEdge(3,4);
    graph->AddEdge(3,7);
    graph->AddEdge(4,5);
    graph->AddEdge(5,9);
    graph->AddEdge(9,9);
    graph->AddEdge(8,6);
    graph->AddEdge(0,8);
    graph->AddEdge(3,9);
    graph->AddEdge(5,7);
    graph->AddEdge(9,8);

    graph->DFS_Spanning_Tree(graph->SelectVertex(startVertex));
}
