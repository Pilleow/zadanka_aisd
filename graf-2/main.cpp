#include "GraphAsMatrix.h"

#define HALT_ON_MSG true
#define awaitWithMsg(x) std::cout << "\n" << x << " [Enter]..." << std::endl; if (HALT_ON_MSG) std::cin.ignore()

void testGraph(GraphAsMatrix graph);

int main() {

    print("============= GRAF JEDNOKIERUNKOWY 10 ELEMENTOWY =============");
    testGraph(GraphAsMatrix(10, true));
    print("============= GRAF DWUKIERUNKOWY 10 ELEMENTOWY =============");
    testGraph(GraphAsMatrix(10, false));

    awaitWithMsg("Bonus: Nieistniejąca krawędź! ");

    print("SelectEdge(99990, 65535)");
    GraphAsMatrix(10, true).SelectEdge(99990, 65535);

    return 0;
}

void testGraph(GraphAsMatrix graph) {

    print("graph->NumberOfVertices()            " << graph.NumberOfVertices());
    print("graph->NumberOfEdges()               " << graph.NumberOfEdges());

    awaitWithMsg("Następne: SelectVertex(2)     ");

    Vertex* v = graph.SelectVertex(2);
    print("SelectVertex(2)->Number()            " << v->Number());
    v->weight = v->Number() * v->Number();
    print("SelectVertex(2)->weight              " << v->weight);

    awaitWithMsg("Następne: Dodawanie krawędzi  ");

    print("AddEdge(1, 2)");
    graph.AddEdge(1, 2);
    try {
        print("AddEdge(1, 2)");
        graph.AddEdge(1, 2);
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    print("AddEdge(2, 3)");
    graph.AddEdge(2, 3);
    print("AddEdge(3, 4)");
    graph.AddEdge(3, 4);
    print("AddEdge(9, 9)");
    graph.AddEdge(9, 9);

    awaitWithMsg("Następne: IsEdge()            ");

    print("NumberOfVertices()                   " << graph.NumberOfVertices());
    print("NumberOfEdges()                      " << graph.NumberOfEdges());
    print("IsEdge(1, 1)                         " << graph.IsEdge(1, 1));
    print("IsEdge(1, 2)                         " << graph.IsEdge(1, 2));
    print("IsEdge(2, 1)                         " << graph.IsEdge(2, 1));

    std::vector<std::vector<int>> vec = {{1, 2}, {2, 3}, {3, 4}, {9, 9}};

    for (const auto& pair: vec) {
        awaitWithMsg("Następne: SelectEdge(" << pair[0] << ", " << pair[1] << ")    ");
        Edge *e = graph.SelectEdge(pair[0], pair[1]);
        print("SelectEdge(" << pair[0] << ", " << pair[1] << ")->V0()               " << e->V0() << " (" << e->V0()->Number() << ")");
        print("SelectEdge(" << pair[0] << ", " << pair[1] << ")->V1()               " << e->V1() << " (" << e->V1()->Number() << ")");
        print("SelectEdge(" << pair[0] << ", " << pair[1] << ")->Mate(V0)           " << e->Mate(e->V0()) << " (" << e->Mate(e->V0())->Number() << ")");
        print("SelectEdge(" << pair[0] << ", " << pair[1] << ")->Mate(V1)           " << e->Mate(e->V1()) << " (" << e->Mate(e->V1())->Number() << ")");
        e->weight = e->V0()->Number() + e->V1()->Number();
        print("SelectEdge(" << pair[0] << ", " << pair[1] << ")->weight             " << e->weight);
    }

    awaitWithMsg("Następne: Iterator Vertices   ");

    Iterator<Vertex> &iter1 = graph.VerticesIter();
    while (!iter1.IsDone()) {
        print((*iter1).Number() << " - waga " << (*iter1).weight);
        ++iter1;
    }

    print("\nAddEdge(3, 5)");
    graph.AddEdge(3, 5);
    print("AddEdge(8, 3)");
    graph.AddEdge(8, 3);
    print("AddEdge(5, 2)");
    graph.AddEdge(5, 2);

    awaitWithMsg("Następne: Iterator Edges      ");

    Iterator<Edge> &iter2 = graph.EdgesIter();
    while (!iter2.IsDone()) {
        print((*iter2).V0()->Number() << " -> " << (*iter2).V1()->Number());
        ++iter2;
    }

    awaitWithMsg("Następne: Iterator wychodzących z 3 ");

    Iterator<Edge> &iter3 = graph.EmanatingEdgesIter(3);
    while (!iter3.IsDone()) {
        print((*iter3).V0()->Number() << " -> " << (*iter3).V1()->Number());
        ++iter3;
    }

    awaitWithMsg("Następne: Iterator wchodzących do 2 ");

    Iterator<Edge> &iter4 = graph.IncidentEdgesIter(2);
    while (!iter4.IsDone()) {
        print((*iter4).V0()->Number() << " -> " << (*iter4).V1()->Number());
        ++iter4;
    }

}