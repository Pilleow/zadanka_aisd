
#include "GraphAsMatrix.h"
#include "visitor.h"

// ------------------------------------------- Vertex

int Vertex::Number() const {
    return number;
}

Vertex::Vertex(int n) {
    weight = 0;
    number = n;
}

// ------------------------------------------- Edge

Vertex *Edge::Mate(Vertex *v) {
    if (v == v0) return v1;
    else return v0;
}

Edge::Edge(Vertex *V0, Vertex *V1) {
    weight = 0;
    v0 = V0;
    v1 = V1;
}

// ------------------------------------------- GraphAsMatrix

GraphAsMatrix::GraphAsMatrix(int n, bool b) {
    std::vector<std::vector<Edge *>> aM(n, std::vector<Edge *>(n, nullptr));
    adjacencyMatrix = aM;

    vertices.reserve(n);
    for (int i = 0; i < n; ++i) {
        vertices[i] = new Vertex(i);
    }

    isDirected = b;
    numberOfVertices = n;
    numberOfEdges = 0;
}

int GraphAsMatrix::NumberOfVertices() const {
    return numberOfVertices;
}

int GraphAsMatrix::NumberOfEdges() const {
    return numberOfEdges;
}

bool GraphAsMatrix::IsDirected() const {
    return isDirected;
}

void GraphAsMatrix::MakeNull() {
    std::vector<std::vector<Edge *>> aM(numberOfVertices, std::vector<Edge *>(numberOfVertices, nullptr));
    adjacencyMatrix = aM;
    numberOfEdges = 0;
}

bool GraphAsMatrix::isValidVertexPair(int u, int v) const {
    return !(u < 0 || u >= numberOfVertices || v < 0 || v >= numberOfVertices);
}

bool GraphAsMatrix::IsEdge(int u, int v) {
    if (!isValidVertexPair(u, v))
        throw std::out_of_range("Jeden z podanych wierzchołków wykracza poza zdefiniowany zakres wierzchołków.");
    if (adjacencyMatrix[u][v] == nullptr) return false;
    return true;
}

void GraphAsMatrix::AddEdge(int u, int v) {
    if (!isValidVertexPair(u, v))
        throw std::out_of_range("Jeden z podanych wierzchołków wykracza poza zdefiniowany zakres wierzchołków.");
    if (IsEdge(u, v)) throw std::runtime_error("Podana krawędź już istnieje.");
    Vertex *v0 = vertices[u];
    Vertex *v1 = vertices[v];
    Edge *e = new Edge(v0, v1);
    adjacencyMatrix[u][v] = e;
    if (!IsDirected()) adjacencyMatrix[v][u] = new Edge(v1, v0);
    numberOfEdges++;
}

Edge *GraphAsMatrix::SelectEdge(int u, int v) {
    if (!isValidVertexPair(u, v))
        throw std::out_of_range("Jeden z podanych wierzchołków wykracza poza zdefiniowany zakres wierzchołków.");
    return adjacencyMatrix[u][v];
}

Vertex *GraphAsMatrix::SelectVertex(int v) const {
    if (v < 0 || v >= numberOfVertices)
        throw std::out_of_range("Wierzchołek wykracza poza zdefiniowany zakres wierzchołków.");
    return vertices[v];
}

Iterator<Vertex> &GraphAsMatrix::VerticesIter() {
    return *(new AllVerticesIter(*this));
}

Iterator<Edge> &GraphAsMatrix::EdgesIter() {
    return *(new AllEdgesIter(*this));
}

Iterator<Edge> &GraphAsMatrix::EmanatingEdgesIter(int v) {
    return *(new EmanEdgesIter(*this, v));
}

Iterator<Edge> &GraphAsMatrix::IncidentEdgesIter(int v) {
    return *(new InciEdgesIter(*this, v));
}


// iteratory -----------------------------------------------------------

GraphAsMatrix::AllVerticesIter::AllVerticesIter(GraphAsMatrix &owner) : owner(owner) {
    current = 0;
}

bool GraphAsMatrix::AllVerticesIter::IsDone() {
    return owner.numberOfVertices <= current;
}

void GraphAsMatrix::AllVerticesIter::operator++() {
    current++;
}

Vertex &GraphAsMatrix::AllVerticesIter::operator*() {
    return *owner.vertices[current];
}

GraphAsMatrix::AllEdgesIter::AllEdgesIter(GraphAsMatrix &owner) : owner(owner) {
    row = 0;
    col = 0;
}

bool GraphAsMatrix::AllEdgesIter::IsDone() {
    return owner.numberOfVertices <= row && owner.numberOfVertices <= col;
}

Edge &GraphAsMatrix::AllEdgesIter::operator*() {
    if (owner.adjacencyMatrix[row][col] == nullptr) next();
    return *owner.adjacencyMatrix[row][col];
}

void GraphAsMatrix::AllEdgesIter::next() {
    do {
        col++;
        if (col >= owner.numberOfVertices) {
            col = 0;
            row++;
        }
    } while (!IsDone() && owner.adjacencyMatrix[row][col] == nullptr);
}

GraphAsMatrix::EmanEdgesIter::EmanEdgesIter(GraphAsMatrix &owner, int v) : owner(owner) {
    row = v;
    col = 0;
}

bool GraphAsMatrix::EmanEdgesIter::IsDone() {
    return owner.numberOfVertices <= col;
}

Edge &GraphAsMatrix::EmanEdgesIter::operator*() {
    if (owner.adjacencyMatrix[row][col] == nullptr) next();
    if (IsDone()) return *(new Edge(nullptr, nullptr));
    return *owner.adjacencyMatrix[row][col];
}

void GraphAsMatrix::EmanEdgesIter::next() {
    do col++; while (!IsDone() && owner.adjacencyMatrix[row][col] == nullptr);
}


GraphAsMatrix::InciEdgesIter::InciEdgesIter(GraphAsMatrix &owner, int v) : owner(owner) {
    col = v;
    row = 0;
}

bool GraphAsMatrix::InciEdgesIter::IsDone() {
    return owner.numberOfVertices <= row;
}

Edge &GraphAsMatrix::InciEdgesIter::operator*() {
    if (owner.adjacencyMatrix[row][col] == nullptr) next();
    return *owner.adjacencyMatrix[row][col];
}

void GraphAsMatrix::InciEdgesIter::next() {
    do row++; while (!IsDone() && owner.adjacencyMatrix[row][col] == nullptr);
}

// dfs, dfsUtil ------------------------------------------------------------------------------

void GraphAsMatrix::dfs(Vertex *v_vert) {
    int v = v_vert->Number();
    std::vector<bool> visited(numberOfVertices, false);

    dfsUtil(v_vert, &visited);

    Iterator<Vertex> &iter = VerticesIter();
    while (!iter.IsDone()) {
        dfsUtil(&iter.operator*(), &visited);
        iter.operator++();
    }
    std::cout << std::endl;
}

void GraphAsMatrix::dfsUtil(Vertex *v_vert, std::vector<bool> *visited) {
    int v = v_vert->Number();
    if (!visited->operator[](v)) {
        std::cout << v << ", ";
        visited->operator[](v) = true;
        Iterator<Edge> &iter = EmanatingEdgesIter(v);
        while (!iter.IsDone()) {
            Edge neighbor = iter.operator*();
            if (neighbor.V1() == nullptr) break;
            if (!visited->operator[](neighbor.V1()->Number())) dfsUtil(neighbor.V1(), visited);
            iter.operator++();
        }
    }
}

// dfs, dfsUtil ale z wizytatorem ------------------------------------------------------------

void GraphAsMatrix::dfs(AddingVisitor *visitor, Vertex *v_vert) {
    int v = v_vert->Number();
    std::vector<bool> visited(numberOfVertices, false);
    dfsUtil(visitor, v_vert, &visited);
}

void GraphAsMatrix::dfsUtil(AddingVisitor *visitor, Vertex *v_vert, std::vector<bool> *visited) {
    int v = v_vert->Number();
    if (!visited->operator[](v)) {
        visitor->Visit();
        visited->operator[](v) = true;
        Iterator<Edge> &iter = EmanatingEdgesIter(v);
        while (!iter.IsDone()) {
            Edge neighbor = iter.operator*();
            if (neighbor.V1() == nullptr) break;
            if (!visited->operator[](neighbor.V1()->Number())) dfsUtil(visitor, neighbor.V1(), visited);
            iter.operator++();
        }
    }
}

bool GraphAsMatrix::isConnected() {
    if (!isDirected) {
        auto *visitor = new AddingVisitor();
        dfs(visitor, SelectVertex(0));
        int out = visitor->getAndResetSum();
        return out == numberOfVertices;
    } else {
        Iterator<Vertex> &iter = VerticesIter();
        while (!iter.IsDone()) {
            Vertex &v = iter.operator*();
            iter.operator++();
            auto *visitor = new AddingVisitor();
            dfs(visitor, &v);
            int out = visitor->getAndResetSum();
            if (out != numberOfVertices) return false;
        }
        return true;
    }
}










// spanning tree -----------------------------------------------------------------------------

void GraphAsMatrix::DFS_Spanning_Tree(Vertex *vVert) {
    if (!isConnected()) throw std::runtime_error("Graf nie jest spójny.");
    std::vector<bool> visited(numberOfVertices, false);
    std::vector<int> parent(numberOfVertices, -1);
    std::cout << "parent[u] > u" << std::endl;
    DFS_Spanning_Tree_1(vVert, visited, parent);
}

void GraphAsMatrix::DFS_Spanning_Tree_1(Vertex *vVert, std::vector<bool> &visited, std::vector<int> &parent) {
    int v = vVert->Number();
    visited[v] = true;
    Iterator<Edge>& iter = EmanatingEdgesIter(v);
    while (!iter.IsDone()) {
        Edge& neighborEdge = iter.operator*();
        Vertex* neighborVertex = neighborEdge.Mate(vVert);
        int u = neighborVertex->Number();
        if (!visited[u]) {
            parent[u] = v;
            std::cout << parent[u] << ">" << u << std::endl;
            DFS_Spanning_Tree_1(neighborVertex, visited, parent);
        }
        iter.operator++();
    }
}
