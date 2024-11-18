#ifndef BIPARTITE_MATCHING_H
#define BIPARTITE_MATCHING_H

#include "Edge.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <fstream>

class BipartiteMatching {
private:
    std::vector<std::vector<Edge>> graph;
    std::vector<std::string> vertexNames;
    std::unordered_map<std::string, int> nameToIndex;
    int vertexCount;
    int flow;
    std::vector<Edge*> edgeTo;
    std::vector<bool> isVertexMarked;
    std::vector<std::pair<std::string, std::string>> matches;

public:
    BipartiteMatching(int vertexCount, const std::vector<std::string>& vertexNames);

    void addEdge(const std::string& fromName, const std::string& toName);
    void connectSourceToLeftHalf(const std::string& source, const std::vector<std::string>& leftHalfVertices);
    void connectSinkToRightHalf(const std::string& sink, const std::vector<std::string>& rightHalfVertices);
    void fordFulkersonMaxFlow(const std::string& source, const std::string& sink);

private:
    bool existsAugmentingPath(int sourceIndex, int sinkIndex);
    void writeMatchesToFile(const std::string& outputFile) const;
};

#endif
