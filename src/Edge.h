#ifndef EDGE_H
#define EDGE_H

class Edge {
private:
    int fromVertex;
    int toVertex;
    int capacity;
    int flow;

public:
    Edge(int fromVertex, int toVertex, int capacity = 1)
        : fromVertex(fromVertex), toVertex(toVertex), capacity(capacity), flow(0) {}

    int getOtherEndNode(int vertex) const {
        return (vertex == fromVertex) ? toVertex : fromVertex;
    }

    int getCapacity() const { return capacity; }

    int getFlow() const { return flow; }

    std::string toString() const;

    int residualCapacityTo(int vertex) const {
        return (vertex == fromVertex) ? flow : (capacity - flow);
    }

    void increaseFlowTo(int vertex, int changeInFlow) {
        if (vertex == fromVertex) {
            flow -= changeInFlow;
        } else {
            flow += changeInFlow;
        }
    }
};

#endif
