#include "BipartiteMatching.h"

BipartiteMatching::BipartiteMatching(int vertexCount, const std::vector<std::string>& vertexNames)
    : vertexCount(vertexCount), vertexNames(vertexNames), flow(0) {
    graph.resize(vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
        nameToIndex[vertexNames[i]] = i;
    }
}

void BipartiteMatching::addEdge(const std::string& fromName, const std::string& toName) {
    int from = nameToIndex[fromName];
    int to = nameToIndex[toName];
    Edge newEdge(from, to);
    graph[from].push_back(newEdge);
    graph[to].push_back(newEdge);
}

void BipartiteMatching::connectSourceToLeftHalf(const std::string& source, const std::vector<std::string>& leftHalfVertices) {
    for (const auto& vertex : leftHalfVertices) {
        addEdge(source, vertex);
    }
}

void BipartiteMatching::connectSinkToRightHalf(const std::string& sink, const std::vector<std::string>& rightHalfVertices) {
    for (const auto& vertex : rightHalfVertices) {
        addEdge(vertex, sink);
    }
}

void BipartiteMatching::fordFulkersonMaxFlow(const std::string& source, const std::string& sink) {
    int sourceIndex = nameToIndex[source];
    int sinkIndex = nameToIndex[sink];
    edgeTo.resize(vertexCount, nullptr);

    matches.clear();  // Reset matches before running the algorithm

    while (existsAugmentingPath(sourceIndex, sinkIndex)) {
        int flowIncrease = 1;
        for (int v = sinkIndex; v != sourceIndex; v = edgeTo[v]->getOtherEndNode(v)) {
            flowIncrease = std::min(flowIncrease, edgeTo[v]->residualCapacityTo(v));
        }
        for (int v = sinkIndex; v != sourceIndex; v = edgeTo[v]->getOtherEndNode(v)) {
            edgeTo[v]->increaseFlowTo(v, flowIncrease);
        }

        // Track the match (professor -> student) for new flows
        for (int v = sinkIndex; v != sourceIndex; v = edgeTo[v]->getOtherEndNode(v)) {
            if (vertexNames[v] != source && vertexNames[v] != sink) {
                int other = edgeTo[v]->getOtherEndNode(v);
                if (vertexNames[other] != source && vertexNames[other] != sink) {
                    matches.emplace_back(vertexNames[other], vertexNames[v]);
                }
            }
        }
        flow += flowIncrease;
    }

    std::cout << "Maximum pairs matched = " << flow << std::endl;
    writeMatchesToFile("output.txt");
}

bool BipartiteMatching::existsAugmentingPath(int sourceIndex, int sinkIndex) {
    edgeTo.assign(vertexCount, nullptr);
    isVertexMarked.assign(vertexCount, false);

    std::queue<int> queue;
    queue.push(sourceIndex);
    isVertexMarked[sourceIndex] = true;

    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();

        for (Edge& edge : graph[v]) {
            int w = edge.getOtherEndNode(v);
            if (!isVertexMarked[w] && edge.residualCapacityTo(w) > 0) {
                edgeTo[w] = &edge;
                isVertexMarked[w] = true;
                if (w == sinkIndex) return true;
                queue.push(w);
            }
        }
    }
    return false;
}

void BipartiteMatching::writeMatchesToFile(const std::string& outputFile) const {
    std::ofstream out(outputFile);
    if (!out) {
        std::cerr << "Error: Could not write to file " << outputFile << std::endl;
        return;
    }

    out << "Maximum pairs matched: " << flow << "\n";
    out << "Matches:\n";
    for (const auto& match : matches) {
        out << match.first << " -> " << match.second << "\n";
    }

    std::cout << "Matches written to " << outputFile << std::endl;
}
