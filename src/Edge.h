#ifndef EDGE_H
#define EDGE_H

#include<string>

class Edge {
private:
    int fromVertex;
    int toVertex;
    int capacity;
    int flow;

public:
    Edge(int fromVertex, int toVertex, int capacity = 1)
        : fromVertex(fromVertex), toVertex(toVertex), capacity(capacity), flow(0) {}

    int getOtherEndNode(int vertex) const;

    int getCapacity() const ;

    int getFlow() const ;

    std::string toString() const;

    int residualCapacityTo(int vertex) const ;
    void increaseFlowTo(int vertex, int changeInFlow) ;
};

#endif
