#include "GraphAsMatrix.h"

#define HALT_ON_MSG false
#define awaitWithMsg(x) std::cout << "\n" << x << " [Enter]..." << std::endl; if (HALT_ON_MSG) std::cin.ignore()


void test();
void testSkierowanySpojny();

int main() {

    awaitWithMsg("Zadanie 1");
    test();
    awaitWithMsg("Zadanie 2");
    testSkierowanySpojny();

    return 0;
}

void test() {
    auto * graph = new GraphAsMatrix(10, false);
    graph->AddEdge(0,1);
    graph->AddEdge(1,2);
    graph->AddEdge(2,3);
    graph->AddEdge(3,4);
    graph->AddEdge(3,7);
    graph->AddEdge(4,5);
    graph->AddEdge(5,9);
    graph->AddEdge(9,9);
    graph->AddEdge(6,8);
    std::cout << "graf jest spojny=" << graph->isConnected()<<std::endl;
    graph->AddEdge(0,8);
    std::cout << "graf jest spojny=" << graph->isConnected()<<std::endl;
}

void testSkierowanySpojny() {
    auto * graph = new GraphAsMatrix(5, true);
    graph->AddEdge(0,1);
    graph->AddEdge(1,0);
    graph->AddEdge(1,2);
    graph->AddEdge(2,1);
    graph->AddEdge(3, 4);
    graph->AddEdge(4,3);
    graph->AddEdge(2,3);
    std::cout << "graf jest spojny=" << graph->isConnected()<<std::endl;
    graph->AddEdge(3, 2);
    std::cout << "graf jest spojny=" << graph->isConnected()<<std::endl;
}
