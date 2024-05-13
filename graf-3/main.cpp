#include "GraphAsMatrix.h"

#define HALT_ON_MSG false
#define awaitWithMsg(x) std::cout << "\n" << x << " [Enter]..." << std::endl; if (HALT_ON_MSG) std::cin.ignore()


void testDFS(bool isDirected);

int main() {
    awaitWithMsg("TestDFS undirected");
    testDFS(false);
    awaitWithMsg("TestDFS directed");
    testDFS(true);

    return 0;
}

void testDFS(bool isDirected) {
    auto *g = new GraphAsMatrix(10, isDirected);

    g->AddEdge(0,1);
    g->AddEdge(1,2);
    g->AddEdge(2,3);
    g->AddEdge(3,4);
    g->AddEdge(3,7);
    g->AddEdge(4,5);
    g->AddEdge(5,9);
    g->AddEdge(9,9);
    g->AddEdge(6,8);
    g->AddEdge(0,8);

    g->AddEdge(7, 5);

    g->dfs(g->SelectVertex(0));
    delete g;
}
