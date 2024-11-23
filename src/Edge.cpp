#include "Edge.h"
#include <stdexcept>
#include <sstream>
#include<string.h>

// Edge::Edge(int fromVertex, int toVertex, int capacity)
//     : fromVertex(fromVertex), toVertex(toVertex), capacity(capacity), flow(0) {}

int Edge::getOtherEndNode(int vertex) const {
    if (vertex == fromVertex) return toVertex;
    if (vertex == toVertex) return fromVertex;
    throw std::invalid_argument("Vertex not part of edge");
}

int Edge::getCapacity() const { return capacity; }

int Edge::getFlow() const { return flow; }

int Edge::residualCapacityTo(int vertex) const {
    if (vertex == fromVertex) return flow;
    if (vertex == toVertex) return capacity - flow;
    throw std::invalid_argument("Vertex not part of edge");
}

void Edge::increaseFlowTo(int vertex, int changeInFlow) {
    if (vertex == fromVertex) flow -= changeInFlow;
    else if (vertex == toVertex) flow += changeInFlow;
    else throw std::invalid_argument("Vertex not part of edge");
}

std::string Edge::toString() const {
    std::ostringstream oss;
    oss << "(" << fromVertex << " --> " << toVertex << ")";
    return oss.str();
}
