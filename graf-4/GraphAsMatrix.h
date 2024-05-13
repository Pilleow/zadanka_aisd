#ifndef GRAF_GRAPHASMATRIX_H
#define GRAF_GRAPHASMATRIX_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <stack>
#include <queue>
#include "visitor.h"

#define print(x) (std::cout << x << std::endl)

template <typename T>
class Iterator
{
public:
    virtual ~Iterator (){;}
    Iterator(){;}
    virtual bool IsDone () = 0;
    virtual T & operator * () = 0;
    virtual void operator ++ () = 0;
};

class Vertex {
    int number;
public:
    explicit Vertex(int n);

    int weight;
    std::string label;

    int Number() const;
};

class Edge {
protected:
    Vertex *v0;
    Vertex *v1;
public:
    int weight;
    std::string label;

    Edge(Vertex *V0, Vertex *V1);

    Vertex *V0() { return v0; };

    Vertex *V1() { return v1; };

    Vertex *Mate(Vertex *v);
};

class GraphAsMatrix {
    std::vector<Vertex *> vertices;
    std::vector<std::vector<Edge *> > adjacencyMatrix;
    // pierwszy indeks - początek,   drugi indeks - koniec.
    bool isDirected;
    int numberOfVertices;
    int numberOfEdges = 0;

    class AllVerticesIter : public Iterator<Vertex> {
        GraphAsMatrix &owner;
        int current;
    public:
        explicit AllVerticesIter(GraphAsMatrix &owner);

        bool IsDone();

        Vertex &operator*();

        void operator++();
    };

    class AllEdgesIter : public Iterator<Edge> {
        GraphAsMatrix &owner;
        int row;
        int col;
    public:
        void next();

        AllEdgesIter(GraphAsMatrix &owner);

        bool IsDone();

        Edge &operator*();

        void operator++() { next(); }
    };

    class EmanEdgesIter : public Iterator<Edge> {
        GraphAsMatrix &owner;
        int row;
        int col;
    public:
        void next();

        EmanEdgesIter(GraphAsMatrix &owner, int v);

        bool IsDone();

        Edge &operator*();

        void operator++() { next(); }
    };

    class InciEdgesIter : public Iterator<Edge> {
        GraphAsMatrix &owner;
        int row;
        int col;
    public:

        void next();

        InciEdgesIter(GraphAsMatrix &owner, int v);

        bool IsDone();

        Edge &operator*();

        void operator++() { next(); }
    };

public:
    GraphAsMatrix(int n, bool b);

    int NumberOfVertices() const;

    bool IsDirected() const;

    int NumberOfEdges() const;

    bool IsEdge(int u, int v);

    void MakeNull();

    void AddEdge(int u, int v);

    Edge *SelectEdge(int u, int v);

    Vertex *SelectVertex(int v) const;

    Iterator <Vertex> &VerticesIter();

    Iterator <Edge> &EdgesIter();

    Iterator <Edge> &EmanatingEdgesIter(int v);

    Iterator <Edge> &IncidentEdgesIter(int v);

    bool isValidVertexPair(int u, int v) const;

    void dfs(Vertex* v);

    void dfs(AddingVisitor* visitor, Vertex* v);

    void dfsUtil(Vertex* v, std::vector<bool> *visited);

    void dfsUtil(AddingVisitor* visitor, Vertex* v, std::vector<bool> *visited);

    bool isConnected();
};


#endif //GRAF_GRAPHASMATRIX_H
