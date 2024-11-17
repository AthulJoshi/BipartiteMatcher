#include "bipartite_matcher.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// Constructor
BipartiteMatcher::BipartiteMatcher(int numProfessors, int numStudents)
    : vertexCount(numProfessors + numStudents + 2), flow(0) { // +2 for source and sink
    vertexNames.resize(vertexCount);
    graph.resize(vertexCount);
    edgeTo.resize(vertexCount, nullptr);
    isVertexMarked.resize(vertexCount, false);
}

// Function to add an edge
void BipartiteMatcher::addEdge(int fromVertex, int toVertex) {
    Edge newEdge(fromVertex, toVertex);
    graph[fromVertex].push_back(newEdge);
    graph[toVertex].push_back(newEdge);
}

// Connect source to professors
void BipartiteMatcher::connectSourceToLeftHalf(int source, const std::vector<int>& leftHalfVertices) {
    for (int vertex : leftHalfVertices) {
        addEdge(source, vertex);
    }
}

// Connect sink to students
void BipartiteMatcher::connectSinkToRightHalf(int sink, const std::vector<int>& rightHalfVertices) {
    for (int vertex : rightHalfVertices) {
        addEdge(vertex, sink);
    }
}

// Function to find maximum matching
void BipartiteMatcher::findMaximumMatching(int source, int sink, std::ostream& output) {
    while (existsAugmentingPath(source, sink)) {
        int flowIncrease = 1;
        output << "Matched: " << vertexNames[edgeTo[sink]->getOtherEndNode(sink)] << " & ";
        for (int i = sink; i != source; i = edgeTo[i]->getOtherEndNode(i)) {
            if (edgeTo[i]->getOtherEndNode(i) == source) {
                output << vertexNames[i] << std::endl;
            }
            flowIncrease = std::min(flowIncrease, edgeTo[i]->residualCapacityTo(i));
        }

        for (int i = sink; i != source; i = edgeTo[i]->getOtherEndNode(i)) {
            edgeTo[i]->increaseFlowTo(i, flowIncrease);
        }
        flow += flowIncrease;
    }

    output << "\nMaximum pairs matched = " << flow << std::endl;
}

// Function to check for augmenting path
bool BipartiteMatcher::existsAugmentingPath(int source, int sink) {
    isVertexMarked.assign(vertexCount, false);
    isVertexMarked[source] = true;
    depthFirstSearch(source, sink);
    return isVertexMarked[sink];
}

// Depth First Search for augmenting path
void BipartiteMatcher::depthFirstSearch(int v, int sink) {
    if (v == sink) return;

    for (Edge& edge : graph[v]) {
        int otherEndNode = edge.getOtherEndNode(v);
        if (!isVertexMarked[otherEndNode] && edge.residualCapacityTo(otherEndNode) > 0) {
            edgeTo[otherEndNode] = &edge;
            isVertexMarked[otherEndNode] = true;
            depthFirstSearch(otherEndNode, sink);
        }
    }
}

// Edge class functions
BipartiteMatcher::Edge::Edge(int fromVertex, int toVertex, int capacity)
    : fromVertex(fromVertex), toVertex(toVertex), capacity(capacity), flow(0) {}

int BipartiteMatcher::Edge::getOtherEndNode(int vertex) const {
    return (vertex == fromVertex) ? toVertex : fromVertex;
}

void BipartiteMatcher::Edge::increaseFlowTo(int vertex, int flow) {
    if (vertex == fromVertex) {
        this->flow -= flow;
    } else {
        this->flow += flow;
    }
}

int BipartiteMatcher::Edge::residualCapacityTo(int vertex) const {
    return (vertex == fromVertex) ? flow : (capacity - flow);
}

std::string BipartiteMatcher::Edge::toString() const {
    return "(" + std::to_string(fromVertex) + " --> " + std::to_string(toVertex) + ")";
}

// Read the graph from a file
void BipartiteMatcher::readGraphFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    int numProfessors, numStudents;
    file >> numProfessors >> numStudents;

    // Define source and sink
    int source = numProfessors + numStudents;  // Source is last node
    int sink = numProfessors + numStudents + 1; // Sink is last node + 1

    // Read professors and students
    vertexNames.resize(numProfessors + numStudents + 2); // including source and sink
    for (int i = 0; i < numProfessors; ++i) {
        file >> vertexNames[i];
    }
    for (int i = 0; i < numStudents; ++i) {
        file >> vertexNames[numProfessors + i];
    }

    // Add edges between professors and students
    std::string professor, student;
    while (file >> professor >> student) {
        int fromVertex = std::find(vertexNames.begin(), vertexNames.begin() + numProfessors, professor) - vertexNames.begin();
        int toVertex = std::find(vertexNames.begin() + numProfessors, vertexNames.end(), student) - vertexNames.begin();
        addEdge(fromVertex, toVertex);
    }

    file.close();
}

// Write the matching result to a file
void BipartiteMatcher::writeMatchingToFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    int source = vertexCount - 2;
    int sink = vertexCount - 1;

    findMaximumMatching(source, sink, outFile); // Assuming source is second last and sink is last
    outFile.close();
}
