#ifndef BIPARTITEMATCHING_H
#define BIPARTITEMATCHING_H

#include <iostream>
#include <vector>
#include <string>

class BipartiteMatcher {
public:
    // Constructor: Takes the number of professors and students
    BipartiteMatcher(int numProfessors, int numStudents);

    // Function to add an edge between two vertices
    void addEdge(int fromVertex, int toVertex);

    // Connect the source to the professors
    void connectSourceToLeftHalf(int source, const std::vector<int>& leftHalfVertices);

    // Connect the sink to the students
    void connectSinkToRightHalf(int sink, const std::vector<int>& rightHalfVertices);

    // Function to find the maximum matching and write to the output stream
    void findMaximumMatching(int source, int sink, std::ostream& output);

    // Read the graph from a file
    void readGraphFromFile(const std::string& filename);

    // Write the matching result to a file
    void writeMatchingToFile(const std::string& filename);

private:
    // Helper functions for augmenting path and DFS
    bool existsAugmentingPath(int source, int sink);
    void depthFirstSearch(int v, int sink);

    // Edge class representing a directed edge with capacity and flow
    class Edge {
    public:
        Edge(int fromVertex, int toVertex, int capacity = 1);

        int getOtherEndNode(int vertex) const;
        void increaseFlowTo(int vertex, int flow);
        int residualCapacityTo(int vertex) const;
        std::string toString() const;

    private:
        int fromVertex;
        int toVertex;
        int capacity;
        int flow;
    };

    int vertexCount;  // Total number of vertices (including source and sink)
    int flow;         // Total flow
    std::vector<std::string> vertexNames;  // Vertex names
    std::vector<std::vector<Edge>> graph;  // Graph adjacency list
    std::vector<Edge*> edgeTo;  // Array of edges leading to each vertex
    std::vector<bool> isVertexMarked;  // Array to mark visited vertices
};

#endif // BIPARTITEMATCHING_H
